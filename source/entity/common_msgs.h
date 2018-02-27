#ifndef INC_COMMON_ENTITY_MSGS_
#define INC_COMMON_ENTITY_MSGS_

#include "msgs.h"
#include "geometry/transform.h"

struct TMsgEntityCreated {
  DECL_MSG_ID();
};

struct TMsgAssignBulletOwner {
  CHandle h_owner;
  DECL_MSG_ID();
};

struct TMsgDamage {
  CHandle h_sender;
  CHandle h_bullet;
  DECL_MSG_ID();
};

struct TMsgJump {
	VEC3 jump_position;
	DECL_MSG_ID();
};

struct TMsgAppear {
	VEC3 appearing_position;
	DECL_MSG_ID();
};

struct TMsgAttachTo {
	CHandle h_attached;
	CHandle h_attacher;
	DECL_MSG_ID();
};

struct TMsgDetachOf {
	CHandle h_attached;
	CHandle h_attacher;
	DECL_MSG_ID();
};

// Sent to all entities from a parsed file once all the entities
// in that file has been created. Used to link entities between them
struct TEntityParseContext;
struct TMsgEntitiesGroupCreated {
  const TEntityParseContext& ctx;
  DECL_MSG_ID();
};

/*
struct TMsgTimeOut {
  DECL_MSG_ID();
};

struct TMsgSpawn {
  DECL_MSG_ID();
};

struct TMsgDefineLocalAABB {
  AABB* aabb;
  DECL_MSG_ID();
};

struct TMsgSpawnAt {
  CTransform where;
  DECL_MSG_ID();
};
*/

#endif

