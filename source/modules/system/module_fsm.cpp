#include "mcv_platform.h"
#include "module_fsm.h"
//#include "utils/json.hpp"
//#include <fstream>

#include "fsm/fsm.h"
#include "fsm/custom_states.h"
#include "fsm/player_states/jump_state.h"
#include "fsm/player_states/dash_state.h"
#include "fsm/player_states/dead_state.h"
#include "fsm/player_states/initial_state.h"
#include "fsm/player_states/omnidash_state.h"
#include "fsm/player_states/omnijump_state.h"
#include "fsm/player_states/idle_state.h"
#include "fsm/player_states/run_state.h"
#include "fsm/player_states/falling_state.h"
#include "fsm/custom_transitions.h"

// for convenience
//using json = nlohmann::json;

CModuleFSM::CModuleFSM(const std::string& name)
	: IModule(name)
{}

bool CModuleFSM::start()
{
  Resources.registerResourceClass(getResourceClassOf<FSM::CMachine>());

  _factory.registerInstancer("AnimationState", new FSM::StateInstancer<FSM::AnimationState>());
	_factory.registerInstancer("InitialState", new FSM::StateInstancer<FSM::InitialState>());
	_factory.registerInstancer("JumpState", new FSM::StateInstancer<FSM::JumpState>());
	_factory.registerInstancer("IdleState", new FSM::StateInstancer<FSM::IdleState>());
	_factory.registerInstancer("RunState", new FSM::StateInstancer<FSM::RunState>());
	_factory.registerInstancer("DashState", new FSM::StateInstancer<FSM::DashState>());
	_factory.registerInstancer("OmnidashState", new FSM::StateInstancer<FSM::OmnidashState>());
	_factory.registerInstancer("OmnijumpState", new FSM::StateInstancer<FSM::OmnijumpState>());
	_factory.registerInstancer("DeadState", new FSM::StateInstancer<FSM::DeadState>());
	_factory.registerInstancer("FallingState", new FSM::StateInstancer<FSM::FallingState>());
  
	_factory.registerInstancer("VariableTransition", new FSM::TransitionInstancer<FSM::VariableTransition>());
	_factory.registerInstancer("LogicTransition", new FSM::TransitionInstancer<FSM::LogicTransition>());
  _factory.registerInstancer("TimeTransition", new FSM::TransitionInstancer<FSM::TimeTransition>());

  return true;
}

bool CModuleFSM::stop()
{
  return true;
}

void CModuleFSM::renderInMenu()
{
	//if (ImGui::TreeNode("Input"))
	//{
	//	// hosts
	//	for (int i = 0; i < Input::NUM_PLAYERS; ++i)
	//	{
	//		auto& host = _hosts[i];
	//		ImGui::PushID(&host);

	//		if (ImGui::TreeNode("Host"))
	//		{
	//			// devices
	//			if (ImGui::TreeNode("Devices"))
	//			{
	//				auto& devices = host.devices();
	//				for (auto& dev : devices)
	//				{
	//					ImGui::Text("%s", dev->getName().c_str());
	//				}
	//				ImGui::TreePop();
	//			}

	//			// keyboard
	//			if (ImGui::TreeNode("Keyboard"))
	//			{
	//				auto& keyboard = host.keyboard();
	//				for (int i = 0; i < Input::NUM_KEYBOARD_KEYS; ++i)
	//				{
	//					const std::string& keyName = getButtonName(Input::KEYBOARD, i);
	//					if (!keyName.empty())
	//					{
	//						ImGui::Text("%20s", keyName.c_str());
	//						ImGui::SameLine();
	//						ImGui::ProgressBar(keyboard.key(i).value);
	//					}
	//				}
	//				ImGui::TreePop();
	//			}

	//			// mouse
	//			if (ImGui::TreeNode("Mouse"))
	//			{
	//				auto& mouse = host.mouse();
	//				ImGui::Text("Position");
	//				ImGui::SameLine();
	//				ImGui::Value("X", mouse._position.x);
	//				ImGui::SameLine();
	//				ImGui::Value("Y", mouse._position.y);
	//				ImGui::Value("Wheel", mouse._wheel_delta);
	//				for (int i = 0; i < Input::MOUSE_BUTTONS; ++i)
	//				{
	//					const std::string& btName = getButtonName(Input::MOUSE, i);
	//					ImGui::Text("%20s", btName.c_str());
	//					ImGui::SameLine();
	//					ImGui::ProgressBar(mouse.button(Input::EMouseButton(i)).value);
	//				}
	//				ImGui::TreePop();
	//			}

	//			// pad
	//			if (ImGui::TreeNode("Pad"))
	//			{
	//				auto& pad = host.pad();
	//				for (int i = 0; i < Input::PAD_BUTTONS; ++i)
	//				{
	//					const std::string& btName = getButtonName(Input::PAD, i);
	//					ImGui::Text("%20s", btName.c_str());
	//					ImGui::SameLine();
	//					if (i < Input::PAD_LANALOG_X)
	//					{
	//						ImGui::ProgressBar(pad.button(Input::EPadButton(i)).value);
	//					}
	//					else
	//					{
	//						ImGui::ProgressBar(0.5f + 0.5f * pad.button(Input::EPadButton(i)).value);
	//					}
	//				}
	//				ImGui::TreePop();
	//			}

	//			// mapping
	//			if (ImGui::TreeNode("Mapping"))
	//			{
	//				auto& mapping = host.mapping();

	//				for (auto& map : mapping.buttons())
	//				{
	//					ImGui::Text("%20s", map.first.c_str());
	//					ImGui::SameLine();
	//					ImGui::ProgressBar(0.5f + 0.5f * map.second.result.value);
	//				}
	//				ImGui::TreePop();
	//			}
	//			ImGui::TreePop();
	//		}
	//		ImGui::PopID();
	//	}

	//	ImGui::TreePop();
	//}
}
