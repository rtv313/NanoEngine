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
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);

  float  spotExponent = 0.0;
  float  spotCutoff = 180.0f;
  float  constantAttenuation = 1.0;
  float  linearAttenuation = 0.0;
  float  quadraticAttenuation = 0.0;

  GLfloat light_difusse[] = { 1.0f,1.0f,1.0f,1.0f };
  GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_difusse);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, constantAttenuation);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, linearAttenuation);
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);

  GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

  //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);

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
  GLfloat light_position[] = { 0.0f,1.0f,0.0f,0.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  return UPDATE_CONTINUE;
}

bool ModuleLighting::CleanUp()
{

  return true;
}
