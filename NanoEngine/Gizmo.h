#ifndef __GIZMO_H__
#define __GIZMO_H__
#include "Globals.h"
#include "Glew/include/GL/glew.h"
class Gizmo
{

public:
  int size = 10;
  Gizmo();
  ~Gizmo();
  GLfloat posX, posY, posZ;
  void setPosition(GLfloat posX, GLfloat posY, GLfloat posZ);
  void draw();
};

#endif
