#include "Cube.h"

#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"
#include <iostream>
using namespace std;
# include <cstdlib>
 Cube::Cube() 
 {
	 posX = 0.0f;
	 posY = 0.0f;
	 posZ = 0.0f;
	 red = 255.0f;
	 green = 0.0f;
	 blue = 0.0f;

	 glGenBuffers(1, (GLuint*) &(my_id));
	 glBindBuffer(GL_ARRAY_BUFFER, my_id);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16 * 3, vertices, GL_STATIC_DRAW); 

	 glGenBuffers(1, (GLuint*) &(my_indices));
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 48, indices, GL_STATIC_DRAW);
	 

	 GLfloat UV2[32] = {
		 0.0f,0.0f,//A
		 0.0f,1.0f,//B
		 1.0f,0.0f,//C
		 1.0f,1.0f,//D
		 0.0f,1.0f,//E
		 0.0f,0.0f,//F
		 1.0f,1.0f,//G
		 1.0f,0.0f,//H

		 1.0f,1.0f, //H2
		 0.0f,1.0f,// G2
		 1.0f,0.0f,// D2
		 0.0f,0.0f, // C2

		 0.0f,0.0f, //A2
		 0.0f,1.0f,// E2
		 1.0f,0.0f,// B2
		 1.0f,1.0f // F2

	 };

	 glGenBuffers(1, (GLuint*) &(my_textIndex));
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_textIndex);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat) * 32, UV2, GL_STATIC_DRAW);

	 for (int i = 0; i < 128; i++) {
		 for (int j = 0; j < 128; j++) {
			 int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			 checkImage[i][j][0] = (GLubyte)c;
			 checkImage[i][j][1] = (GLubyte)c;
			 checkImage[i][j][2] = (GLubyte)c;
			 checkImage[i][j][3] = (GLubyte)255;
		 }
	 }

	
	 
	

				// Create an image ID as a ULuint



	 ILboolean success;			// Create a flag to keep track of success/failure

	 ILenum error;				// Create a flag to keep track of the IL error state

	 ilGenImages(1, &imageID); 		// Generate the image ID

	 ilBindImage(imageID); 			// Bind the image

	 success = ilLoad(IL_PNG,"TestImages/Lenna.png");
	// success = ilLoad(IL_TGA,"3DModels/Batman/Batman_Torso_D.tga");

	 if (!success)
	 {
		 error = ilGetError();
		 std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		 exit(-1);
	 }

	 success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

	
	
	 pixmap =  ilGetData();

	 glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	 glGenTextures(1, &ImageName);
	 glBindTexture(GL_TEXTURE_2D, ImageName);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	 glGenerateMipmap(GL_TEXTURE_2D);


	 glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
		 0,				// Pyramid level (for mip-mapping) - 0 is the top level
		 ilGetInteger(IL_IMAGE_FORMAT),	// Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
		 ilGetInteger(IL_IMAGE_WIDTH),	// Image width
		 ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
		 0,				// Border width in pixels (can either be 1 or 0)
		 ilGetInteger(IL_IMAGE_FORMAT),	// Format of image pixel data
		 GL_UNSIGNED_BYTE,		// Image data type
		 pixmap);




}
 Cube::~Cube() {
	 ilDeleteImages(1, &imageID);
 }

 void Cube::draw() 
 {
	 glPushMatrix();
	 glColor3f(255, 255, 255);
	 glTranslatef(posX, posY, posZ);

	 
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixmap);
		
	//UV-texturea arrays binding
	 glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	 glBindBuffer(GL_ARRAY_BUFFER, my_textIndex);
	 glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	 glBindTexture(GL_TEXTURE_2D, ImageName);
	 

	 glEnableClientState(GL_VERTEX_ARRAY);
	 glBindBuffer(GL_ARRAY_BUFFER, my_id);
	 glVertexPointer(3, GL_FLOAT, 0, NULL);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);

	 glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	 glBindTexture(GL_TEXTURE_2D, 0);
	 
	 glDisableClientState(GL_VERTEX_ARRAY); //end draw
	 glDisableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
	 glPopMatrix();


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
