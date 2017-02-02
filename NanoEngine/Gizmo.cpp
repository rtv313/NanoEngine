#include "Gizmo.h"

Gizmo::Gizmo()
{
  posX = -5.0f;
  posY = 0.0f;
  posZ = -20.0f;
}

Gizmo::~Gizmo()
{
}

void Gizmo::setColor(GLfloat red, GLfloat green, GLfloat blue)
{
  this->red = red;
  this->green = green;
  this->blue = blue;
}

void Gizmo::setPosition(GLfloat posX, GLfloat posY, GLfloat posZ)
{
  this->posX = posX;
  this->posY = posY;
  this->posZ = posZ;
}

void Gizmo::draw()
{
  glTranslatef(posX, posY, posZ);
  glRotatef(30.0f, 1.0f, 0.0f, 0.0f);


  glBegin(GL_LINES);
  for (int i = 0; i <= size; i++) {

    glColor3f(0, 255, 0);

    glVertex3f(i, 0, 0);
    glVertex3f(i, 0, size);

    glVertex3f(0, 0, i);
    glVertex3f(size, 0, i);
  };
  glEnd();
}
