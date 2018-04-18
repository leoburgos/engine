#include "mcv_platform.h"
#include "run_state.h"
#include "fsm/context.h"
#include "components/player/comp_player_controller.h"

namespace FSM
{
	void RunState::onStart(CContext& ctx) const
	{		
		CEntity* e = ctx.getOwner();
		TCompPlayerController* player = e->get<TCompPlayerController>();
		player->change_mesh(0);
	}

	bool RunState::load(const json& jData)
	{
		_x_speed = jData.value("x_speed", 2.f);
		return true;
	}

	bool RunState::update(float dt, CContext& ctx) const
	{
		CEntity* e = ctx.getOwner();
		TCompPlayerController* player = e->get<TCompPlayerController>();
		TCompTransform *c_my_transform = e->get<TCompTransform>();
		float y_speed = (player->y_speed_factor * dt) - (player->gravity * dt * dt / 2);
		
		if (EngineInput["left"].isPressed()) {
			if (!player->looking_left) {
				player->looking_left = true;
				player->move_player(false, true, dt, y_speed, _x_speed);
			}
			else {
				player->move_player(false, false, dt, y_speed, _x_speed);
			}
		}
		else if (EngineInput["right"].isPressed()) {
			if (!player->looking_left) {
				player->move_player(true, false, dt, y_speed, _x_speed);
			}   
			else {
				player->looking_left = false;
				player->move_player(true, true, dt, y_speed, _x_speed);
			}
		}
		// Si no sigue corriendo pasa a estado idle
		if (!EngineInput["left"].isPressed() && !EngineInput["right"].isPressed()) {
			ctx.setVariable("idle", true);
		}
		return false;
	}

	void RunState::onFinish(CContext& ctx) const {
		CEntity* e = ctx.getOwner();
		TCompPlayerController* player = e->get<TCompPlayerController>();
		player->change_mesh(1);
	}
}