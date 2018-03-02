#pragma once

#include "comp_base.h"
#include "geometry/transform.h"
#include "ia/ai_controller.h"

class TCompPlayerController : public IAIController {
	float   current_x_speed_factor = 2.0f;
	float   x_speed_factor = 2.0f;
	float   y_speed_factor = 0.f;
	VEC3    speed;
	VEC3	  omnidash_vector;
	VEC2	  omnidash_arrow;
	float   dashing_max;
	float   dashing_amount;
	float   jump_end;
	float   gravity;
	float   jump_speed;
	float   omnidash_timer = 0;
	float   omnidash_max_time;
	float		omnidashing_ammount;
	float		omnidashing_max_ammount;
	int     dashing_speed;
	bool    looking_left;
	bool    is_grounded;
	bool		can_omni;
	bool		can_dash;

	VEC3 checkpoint;

  DECL_SIBLING_ACCESS();

public:
	VEC3	  center;
	float	  tower_radius;
  void debugInMenu();
  void load(const json& j, TEntityParseContext& ctx);

  // IA
	void initial_state(float dt);
	void idle_state(float dt);
  void running_state(float dt);
  void jumping_state(float dt);
	void omnidashing_state(float dt);
	void omnidashing_jump_state(float dt);
	void dashing_state(float dt);
	void dead_state(float dt);
	void move_player(bool left, bool change_orientation, float dt, float y_speed);

	bool isForward() { return looking_left; };

	static void registerMsgs();
	void killPlayer(const TMsgKillPlayer& msg);
	void setCheckpoint(const TMsgCheckpoint& msg);

  void init();
};