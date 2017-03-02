#ifndef __MODULELIGHTING_H__
#define __MODULELIGHTING_H__

#include "Module.h"
#include "Globals.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

class ModuleLighting : public Module
{
public:
  ModuleLighting();
  ~ModuleLighting();

  bool Init();
  update_status PreUpdate();
  update_status Update();
  update_status PostUpdate();
  void Draw();
  bool CleanUp();
};

#endif