#include "Model.h"
#include "SDL/include/SDL.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"




#pragma comment(lib, "assimp/lib/assimp.lib")

Model::Model()
{
	position = {0,0,0};
	scale = { 1,1,1 };
	rotation = { 0,0,0 };
}


Model::~Model()
{
}

void Model::Load(const char* file)
{
	Uint32 flags = aiProcess_PreTransformVertices;
	flags |= aiProcess_FlipUVs;
	scene = aiImportFile(file, flags);

	uint vertexNumber;
 
	my_id=  new uint[scene->mNumMeshes]();
	my_indices = new uint[scene->mNumMeshes]();
	my_normals = new uint[scene->mNumMeshes]();
	my_textIndex = new uint[scene->mNumMeshes]();
	ILboolean success;			// Create a flag to keep track of success/failure
	ILenum error;
	ilGenImages(1, &imageID); 		// Generate the image ID
	ilBindImage(imageID); 			// Bind the image
	success = ilLoad(IL_PNG, "TestImages/Lenna.png");

	if (!success)
	{
		error = ilGetError();
		std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		exit(-1);
	}

	success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
	pixmap = ilGetData();

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


	for (int i = 0; i < scene->mNumMeshes; i++) 
	{
		//Vertices Buffer
		glGenBuffers(1, (GLuint*) &(my_id[i]));
		glBindBuffer(GL_ARRAY_BUFFER,my_id[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * scene->mMeshes[i]->mNumVertices * 3, scene->mMeshes[i]->mVertices, GL_STATIC_DRAW);

		//Normals Buffer
		glGenBuffers(1, (GLuint*) &(my_normals[i]));
		glBindBuffer(GL_NORMAL_ARRAY, my_normals[i]);
		glBufferData(GL_NORMAL_ARRAY, sizeof(aiVector3D) * scene->mMeshes[i]->mNormals->Length(),scene->mMeshes[i]->mNormals, GL_STATIC_DRAW);

		//UVs
		glGenBuffers(1, (GLuint*) &(my_textIndex[i]));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_textIndex[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(aiVector3D) * scene->mMeshes[i]->mTextureCoords[0]->Length(), scene->mMeshes[i]->mTextureCoords[0], GL_STATIC_DRAW);
		
		for (int x = 0; x < scene->mMeshes[i]->mNumFaces; x++) 
		{
			indices.push_back(scene->mMeshes[i]->mFaces[x].mIndices[0]);
			indices.push_back(scene->mMeshes[i]->mFaces[x].mIndices[1]);
			indices.push_back(scene->mMeshes[i]->mFaces[x].mIndices[2]);
		}
		
		glGenBuffers(1, (GLuint*) &(my_indices[i]));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indices.size(), &indices[0], GL_STATIC_DRAW);

		

		indices.clear();
	}

}

void Model::Clear() 
{

}

void Model::Draw()
{	
	glColor3f(255, 255, 255);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	GLfloat light_difusse[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat light_position[4] = { 0.0f,5.0f,0.0f,0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_difusse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, my_id[i]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices[i]);

		glBindBuffer(GL_NORMAL_ARRAY, my_normals[i]);
		glNormalPointer(GL_FLOAT,0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, my_textIndex[i]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		glBindTexture(GL_TEXTURE_2D, 2);
		
		glDrawElements(GL_TRIANGLES, scene->mMeshes[i]->mNumFaces * 3, GL_UNSIGNED_INT, NULL);
		

	}
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY); //end draw

}