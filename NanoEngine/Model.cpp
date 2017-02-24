#include "Model.h"
#include "SDL/include/SDL.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
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

	for (int i = 0; i < scene->mMeshes[meshIndex]->mNumVertices;i++) {
		uvs.push_back(scene->mMeshes[meshIndex]->mTextureCoords[0][i].x);
		uvs.push_back(scene->mMeshes[meshIndex]->mTextureCoords[0][i].y);
	}

	glGenBuffers(1, (GLuint*) &(textureCoordinatesId));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureCoordinatesId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat) * uvs.size(), &uvs[0], GL_STATIC_DRAW);

	GLuint  materialIndex = scene->mMeshes[meshIndex]->mMaterialIndex;
	aiMaterial* mat = scene->mMaterials[materialIndex];
	aiString str;

	
	// Load diffuse textures
	for (int i = 0; i < mat->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		mat->GetTexture(aiTextureType_DIFFUSE, i, &str);
		texturesIds.push_back(TextureFromFile(str.C_Str(), directory));
	}
	//Load specular textures
	for (int i = 0; i < mat->GetTextureCount(aiTextureType_SPECULAR); i++)
	{
		mat->GetTexture(aiTextureType_SPECULAR, i, &str);
		texturesIds.push_back(TextureFromFile(str.C_Str(), directory));
	}
	//Load normals textures
	for (int i = 0; i < mat->GetTextureCount(aiTextureType_NORMALS); i++)
	{
		mat->GetTexture(aiTextureType_NORMALS, i, &str);
		texturesIds.push_back(TextureFromFile(str.C_Str(), directory));
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

	glColor3f(255, 255, 255);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, verticesId);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);

		glBindBuffer(GL_NORMAL_ARRAY,normalsId);
		glNormalPointer(GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, textureCoordinatesId);
		//glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		for (int i = 0; i < texturesIds.size(); i++) 
		{
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glBindTexture(GL_TEXTURE_2D,texturesIds[i]);
		}
		

		glDrawElements(GL_TRIANGLES, numFaces * 3, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glPopMatrix();

}

GLuint Mesh::TextureFromFile(const char* path, std::string directory)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	ILuint imageId;
	ILboolean success;			// Create a flag to keep track of success/failure
	ILenum error;				// Create a flag to keep track of the IL error state
	ilGenImages(1, &imageId); 		// Generate the image ID
	ilBindImage(imageId); 			// Bind the image

	success = ilLoadImage(filename.c_str());

	if (!success)
	{
		error = ilGetError();
		std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		exit(-1);
	}
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	ILubyte * pixmap = ilGetData();

	//Generate Texture
	GLuint textureID;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureID);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, pixmap);
	glGenerateMipmap(GL_TEXTURE_2D);
	// Parameters
	

	ilBindImage(0);
	ilDeleteImage(imageId);

	return textureID;
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

	glColor3f(255, 255, 255);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);


	GLfloat light_difusse[4] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat light_position[4] = { 0.0f,5.0f,0.0f,0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_difusse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	

	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		meshes[i].draw();
	}

	glDisable(GL_CULL_FACE);
}

