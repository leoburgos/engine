#include "mcv_platform.h"
#include "omnijump_state.h"
#include "components/player/comp_player_controller.h"
#include "fsm/context.h"
#include "components/physics/controller_filter.h"
#include "components/physics/query_filter.h"
#include "components/sound/comp_sound.h"

namespace FSM
{
	void OmnijumpState::onStart(CContext& ctx) const
	{
		CEntity* e = ctx.getOwner();
		TCompPlayerController* player = e->get<TCompPlayerController>();
		_sound->setVolume(player->volumen);
		_sound_cloth_rustle->setVolume(player->volumen);
		TCompTransform* c_my_transform = e->get<TCompTransform>();
		player->jumping_start_height = c_my_transform->getPosition().y;
        player->y_speed_factor = _y_speed;
        player->change_animation(player->EAnimations::NajaJumpLoop, false, 0.01, 0.01, false);
        _sound->start();
        TCompSound* sound = e->get<TCompSound>();
				TMsgVolumeSound msg;
				msg.volumen = player->volumen;
				sound->setVolumen(msg);
        sound->playSound("windstrike");
        sound->playSound("action");
	}

	bool OmnijumpState::load(const json& jData)
	{
		_y_speed = jData.value("y_speed", 12.f);
		_x_speed = jData.value("x_speed", 2.f);
		_is_action = jData.value("is_action", false);
		_delay_out = jData.value("delay_out", 0.01f);
		_delay_in = jData.value("delay_in", 0.01f);
        if (jData.count("sound")) {
            Studio::EventDescription* event_description = NULL;
            std::string event_name = jData["sound"];
            EngineSound.res = EngineSound.system->getEvent(event_name.c_str(), &event_description);
            EngineSound.res = event_description->createInstance(&_sound);
        }
        if (jData.count("sound_cloth")) {
            Studio::EventDescription* event_description_cloth = NULL;
            std::string event_name_cloth = jData["sound_cloth"];
            EngineSound.system->getEvent(event_name_cloth.c_str(), &event_description_cloth);
            event_description_cloth->createInstance(&_sound_cloth_rustle);
        }
		return true;
	}

	bool OmnijumpState::update(float dt, CContext& ctx) const
	{
		CEntity* e = ctx.getOwner();
		TCompPlayerController* player = e->get<TCompPlayerController>();

		TCompCollider* comp_collider = e->get<TCompCollider>();
		TCompTransform *c_my_transform = e->get<TCompTransform>();
		VEC3 my_pos = c_my_transform->getPosition();
		player->omnidash_vector = c_my_transform->getFront();
		if (player->looking_left)
			player->omnidash_vector *= player->omnidash_arrow.x;
		else
			player->omnidash_vector *= player->omnidash_arrow.x * -1;

		player->omnidash_vector.y += player->omnidash_arrow.y;
		VEC3 new_pos;
		new_pos = my_pos + (player->omnidash_vector * ((_y_speed * 6 - player->gravity * dt) * dt));

		VEC3 centre = VEC3(0, new_pos.y, 0);
		float d = VEC3::Distance(centre, new_pos);
		d = (player->tower_radius) / d;
		new_pos.x = new_pos.x * d;
		new_pos.z = new_pos.z * d;

		VEC3 delta_move = new_pos - my_pos;		

		float current_yaw;
		float current_pitch;
		float amount_moved = _x_speed * dt;
		c_my_transform->getYawPitchRoll(&current_yaw, &current_pitch);
		current_yaw = current_yaw - (0.33f * player->omnidash_arrow.x * amount_moved);
		c_my_transform->setYawPitchRoll(current_yaw, current_pitch);

		PxShape* player_shape;
		comp_collider->controller->getActor()->getShapes(&player_shape, 1);
		PxFilterData filter_data = player_shape->getSimulationFilterData();
		ControllerFilterCallback *filter_controller = new ControllerFilterCallback();
		BasicQueryFilterCallback *query_filter = new BasicQueryFilterCallback();
		PxControllerCollisionFlags flags = comp_collider->controller->move(PxVec3(delta_move.x, delta_move.y, delta_move.z), 0.f, dt, PxControllerFilters(&filter_data, query_filter, filter_controller));

		if (flags.isSet(physx::PxControllerCollisionFlag::eCOLLISION_UP) || flags.isSet(physx::PxControllerCollisionFlag::eCOLLISION_SIDES) || flags.isSet(physx::PxControllerCollisionFlag::eCOLLISION_DOWN)) {
			ctx.setVariable("idle", true);
            player->change_animation(player->EAnimations::NajaJumpLoop, false, 0.01, 0.01, false);
		}

		return false;
	}

	void OmnijumpState::onFinish(CContext& ctx) const {
		ctx.setVariable("omnijump", false);
		CEntity* e = ctx.getOwner();
		TCompPlayerController* player = e->get<TCompPlayerController>();   
		player->y_speed_factor = 0;
        player->previous_state = "omnijump";
	}
}