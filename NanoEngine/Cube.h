#ifndef __CUBE_H__
#define __CUBE_H__
#include "Globals.h"
#include "Glew/include/GL/glew.h"
class Cube
{
public:
	GLfloat posX, posY, posZ;
	GLuint tex;
	Cube();
	~Cube();
	void setColor(GLfloat red, GLfloat green , GLfloat blue);
	void setPosition(GLfloat posX, GLfloat posY, GLfloat posZ);
	void draw();

private:
	GLfloat red, green, blue;
	bool buffersInitFlag = false;
	uint my_id = 0;
	uint my_indices = 0;
	uint my_textIndex = 0;
	GLfloat vertices[24] = {
		-0.5f, -0.5f, 0.5f, // A
		0.5f, -0.5f, 0.5f, // B
		-0.5f, 0.5f, 0.5f, // C
		0.5f, 0.5f, 0.5f, // D
		-0.5f, -0.5f, -0.5f,//E
		0.5f, -0.5f, -0.5f, // F
		-0.5f, 0.5f, -0.5f,//G
		0.5f, 0.5f, -0.5f, // H
	};
	GLfloat UV[16] = {
		0.0f,0.0f,//A
		1.0f,0.0f,//B
		0.0f,1.0f,//C
		1.0f,1.0f,//D
		1.0f,0.0f,//E
		0.0f,0.0f,//F
		1.0f,1.0f,//G
		0.0f,1.0f//H
	};
	uint indices[36] = { 
		0,1,2,
		1,3,2,
		5,7,3,
		3,1,5,
		4,6,7,
		4,7,5,
		2,6,4,
		4,0,2,
		6,2,3,
		7,6,3,
		0,4,1,
		4,5,1 };
	
};


#endif