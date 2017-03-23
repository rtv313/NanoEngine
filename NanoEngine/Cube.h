#ifndef __CUBE_H__
#define __CUBE_H__
#include "Globals.h"
#include "Glew/include/GL/glew.h"
#include "DevIL/include/IL/il.h"
class Cube
{
public:
	GLfloat posX, posY, posZ;
	GLfloat scaleX, scaleY, scaleZ;
	GLuint tex;
	Cube();
	~Cube();
	void setColor(GLfloat red, GLfloat green , GLfloat blue);
	void setPosition(GLfloat posX, GLfloat posY, GLfloat posZ);
	void draw();

private:



	ILubyte  *pixmap;
	ILuint imageID;
	GLuint ImageName;
	GLubyte checkImage[128][128][4];
	GLfloat red, green, blue;
	uint my_id = 0;
	uint my_indices = 0;
	uint my_textIndex = 0;
	GLfloat vertices[48] = {
		-0.5f, -0.5f, 0.5f, // A 0
		0.5f, -0.5f, 0.5f, // B 1
		-0.5f, 0.5f, 0.5f, // C 2
		0.5f, 0.5f, 0.5f, // D 3
		-0.5f, -0.5f, -0.5f,//E 4
		0.5f, -0.5f, -0.5f, // F 5
		-0.5f, 0.5f, -0.5f,//G 6
		0.5f, 0.5f, -0.5f, // H 7

		0.5f, 0.5f, -0.5f, // H 8-2  TOP
	   -0.5f, 0.5f, -0.5f,//  G 9-2
	    0.5f, 0.5f, 0.5f, //  D 10-2
	   -0.5f, 0.5f, 0.5f, //  C 11-2

	   -0.5f, -0.5f, 0.5f, //A 12-2 DOWN
	    0.5f, -0.5f, 0.5f, // B 13-2
	   -0.5f, -0.5f, -0.5f,//E 14-2
	    0.5f, -0.5f, -0.5f, // F 15-2

	};
	
	uint indices[36] = { 
		0,1,2,//ABC  //cada uno de estos es un vertice del triangulo y los tres un triangulo
		1,3,2,//BDC
		5,7,3,//FHD
		3,1,5,//DBF
		4,6,7,//EGH
		4,7,5,//EHF
		2,6,4,//CGE
		4,0,2,//EAC
		//6,2,3,//GCD
		//7,6,3,//HGD
		//0,4,1,//AEB
		//4,5,1,//EFB

		8,9,10, // HGD-2
		9,11,10, // GCD -2

		12,14,13, //AEB-2
		14,15,13 //EFB-2


	}; 
	
};


#endif