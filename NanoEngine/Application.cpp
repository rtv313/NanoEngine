#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleCameraEditor.h"
#include "ModuleLighting.h"
#include "ModuleEditor.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStageOne.h"
#include "ModulePlayer.h"
#include "TempMicro.h"
#include "Globals.h"
#include <math.h>   


using namespace std;

Application::Application()
{
	TempMicro timer;
	timer.start();
	
	// Order matters: they will init/start/pre/update/post in this order
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());
  modules.push_back(editor = new ModuleEditor());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(audio = new ModuleAudio());
	modules.push_back(cameraEditor = new ModuleCameraEditor());
  modules.push_back(lighting = new ModuleLighting());

	// Game Modules
	modules.push_back(stageOne = new ModuleStageOne(true));
	modules.push_back(player = new ModulePlayer(true));
	// Modules to draw on top of game logic
	modules.push_back(fade = new ModuleFadeToBlack());

	framesSinceStartup = 0;
	averageFPS = 0;
	msLastUpdate = 0;
	resetFPScounter = true;
	actualFPScounter = 0;
	second = 1000.0f;
	dt = 0.0f;
	oldTime = 0.0f;
	newTime = 0.0f;
	LOG_GLOBALS("Time for constructor: %lf", timer.stop());
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

bool Application::Init()
{
	bool ret = true;
	TempMicro timer;
	timer.start();
	timerSinceStart.start();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not anabled

	LOG_GLOBALS("Time for Init() in modules: %lf", timer.stop());

	timer.start();
	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}
	LOG_GLOBALS("Time for Start() in modules: %lf", timer.stop());
	// Start the first scene --
	fade->FadeToBlack(stageOne, nullptr, 1.0f);
	++framesSinceStartup;
	return ret;
}

update_status Application::Update()
{	
	if (resetFPScounter == true) {
		timerFPScounter.start();
		resetFPScounter = false;
	}

	timerMsLastUpdate.start();
    newTime = SDL_GetTicks();
	dt =(newTime - oldTime)/second;
	oldTime = newTime;

	LOG_GLOBALS("Delta Time:%f", dt);
  App->editor->sendFPS(dt);

	update_status ret = UPDATE_CONTINUE;
	
	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
	{
		if ((*it)->IsEnabled() == true) {
			(*it)->dt = dt; // update deltatime
			ret = (*it)->PreUpdate();
		}
	}

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PostUpdate();
	 
	++framesSinceStartup;
	++actualFPScounter;
	
	measureDelayTimer.start();
	Uint32 delayTime = abs((second/FPS_CAP) - msLastUpdate);
	SDL_Delay(delayTime);
	double time = measureDelayTimer.stop();
	LOG_GLOBALS("We waited for %lf ms, and got back in %lf ms", (double)delayTime, time);
	
	if (timerFPScounter.read() / second >= 1.0) {
		char fps[7];
		sprintf(fps, "FPS:%d", actualFPScounter);
		SDL_SetWindowTitle(window->window,fps);
		resetFPScounter = true;
		actualFPScounter = 0;
	}

	return ret;
}

bool Application::CleanUp()
{
	
	LOG_GLOBALS("Amount of time since game started:%d", timerSinceStart.stop());
	averageFPS =ceil(framesSinceStartup / (timerSinceStart.stop() / 1000));
	LOG_GLOBALS("Average FPS whole game life:%d", averageFPS);
	bool ret = true;
	TempMicro timer;
	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->CleanUp();

	LOG_GLOBALS("Time for CleanUp()  modules in microseconds: %lf", timer.stop());
	
	
	return ret;
}

