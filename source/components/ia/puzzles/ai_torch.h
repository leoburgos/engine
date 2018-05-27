#ifndef _AIC_TORCH
#define _AIC_TORCH

#include "../ai_controller.h"
#include <string>


class CAITorch : public IAIController
{
  DECL_SIBLING_ACCESS();

	float timer = 0.f;
	float timer_limit;
	boolean in_puzzle;
	std::string puzzle_name;

public:
	boolean active = false;
  void load(const json& j, TEntityParseContext& ctx);
  void debugInMenu();

  void Init();
	void ActiveState(float dt);
	void InactiveState(float dt);
  
  static void registerMsgs();
	void activate();
	void deactivate(const TMsgDeactivateTorch& msg);
};

#endif