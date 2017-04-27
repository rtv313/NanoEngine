#ifndef __MODULEPHYSICS_H__
#define __MODULEPHYSICS_H__

#include "Module.h"
#include "Globals.h"
#include "Bullet/include/btBulletDynamicsCommon.h"
#ifdef _DEBUG
#pragma comment (lib, "Bullet/libx86/BulletDynamics_debug.lib")
#pragma comment (lib, "Bullet/libx86/BulletCollision_debug.lib")
#pragma comment (lib, "Bullet/libx86/LinearMath_debug.lib")
#else
#pragma comment (lib, "Bullet/libx86/BulletDynamics.lib")
#pragma comment (lib, "Bullet/libx86/BulletCollision.lib")
#pragma comment (lib, "Bullet/libx86/LinearMath.lib")
#endif

class ModulePhysics : public Module
{
public:
  ModulePhysics();
  ~ModulePhysics();

  bool Init();
  update_status PreUpdate();
  update_status Update();
  update_status PostUpdate();
  bool CleanUp();

public:
  btDefaultCollisionConfiguration* collision_conf;
  btCollisionDispatcher* dispatcher;
  btBroadphaseInterface* broad_phase;
  btSequentialImpulseConstraintSolver* solver;
  btDiscreteDynamicsWorld* world;
};

#endif