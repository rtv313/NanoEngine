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
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "Glew/lib/Release/Win32/glew32.lib" )

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

  showcase = false;
  consoleIsActive = false;
  console.AddLog("Sample Text");

  fps_log = std::vector<float>(60, -1.0);

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
  update_status ret = UPDATE_CONTINUE;
  
  if (ImGui::BeginMainMenuBar())
  {
    bool selected = false;
    if (ImGui::BeginMenu("File"))
    {
      ImGui::MenuItem("New ...");
      ImGui::MenuItem("Load ...");
      if (ImGui::MenuItem("Save ..."));
        //App->level->Save("level.json");

      if (ImGui::MenuItem("Quit", "ESC"))
        ret = UPDATE_STOP;

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("View"))
    {
      if (ImGui::MenuItem("Console", "1"))
        consoleIsActive = !consoleIsActive;
      //ImGui::MenuItem("Scene Hierarchy", "2", &tree->active);
      //ImGui::MenuItem("Properties", "3", &props->active);
      //ImGui::MenuItem("Configuration", "4", &conf->active);
      //ImGui::MenuItem("Resource Browser", "5", &res->active);
      //ImGui::MenuItem("Quick Bar", "6", &res->active);

      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Help"))
    {
      if (ImGui::MenuItem("Gui Demo"))
        showcase = !showcase;

      if (ImGui::MenuItem("Documentation"))
        HINSTANCE r = ShellExecute(NULL, "open", "https://github.com/rtv313/NanoEngine/wiki", NULL, NULL, SW_SHOWNORMAL);

      if (ImGui::MenuItem("Download latest"))
        HINSTANCE r = ShellExecute(NULL, "open", "https://github.com/rtv313/NanoEngine/releases", NULL, NULL, SW_SHOWNORMAL);

      if (ImGui::MenuItem("Report a bug"))
        HINSTANCE r = ShellExecute(NULL, "open", "https://github.com/rtv313/NanoEngine/issues", NULL, NULL, SW_SHOWNORMAL);

      if (ImGui::MenuItem("About"));
        //about->SwitchActive();

      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }

  char title[25];
  ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 1.0f, ImVec2(310, 100));
  ImGui::PlotHistogram("##milliseconds", &fps_log[0], fps_log.size(), 0, title, 0.0f, 1.0f, ImVec2(310, 100));


  if (consoleIsActive) console.Draw("Console", &consoleIsActive);
  if (showcase) ImGui::ShowTestWindow();

  return ret;
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
  ImGui_ImplSdlGL3_Shutdown();
  return true;
}

void ModuleEditor::sendFPS(float delta)
{
  if (fps_log[0] != -1.0) {
    std::rotate(fps_log.begin(), fps_log.begin() + 1, fps_log.end());
  }
  fps_log[fps_log.size() - 1] = delta;
}
