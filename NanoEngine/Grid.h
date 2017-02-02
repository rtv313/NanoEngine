#ifndef __PLANE_H__
#define __PLANE_H__
#include "Globals.h"
#include "Glew/include/GL/glew.h"
class Grid
{

public:
	int size = 10;
	Grid();
	~Grid();
	GLfloat posX, posY, posZ;
	void setColor(GLfloat red, GLfloat green, GLfloat blue);
	void setPosition(GLfloat posX, GLfloat posY, GLfloat posZ);
	void draw();
private:
	GLfloat red, green, blue;
};

#endif