#include "Application.h"
#include "ModulePhysics.h"

ModulePhysics::ModulePhysics()
{
  collision_conf = nullptr;
  dispatcher = nullptr;
  broad_phase = nullptr;
  solver = nullptr;
  world = nullptr;
}

ModulePhysics::~ModulePhysics()
{

}

bool ModulePhysics::Init()
{
  collision_conf = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collision_conf);
  broad_phase = new btDbvtBroadphase();
  solver = new btSequentialImpulseConstraintSolver;
  world = new btDiscreteDynamicsWorld(dispatcher, broad_phase, solver, collision_conf);
  world->setGravity(btVector3(0.0f, -10.0f, 0.0f));

  return true;
}

update_status ModulePhysics::PreUpdate()
{
  return UPDATE_CONTINUE;
}

update_status ModulePhysics::Update()
{
  return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate() 
{
  return UPDATE_CONTINUE;
}

bool ModulePhysics::CleanUp()
{
  return true;
}
