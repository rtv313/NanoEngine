#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__
#include "assimp/include/assimp/scene.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "Module.h"
#include "Globals.h"
#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include <vector>

class Application;

class ModuleScene : public Module
{
private:
  std::vector<GameObject*> game_objects;
  GameObject* CreateGameObjects(GameObject * father, aiNode* node);
  const aiScene* scene;
  void DrawNodes(GameObject* node);

public:
  ModuleScene();
  ~ModuleScene();

  bool Init();
  update_status PreUpdate();
  update_status Update();
  update_status PostUpdate();
  bool CleanUp();
  
  void Draw();
  bool LoadModel(std::string file);
};

#endif