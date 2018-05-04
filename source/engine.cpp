#include "mcv_platform.h"
#include "engine.h"

#include "modules/system/module_fsm.h"
#include "modules/game/module_splash.h"
#include "modules/game/module_main_menu.h"
#include "modules/game/module_gameover.h"
#include "modules/game/module_test_axis.h"
#include "modules/test/module_test_input.h"
#include "modules/test/module_test_cameras.h"
#include "modules/test/module_test_instancing.h"

//--------------------------------------------------------------------------------------
CEngine& CEngine::get() {
	static CEngine engine;
	return engine;
}

CEngine::CEngine()

	: _module_render("render")
	, _module_entities("entities")
	, _module_physics("physics")
	, _module_ia("ia")
	, _module_input("input")
	, _module_timer("timer")
	, _module_tower("tower")
	, _module_cameras("cameras")
	, _module_fsm("fsm")
  , _module_gui("gui")
{}

bool CEngine::start() {

  static CModuleSplash   module_splash("splash");
  static CModuleMainMenu module_main_menu("main_menu");
  static CModuleGameOver module_game_over("game_over");
  static CModuleTestAxis module_test_axis("test_axis");
  static CModuleTestInput module_test_input("test_input");
  static CModuleTestCameras module_test_cameras("test_cameras");
  static CModuleTestInstancing module_test_instancing("test_instancing");


	_modules.registerSystemModule(&_module_render);
	_modules.registerSystemModule(&_module_entities);
	_modules.registerSystemModule(&_module_physics);
	_modules.registerSystemModule(&_module_ia);
	_modules.registerSystemModule(&_module_input);
	_modules.registerSystemModule(&_module_timer);
	_modules.registerSystemModule(&_module_tower);
	_modules.registerSystemModule(&_module_cameras);
  _modules.registerSystemModule(&_module_fsm);
  _modules.registerSystemModule(&_module_gui);

	_modules.registerGameModule(&module_splash);
	_modules.registerGameModule(&module_main_menu);
	_modules.registerGameModule(&module_game_over);
	_modules.registerGameModule(&module_test_axis);
	_modules.registerGameModule(&module_test_input);
  _modules.registerGameModule(&module_test_instancing);

	_modules.loadModules("data/modules.json");
	_modules.loadGamestates("data/gamestates.json");

	return _modules.start();
}

bool CEngine::stop() {
	bool ok = true;
	ok &= _modules.stop();
	return ok;
}

void CEngine::update(float delta)
{
  PROFILE_FUNCTION("CEngine::update");
  current_unscaled_delta_time = delta;
  _modules.update(delta);
}

void CEngine::render()
{

	PROFILE_FUNCTION("CEngine::render");
	_module_render.generateFrame();
}
