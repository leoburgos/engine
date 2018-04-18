#include "mcv_platform.h"
#include "glide_state.h"
#include "fsm/context.h"
#include "components/player/comp_player_controller.h"
#include "modules/system/module_physics.h"

using namespace physx;

namespace FSM
{
	void GlideState::onStart(CContext& ctx) const
	{
		CEntity* e = ctx.getOwner();
		TCompPlayerController* player = e->get<TCompPlayerController>();
		TCompTransform *c_my_transform = e->get<TCompTransform>();
		ctx.setVariable("is_grounded", false);
		player->is_grounded = false;
	}

	bool GlideState::load(const json& jData)
	{
		_x_speed = jData.value("x_speed", 2.f);
		return true;
	}

	bool GlideState::update(float dt, CContext& ctx) const
	{		
		CEntity* e = ctx.getOwner();
		TCompPlayerController* player = e->get<TCompPlayerController>();
		TCompTransform *c_my_transform = e->get<TCompTransform>();
		
		TCompCollider *e_col = e->get<TCompCollider>();
	
		//Mitigate force by distance from Center of the fan
		//float distance_from_transform = VEC3::Distance(e_transform->getPosition(), my_transform->getPosition());
		VEC3 direction = VEC3(0,1,0) * 0.025;
		

		PxRigidActor* rigidActor = ((PxRigidActor*)e_col->actor);
		PxTransform tr = rigidActor->getGlobalPose();
		c_my_transform->setPosition(VEC3(tr.p.x, tr.p.y, tr.p.z));


		VEC3 my_pos = c_my_transform->getPosition();
		VEC3 new_pos = my_pos;
		float y_speed;

		// Chequea movimiento
		if (EngineInput["left"].isPressed()) {
			if (!player->looking_left) {
				player->looking_left = true;
				player->move_player(false, true, dt, 0, 2);
			}
			else {
				player->move_player(false, false, dt, 0, 2);
			}
		}
		else if (EngineInput["right"].isPressed()) {
			if (!player->looking_left) {
				player->move_player(true, false, dt, 0, 2);
			}
			else {
				player->looking_left = false;
				player->move_player(true, true, dt, 0, 2);
			}
		}

		e_col->controller->move(physx::PxVec3(direction.x, direction.y, direction.z), 0.f, dt, physx::PxControllerFilters());
		

		return false;
	}

	void GlideState::onFinish(CContext& ctx) const {
		ctx.setVariable("glide", false);
		CEntity* e = ctx.getOwner();
		TCompPlayerController* player = e->get<TCompPlayerController>();
		player->y_speed_factor = 0;
	}

}

