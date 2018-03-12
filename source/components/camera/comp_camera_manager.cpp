#include "mcv_platform.h"
#include "comp_camera_manager.h"
#include "components/juan/comp_transform.h"
#include "components/player/comp_player_controller.h"

DECL_OBJ_MANAGER("cameraManager", TCompCameraManager);

bool TCompCameraManager::isGrounded()
{
  TCompPlayerController* pc = player->get<TCompPlayerController>();
  return pc->isGrounded();
}

bool TCompCameraManager::isForward()
{

  TCompPlayerController* pc = player->get<TCompPlayerController>();
  return !pc->isForward();
  //if (player.x > 0 && player.z < 0) {								// CUADRANTE 1 (+-)
  //	if (frontPlayer.x < 0 && frontPlayer.z < 0) return true;
  //	return false;
  //}
  //else if (player.x < 0 && player.z < 0) {						// CUADRANTE 2 (--)
  //	if (frontPlayer.x < 0 && frontPlayer.z > 0) return true;
  //	return false;
  //}
  //else if (player.x < 0 && player.z > 0) {						// CUADRANTE 3 (-+)
  //	if (frontPlayer.x > 0 && frontPlayer.z > 0) return true;
  //	return false;
  //}
  //else if (player.x > 0 && player.z > 0) {						// CUADRANTE 4 (++)
  //	if (frontPlayer.x > 0 && frontPlayer.z < 0) return true;
  //	return false;
  //}
  //else return false;
}

//void TCompCameraManager::changeCamerainPlatform(const TMsgchangeCamerainPlatform & msg) {
//  inPlatform = true;
//}

void TCompCameraManager::attachPlayer(const TMsgAttachTo & msg){
  platform = (CEntity *)msg.h_attached;
  TCompTransform* pl = platform->get<TCompTransform>();
  assert(pl);
  VEC3 plPos = pl->getPosition();

  TCompTransform* p = player->get<TCompTransform>();
  assert(p);
  VEC3 pPos = p->getPosition();

  if (pPos.y > plPos.y)inPlatform = true;
}

void TCompCameraManager::detachPlayer(const TMsgDetachOf & msg){
  if (inPlatform) {
    inPlatform = false;
    jumpinPlatform = true;
  }
}


void TCompCameraManager::registerMsgs() {
  DECL_MSG(TCompCameraManager, TMsgAttachTo, attachPlayer);
  DECL_MSG(TCompCameraManager, TMsgDetachOf, detachPlayer);
}

void TCompCameraManager::debugInMenu() {

  /*float fov_deg = rad2deg(getFov());
  float new_znear = getZNear();
  float new_zfar = getZFar();*/
  float fov_deg = 0.f;
  ImGui::DragFloat("Fov", &fov_deg, 0.1f, 30.f, 175.f);
}

void TCompCameraManager::load(const json& j, TEntityParseContext& ctx) {

  // ..
  player = (CEntity *)getEntityByName("The Player");

  //float fov_deg = j.value("fov", rad2deg(getFov()));
  //float z_near = j.value("z_near", getZNear());
  //float z_far = j.value("z_far", getZFar());
  //setPerspective(deg2rad(fov_deg), z_near, z_far);

  pForwarding = true;

  carga = true;

  inPlatform = false;
  jumpinPlatform = false;
  exitPlatform = false;

  lateral = false;
}

void TCompCameraManager::update(float dt) {

  if (carga) {
    CHandle h_camera = getEntityByName("camera_orbit_IZQ");
    Engine.getCameras().setDefaultCamera(h_camera);

    h_camera = getEntityByName("the_camera");
    Engine.getCameras().setOutputCamera(h_camera);

    lateral = true;

    carga = false;
  }

  TCompTransform* p = player->get<TCompTransform>();
  assert(p);
  VEC3 pPos = p->getPosition();

  static Interpolator::TSineInOutInterpolator interpolator;

  if (exitPlatform && isGrounded())exitPlatform = false;

  if (jumpinPlatform) {
    jumpinPlatform = false;
    exitPlatform = true;
  }

  if ((inPlatform || exitPlatform) && lateral) {
    CHandle h_camera = getEntityByName("camera_platform");
    Engine.getCameras().blendInCamera(h_camera, 1.f, CModuleCameras::EPriority::GAMEPLAY, &interpolator);

    lateral = false;
  }
  else if(!inPlatform && !exitPlatform) {
    bool playerForward = isForward();  //Vemos si el player se esta moviendo hacia delante o hacia atras

    CEntity* camIzq = (CEntity *)getEntityByName("camera_orbit_IZQ");
    TCompTransform* ci = camIzq->get<TCompTransform>();
    assert(ci);
    VEC3 cip = ci->getPosition();
    float distanceCamIzq = VEC3::Distance(pPos, cip);

    CEntity* camDer = (CEntity *)getEntityByName("camera_orbit_DER");
    TCompTransform* cd = camDer->get<TCompTransform>();
    assert(cd);
    VEC3 cdp = cd->getPosition();
    float distanceCamDer = VEC3::Distance(pPos, cdp);

    if ((playerForward && distanceCamDer > 9.f)) {
      //if (!pForwarding) {
      //if (inPlatform) {
      //  /*CHandle h_camera = getEntityByName("camera_orbit_DER");
      //  Engine.getCameras().blendInCamera(h_camera, 1.f, CModuleCameras::EPriority::GAMEPLAY, &interpolator);*/
      //  inPlatform = false;
      //}
      CHandle h_camera = getEntityByName("camera_orbit_IZQ");
      Engine.getCameras().blendInCamera(h_camera, 1.f, CModuleCameras::EPriority::GAMEPLAY, &interpolator);

      pForwarding = true;

      lateral = true;
      //}
    }
    else if (/*(*/distanceCamIzq > 9.f) {//) && !blending*/) {
                                         //if (pForwarding) {
      //if (inPlatform) {
      //  /*CHandle h_camera = getEntityByName("camera_orbit_IZQ");
      //  Engine.getCameras().blendInCamera(h_camera, 1.f, CModuleCameras::EPriority::GAMEPLAY, &interpolator);*/
      //  inPlatform = false;
      //}
      CHandle h_camera = getEntityByName("camera_orbit_DER");
      Engine.getCameras().blendInCamera(h_camera, 1.f, CModuleCameras::EPriority::GAMEPLAY, &interpolator);

      pForwarding = false;

      lateral = true;
      //}
    }
  }

}
