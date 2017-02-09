#ifndef __SOLID_SPHERE_H__
#define __SOLID_SPHERE_H__
#include "Globals.h"
#include "Glew/include/GL/glew.h"
#include <vector>


class SolidSphere
{
public:
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	std::vector<GLushort> indices;

	SolidSphere(float radius, unsigned int rings, unsigned int sectors);
	~SolidSphere();

	void draw(GLfloat x, GLfloat y, GLfloat z);
private:

	bool buffersInitFlag = false;

};

#endif