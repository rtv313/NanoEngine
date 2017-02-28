#include "Model.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "assimp/include/assimp/cimport.h"
#include "assimp/include/assimp/postprocess.h"
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"

#pragma comment(lib, "assimp/lib/assimp.lib")

Mesh::Mesh() 
{

}

Mesh::Mesh(const aiScene* scene,GLuint meshIndex, GLuint textureId,std::string directory):textureId(textureId),directory(directory)
{
	//Material Index
	materialIndex = scene->mMeshes[meshIndex]->mMaterialIndex;

	//Vertices Buffer
	glGenBuffers(1, (GLuint*) &(verticesId));
	glBindBuffer(GL_ARRAY_BUFFER, verticesId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * scene->mMeshes[meshIndex]->mNumVertices * 3, scene->mMeshes[meshIndex]->mVertices, GL_STATIC_DRAW);

	//Indices Buffer we get all indices for each face in the mesh
	numFaces = scene->mMeshes[meshIndex]->mNumFaces;

	for (int x = 0; x < numFaces; x++)
	{
		indices.push_back(scene->mMeshes[meshIndex]->mFaces[x].mIndices[0]);
		indices.push_back(scene->mMeshes[meshIndex]->mFaces[x].mIndices[1]);
		indices.push_back(scene->mMeshes[meshIndex]->mFaces[x].mIndices[2]);
	}
	
	glGenBuffers(1, (GLuint*) &(indicesId));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	//Normals Buffer
	glGenBuffers(1, (GLuint*) &(normalsId));
	glBindBuffer(GL_NORMAL_ARRAY, normalsId);
	glBufferData(GL_NORMAL_ARRAY, sizeof(aiVector3D) * scene->mMeshes[meshIndex]->mNormals->Length(), scene->mMeshes[meshIndex]->mNormals, GL_STATIC_DRAW);


	//UV Buffer, capture only uvs from mtexture 

	if (scene->mMeshes[meshIndex]->mTextureCoords[0]) {

		for (int i = 0; i < scene->mMeshes[meshIndex]->mNumVertices; i++) {

			uvs.push_back(scene->mMeshes[meshIndex]->mTextureCoords[0][i].x);
			uvs.push_back(scene->mMeshes[meshIndex]->mTextureCoords[0][i].y);
		}

		glGenBuffers(1, (GLuint*) &(textureCoordinatesId));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureCoordinatesId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat) * uvs.size(), &uvs[0], GL_STATIC_DRAW);
	}

	
	if (scene->mMeshes[meshIndex]->mMaterialIndex >= 0) {
		GLuint  materialIndex = scene->mMeshes[meshIndex]->mMaterialIndex;
		aiMaterial* mat = scene->mMaterials[materialIndex];
		aiString str;
		// Load materials


		// Load diffuse textures
		for (int i = 0; i < mat->GetTextureCount(aiTextureType_DIFFUSE); i++)
		{
			mat->GetTexture(aiTextureType_DIFFUSE, i, &str);
			texturesIds.push_back(App->textures->Load(str.C_Str(), directory));
		}
		//Load specular textures
		for (int i = 0; i < mat->GetTextureCount(aiTextureType_SPECULAR); i++)
		{
			mat->GetTexture(aiTextureType_SPECULAR, i, &str);
			texturesIds.push_back(App->textures->Load(str.C_Str(), directory));
		}
		//Load normals textures
		for (int i = 0; i < mat->GetTextureCount(aiTextureType_NORMALS); i++)
		{
			mat->GetTexture(aiTextureType_NORMALS, i, &str);
			texturesIds.push_back(App->textures->Load(str.C_Str(), directory));
		}
	}

	indices.clear();
	uvs.clear();

}

Mesh::~Mesh()
{

}


void Mesh::draw() 
{
	glPushMatrix();


	glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, verticesId);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);

		glBindBuffer(GL_NORMAL_ARRAY,normalsId);
		glNormalPointer(GL_FLOAT, 0, NULL);

		glBindTexture(GL_TEXTURE_2D, 0);

		if (texturesIds.size() > 0) {
			glBindBuffer(GL_ARRAY_BUFFER, textureCoordinatesId);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			for (int i = 0; i < texturesIds.size(); i++)
			{
				glTexCoordPointer(2, GL_FLOAT, 0, NULL);
				glBindTexture(GL_TEXTURE_2D, texturesIds[i]);
			}
		}

	

		glDrawElements(GL_TRIANGLES, numFaces*3, GL_UNSIGNED_INT, NULL);
		glBindTexture(GL_TEXTURE_2D, 0); // Reset clear
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glPopMatrix();

}




Model::Model() 
{
}



Model::Model(std::string file)
{
	position = {0,0,0};
	scale = { 1,1,1 };
	rotation = { 0,0,0 };
	
	directory = file.substr(0, file.find_last_of('/'));
	Uint32 flags = aiProcess_PreTransformVertices;
	flags |= aiProcess_FlipUVs;
	flags |= aiProcess_Triangulate;
	const char * c = file.c_str();
	scene = aiImportFile(c, flags);

	// set meshes
	for (int i = 0; i < scene->mNumMeshes; i++) 
	{
		meshes.push_back(Mesh(scene,i,1,directory));
	}


}


Model::~Model()
{
}



void Model::clear() 
{
	meshes.clear();
}

void Model::draw()
{	

	//glColor3f(1, 1, 1);
	



	
	

	/*GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);*/
	glEnable(GL_COLOR_MATERIAL);

	GLfloat ambient[] = { 0.3, 0.0, 0.0, 1.0 };

	GLfloat diffuse[] = { 0.6, 0.60, 0.6, 1.0 };

	GLfloat specular[] = { 0.8, 0.6, 0.6, 1.0 };

	GLfloat shininess = 1.0; /* [0..128] */

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	glMaterialf(GL_FRONT, GL_SHININESS, shininess);


	//scene->mMeshes[i]->mFaces[x].mIndices[0]
	for (int i = 0; i < scene->mNumMeshes; i++)
	{

		meshes[i].draw();
		glColor3f(1, 0, 0);
		/*glBegin(GL_LINES);
			for (int x = 0; x < scene->mMeshes[i]->mNumFaces; x++){
				glVertex3f(scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[0]].x,
						scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[0]].y, 
						scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[0]].z);

				glVertex3f(scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[0]].x + scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[x].mIndices[0]].x,
						scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[0]].y + scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[x].mIndices[0]].y,
						scene->mMeshes[i]->mVertices[scene->mMeshes[i]->mFaces[x].mIndices[0]].z + scene->mMeshes[i]->mNormals[scene->mMeshes[i]->mFaces[x].mIndices[0]].z);
			}
		glEnd();*/
		glColor3f(1, 1, 1);
	}



	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
}

