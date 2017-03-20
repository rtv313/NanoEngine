#include "Globals.h"
#include "ModuleScene.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "assimp/include/assimp/cimport.h"
#include "assimp/include/assimp/postprocess.h"
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"

#pragma comment(lib, "assimp/lib/assimp.lib")

ModuleScene::ModuleScene()
{

}

ModuleScene::~ModuleScene()
{

}

bool ModuleScene::Init()
{

  return true;
}

update_status ModuleScene::PreUpdate()
{

  return UPDATE_CONTINUE;
}

update_status ModuleScene::Update()
{

  return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate()
{

  return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{

  return true;
}

GameObject * ModuleScene::CreateGameObject()
{

  return new GameObject();
}
