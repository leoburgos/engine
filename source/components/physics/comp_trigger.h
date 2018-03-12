#pragma once

#include "components/comp_base.h"
#include "geometry/transform.h"
#include "components/ia/ai_controller.h"

class TCompTrigger : public IAIController {
	enum TriggerTypes {player, runner, plattform, spikes, none};
	std::string trigger_type;
	std::string collider_entity;

	CHandle         h_entity;
	CHandle h_other_entity;
	VEC3 appearing_position;
	bool b_appear;
	bool render = true;
	std::string next_state;

	void onTriggerEnter(const TMsgTriggerEnter& msg);
	void onTriggerExit(const TMsgTriggerExit& msg);
	
	DECL_SIBLING_ACCESS();

public:
	static void registerMsgs();
	void debugInMenu();
	void load(const json& j, TEntityParseContext& ctx);
	void update(float dt);
};