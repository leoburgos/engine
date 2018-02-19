#pragma once

#include "modules/module.h"
#include "camera/controllers/camera_controller_free.h"
#include "camera/controllers/camera_controller_orbit.h"
#include "geometry/curve.h"

class CModuleTestCameras : public IModule
{
public:
  CModuleTestCameras(const std::string& name)
		: IModule(name)
	{}
  bool start() override;
  void update(float delta) override;
  void render() override;

private:
  CCameraController_Free _free;
  CCameraController_Orbit _orbit;
  CCamera _cameraA;
  CCamera _cameraB;
  CCamera _cameraC;
  CCamera _cameraD;
  CCurve _curve;
};