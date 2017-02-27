#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "imgui/imgui.h"
#include "imgui_impl_sdl_gl3.h"
#define WIN32_MEAN_AND_LEAN
#include <Windows.h>
#include "Glew/include/GL/glew.h" // extension lib
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"
#include "SolidSphere.h"
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "Glew/lib/Release/Win32/glew32.lib" )
#pragma comment(lib,"DevIL/lib/x86/Release/DevIL.lib")
#pragma comment(lib,"DevIL/lib/x86/Release/ILU.lib")
#pragma comment(lib,"DevIL/lib/x86/Release/ILUT.lib")

ModuleEditor::ModuleEditor()
{

}

// Destructor
ModuleEditor::~ModuleEditor()
{

}

// Called before render is available
bool ModuleEditor::Init()
{
  LOG_GLOBALS("Creating Editor context");
  bool ret = ImGui_ImplSdlGL3_Init(App->window->window);

  return ret;
}

update_status ModuleEditor::PreUpdate()
{
  ImGui_ImplSdlGL3_NewFrame(App->window->window);
  return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{
  ImGui::ShowTestWindow();
  return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
  return UPDATE_CONTINUE;
}

void ModuleEditor::Draw()
{
  ImGui::Render();
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
  LOG_GLOBALS("Destroying editor");
  return true;
}


