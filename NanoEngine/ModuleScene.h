#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Globals.h"
#include "GameObject.h"
#include <vector>

class Application;

class ModuleScene : public Module
{
private:
  std::vector<GameObject*> game_objects;

public:
  ModuleScene();
  ~ModuleScene();

  bool Init();
  update_status PreUpdate();
  update_status Update();
  update_status PostUpdate();
  bool CleanUp();

  GameObject* CreateGameObject();
};

#endif