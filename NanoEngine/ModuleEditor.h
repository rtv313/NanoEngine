#ifndef __MODULEEDITOR_H__
#define __MODULEEDITOR_H__

#include "Module.h"
#include "Globals.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>



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

};

#endif // __MODULEEDITOR_H__