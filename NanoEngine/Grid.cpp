#include "Grid.h"

Grid::Grid()
{
	posX = 0.0f;
	posY = 0.0f;
	posZ = 0.0f;

	vertices = new GLfloat[size*size * 3]; //x,y,z
	indices = new uint[size*size];
	int componentVertexIndex = 0;
	int id = 0;
	red = 1.0f;
	green = 1.0f;
	blue = 1.0f;

	for (int i = -size / 2; i <= size / 2; i++) {
		
		indices[id] = id; id++;//each vertex is unique
		vertices[componentVertexIndex] = i; componentVertexIndex++;
		vertices[componentVertexIndex] = 0; componentVertexIndex++;
		vertices[componentVertexIndex] = -size / 2; componentVertexIndex++;

		indices[id] = id; id++;
		vertices[componentVertexIndex] = i; componentVertexIndex++;
		vertices[componentVertexIndex] = 0; componentVertexIndex++;
		vertices[componentVertexIndex] = size / 2; componentVertexIndex++;

		indices[id] = id; id++;
		vertices[componentVertexIndex] = size / 2; componentVertexIndex++;
		vertices[componentVertexIndex] = 0; componentVertexIndex++;
		vertices[componentVertexIndex] = i; componentVertexIndex++;

		indices[id] = id; id++;
		vertices[componentVertexIndex] = -size / 2; componentVertexIndex++;
		vertices[componentVertexIndex] = 0; componentVertexIndex++;
		vertices[componentVertexIndex] = i; componentVertexIndex++;

	}

	indicesSize = id--;

	glGenBuffers(1, (GLuint*) &(my_id));
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size*size * 3, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, (GLuint*) &(my_indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indicesSize, indices, GL_STATIC_DRAW);
	
}

Grid::~Grid()
{
	delete vertices;
	delete indices;
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
	glDisable(GL_LIGHTING);
	glColor3f(red, green, blue);
	glPushMatrix();
	glTranslatef(posX, posY, posZ);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	glDrawElements(GL_LINES, indicesSize, GL_UNSIGNED_INT, NULL);
	glDisableClientState(GL_VERTEX_ARRAY); //end draw
	//glEnable(GL_LIGHTING);
  glPopMatrix();
}