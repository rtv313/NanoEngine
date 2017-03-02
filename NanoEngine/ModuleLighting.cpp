#include "Globals.h"
#include "Application.h"
#include "ModuleLighting.h"
#include "ModuleWindow.h"
#include "Glew/include/GL/glew.h" // extension lib
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "Glew/lib/Release/Win32/glew32.lib" )

ModuleLighting::ModuleLighting()
{

}


ModuleLighting::~ModuleLighting()
{

}

bool ModuleLighting::Init()
{

  return true;
}

update_status ModuleLighting::PreUpdate()
{

  return UPDATE_CONTINUE;
}

update_status ModuleLighting::Update()
{

  return UPDATE_CONTINUE;
}

update_status ModuleLighting::PostUpdate()
{

  return UPDATE_CONTINUE;
}

bool ModuleLighting::CleanUp()
{

  return true;
}
