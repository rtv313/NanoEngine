#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "TempMili.h"
class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleCameraEditor;
class ModuleEditor;
class ModuleLighting;
class ModuleScene;
class ModulePhysics;
// Game modules ---
class ModulePlayer;
class ModuleSceneIntro;
class ModuleLevelIntro;
class ModuleStageOne;

class Application
{
public:

	Application();
	~Application();
	bool Init();
	update_status Update();
	bool CleanUp();
	
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleCameraEditor* cameraEditor;
  ModuleEditor* editor;
  ModuleLighting* lighting;
  ModuleScene* scene;
  ModulePhysics* physics;

	// Game modules ---
	ModulePlayer* player;
	ModuleSceneIntro* scene_intro;
	ModuleLevelIntro * levelIntro;
	ModuleStageOne * stageOne;
	TempMili timerSinceStart;
	TempMili timerMsLastUpdate;
	TempMili timerFPScounter;
	long int framesSinceStartup;
	int averageFPS;
	double msLastUpdate;
	int actualFPScounter;
	bool resetFPScounter;
	TempMili measureDelayTimer;
	double second;
	float dt;
	Uint32 newTime;
	Uint32 oldTime;

private:

	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__