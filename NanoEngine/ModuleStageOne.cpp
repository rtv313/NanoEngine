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
	
	return true;
}

update_status ModuleStageOne::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleStageOne::CleanUp()
{
	
	return true;
}

