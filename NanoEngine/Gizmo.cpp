#include "Gizmo.h"

Gizmo::Gizmo()
{
  posX = -3.0f;
  posY = -3.0f;
  posZ = -15.0f;
}

Gizmo::~Gizmo()
{
}

void Gizmo::setPosition(GLfloat posX, GLfloat posY, GLfloat posZ)
{
  this->posX = posX;
  this->posY = posY;
  this->posZ = posZ;
}

void Gizmo::draw()
{
  glPushMatrix();

  glTranslatef(posX, posY, posZ);

  glBegin(GL_LINES);
    // X Axis
    glColor3f(255.0f, 0.0f, 0.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);

    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, 0.1f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, -0.1f, 0.0f);

    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, 0.0f, 0.1f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.8f, 0.0f, -0.1f);

    // Y Axis
    glColor3f(0.0f, 255.0f, 0.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.1f, 0.8f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.1f, 0.8f, 0.0f);

    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.8f, 0.1f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.8f, -0.1f);

    // Z Axis
    glColor3f(0.0f, 0.0f, 255.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);

    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.1f, 0.8f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, -0.1f, 0.8f);

    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.1f, 0.0f, 0.8f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.1f, 0.0f, 0.8f);

  glEnd();

  glPopMatrix();
}
