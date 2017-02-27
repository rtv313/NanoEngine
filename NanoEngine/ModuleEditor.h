#ifndef __MODULEEDITOR_H__
#define __MODULEEDITOR_H__

#include "Module.h"
#include "Globals.h"
#include "imgui/imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

struct ConsoleLog
{
  ImGuiTextBuffer     Buf;
  bool                ScrollToBottom;

  void    Clear() { Buf.clear(); }

  void    AddLog(const char* fmt)
  {
    va_list args;
    va_start(args, fmt);
    Buf.appendv(fmt, args);
    va_end(args);
    ScrollToBottom = true;
  }

  void    Draw(const char* title, bool* p_opened = NULL)
  {
    ImGui::Begin(title, p_opened);
    ImGui::TextUnformatted(Buf.begin());
    if (ScrollToBottom)
      ImGui::SetScrollHere(1.0f);
    ScrollToBottom = false;
    ImGui::End();
  }
};

class ModuleEditor : public Module
{
public:
  ModuleEditor();
  ~ModuleEditor();

  bool Init();
  update_status PreUpdate();
  update_status Update();
  update_status PostUpdate();
  void Draw();
  bool CleanUp();

public:
  ImGuiTextBuffer Buf;
  ConsoleLog console;
  bool showcase;
  bool consoleIsActive;
};

#endif // __MODULEEDITOR_H__