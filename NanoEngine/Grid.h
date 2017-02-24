#ifndef __PLANE_H__
#define __PLANE_H__
#include "Globals.h"
#include "Glew/include/GL/glew.h"
class Grid
{

public:
	int size = 100;
	Grid();
	~Grid();
	GLfloat posX, posY, posZ;
	void setColor(GLfloat red, GLfloat green, GLfloat blue);
	void setPosition(GLfloat posX, GLfloat posY, GLfloat posZ);
	void draw();
private:
	GLfloat red =1, green=1, blue=1;
	uint my_id = 0;
	uint my_indices = 0;
	GLfloat * vertices;
	uint * indices;
	uint indicesSize=0;
};

#endif