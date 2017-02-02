#include "Cube.h"

 Cube::Cube() 
 {
	 posX = 0.0f;
	 posY = 0.0f;
	 posZ = -5.0f;
	 red = 255.0f;
	 green = 0.0f;
	 blue = 0.0f;
 }
 Cube::~Cube() {}

 void Cube::draw() 
 {
	 if (buffersInitFlag == false) { // init buffers once
		 glGenBuffers(1, (GLuint*) &(my_id));
		 glBindBuffer(GL_ARRAY_BUFFER, my_id);
		 glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, vertices, GL_STATIC_DRAW);

		 glGenBuffers(1, (GLuint*) &(my_indices));
		 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
		 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 36, indices, GL_STATIC_DRAW);
		 buffersInitFlag = true;
	 }
	
	 // start draw 
	glColor3f(red, green, blue);
	glTranslatef(posX,posY,posZ);
	glRotatef(45.0f, 1.0f, 1.0f, 0.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	// ... draw other buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY); //end draw

 }
 void Cube::setColor(GLfloat red, GLfloat green, GLfloat blue) 
 {
	 this->red = red;
	 this->green = green;
	 this->blue = blue;
 };
 
 void Cube::setPosition(GLfloat posX, GLfloat posY, GLfloat posZ) 
 {
	 this->posX = posX;
	 this->posY = posY;
	 this->posZ = posZ;
 }
