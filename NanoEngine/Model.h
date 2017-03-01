#ifndef __MODEL_H__
#define __MODEL_H__

#include "assimp/include/assimp/scene.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include <vector>
#include "Glew/include/GL/glew.h"
#include "DevIL/include/IL/il.h"
#include "Globals.h"


<<<<<<< HEAD
struct Material 
{
	aiColor4D ambient = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
	aiColor4D diffuse = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
	aiColor4D specular = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
	float shiness = 0.0f;
};

=======
struct Materials
{
	GLfloat light_ambient[4];
	GLfloat light_diffuse[4];
	GLfloat light_specular[4];
};



>>>>>>> master
class Mesh {
private:
	GLuint verticesId;
	GLuint indicesId;
	GLuint normalsId;
	GLuint textureCoordinatesId;
	GLuint textureId;
	GLuint numFaces;
	GLuint materialIndex;
	std::string directory;
	std::vector<uint> indices;
	std::vector<uint> texturesIds;
	std::vector<GLfloat> uvs;
<<<<<<< HEAD
	Material material;
=======
	Materials materials;
	const aiScene* scene;
>>>>>>> master

public:
	Mesh(const aiScene* scene,GLuint meshIndex,GLuint textureId,std::string directory);
	Mesh();
	~Mesh();
	
	void draw();

};

class Model
{
	
public:
	Model( std::string file);
	Model();
	~Model();
	void Load(const char* file);
	void clear();
	void draw();

	float3 position;
	float3 scale;
	float3 rotation;

private:
	std::vector<Mesh> meshes;
	const aiScene* scene;
	std::string directory;
	
};


#endif