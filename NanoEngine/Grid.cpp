#include "Grid.h"

Grid::Grid()
{
	posX = 0.0f;
	posY = 0.0f;
	posZ = 0.0f;
}

Grid::~Grid()
{
}

void Grid::setColor(GLfloat red, GLfloat green, GLfloat blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

void Grid::setPosition(GLfloat posX, GLfloat posY, GLfloat posZ)
{
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
}

void Grid::draw()
{
  glPushMatrix();
	glTranslatef(posX,posY,posZ);
	//glRotatef(30.0f, 1.0f, 0.0f, 0.0f);


	glBegin(GL_LINES);
	for (int i = -size/2; i <= size/2; i++) {

		glColor3f(0, 255, 0);

		glVertex3f(i, 0, -size/2);
		glVertex3f(i, 0, size/2);

		glVertex3f(size / 2, 0, i);
		glVertex3f(-size / 2, 0, i);
	};
	glEnd();
  glPopMatrix();
}