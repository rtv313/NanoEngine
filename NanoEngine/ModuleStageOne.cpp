#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleStageOne.h"
#include "ModuleFadeToBlack.h"

ModuleStageOne::ModuleStageOne(bool active):Module(active)
{
}


ModuleStageOne::~ModuleStageOne()
{
}

bool ModuleStageOne::Start() {
	LOG_GLOBALS("Loading Scene");
	levelOne = App->textures->Load("Assets/level1.png");
	background = Animation();
	background.frames.push_back({ 518, 7, 1404, 357 });
	return true;
}

update_status ModuleStageOne::Update()
{
	App->renderer->Blit(levelOne, 0, 0, &(background.GetCurrentFrame()), 1.0f);
	return UPDATE_CONTINUE;
}

bool ModuleStageOne::CleanUp()
{
	App->textures->Unload(levelOne);
	return true;
}

