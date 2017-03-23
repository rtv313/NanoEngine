#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleEditor.h"
#include "ModuleScene.h"
#include "SDL/include/SDL.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "SolidSphere.h"
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "Glew/lib/Release/Win32/glew32.lib" )
#pragma comment(lib,"DevIL/lib/x86/Release/DevIL.lib")
#pragma comment(lib,"DevIL/lib/x86/Release/ILU.lib")
#pragma comment(lib,"DevIL/lib/x86/Release/ILUT.lib")

ModuleRender::ModuleRender()
{

}

// Destructor
ModuleRender::~ModuleRender()
{
	delete grid;
	delete cube;
}

// Called before render is available
bool ModuleRender::Init()
{
	LOG_GLOBALS("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

  renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == nullptr)
	{
		LOG_GLOBALS("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	//  ----- Initialise DevIL -----
	ilutRenderer(ILUT_OPENGL);
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	//batman = Model("3DModels/Batman/Batman.obj");
	//magneto = Model("3DModels/Magneto/magnetto2.fbx");
	//city = Level("3DModels/street/Street.obj");
	//PJ = Level("3DModels/ArmyPilot/ArmyPilot.dae");

  App->scene->LoadModel("3DModels/ArmyPilot/ArmyPilot.dae");
  App->scene->LoadModel("3DModels/street/Street.obj");

  //city = Model("3DModels/street/Street.obj");
	grid = new Grid();
	cube = new Cube();
	return ret;
}

update_status ModuleRender::PreUpdate()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{	
	
	//cube->draw();
	gizmo.setPosition(0,3,0);
	gizmo.draw();
	grid->draw();

  //city.draw();
  //batman.draw();
  //magneto.draw();
	//city.Draw();
	//PJ.DrawHierarchy(PJ.root);
	//PJ.draw();

  App->scene->Draw();

	glPopMatrix();
	
  App->editor->Draw();
	SDL_GL_SwapWindow(App->window->window); // stay here not inside any class
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG_GLOBALS("Destroying renderer");

	//Destroy window
	if(renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}


