#include "Model.h"
#include "SDL/include/SDL.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include "Glew/include/GL/glew.h"
//#include "Globals.h"



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
	for (int i = 0; i < scene->mNumMeshes; i++) 
	{
		glGenBuffers(1, (GLuint*) &(my_id[i]));
		glBindBuffer(GL_ARRAY_BUFFER,my_id[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * scene->mMeshes[i]->mNumVertices * 3, scene->mMeshes[i]->mVertices, GL_STATIC_DRAW);


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
	//glBegin(GL_TRIANGLES);
	//for (int i = 0; i < scene->mNumMeshes; i++) 
	//{

	//	for (int x = 0; x < scene->mMeshes[i]->mNumFaces; x++) 
	//	{
	//		glVertex3f(scene->mMeshes[i]->mVertices[ scene->mMeshes[i]->mFaces[x].mIndices[0] ].x, scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[0]].y,scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[0]].z);
	//		glVertex3f(scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[1]].x, scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[1]].y, scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[1]].z);
	//		glVertex3f(scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[2]].x, scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[2]].y, scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[2]].z);
	//	}

	//}

	//glEnd();

	glEnableClientState(GL_VERTEX_ARRAY);
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
	glBindBuffer(GL_ARRAY_BUFFER, my_id[i]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices[i]);
	glDrawElements(GL_TRIANGLES, scene->mMeshes[i]->mNumFaces*3, GL_UNSIGNED_INT, NULL);
}
	glDisableClientState(GL_VERTEX_ARRAY); //end draw
}