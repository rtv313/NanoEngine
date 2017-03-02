#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "assimp/include/assimp/scene.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include <vector>
#include "Glew/include/GL/glew.h"
#include "DevIL/include/IL/il.h"
#include "Globals.h"


struct Node 
{
	std::string name;
	aiVector3D position = aiVector3D(0, 0, 0);
	aiQuaternion rotation = aiQuaternion(1, 0, 0, 0);
	std::vector<unsigned> meshes;
	Node* parent = nullptr;
	std::vector<Node*> childs;
	aiNode* nodeAi;
};

struct MeshLevel 
{
	unsigned  material = 0;
	aiVector3D* vertices = nullptr;
	aiVector3D* tex_coords = nullptr;
	aiVector3D* normals = nullptr;
	unsigned num_vertices = 0;
	std::vector<unsigned> indices;
	unsigned num_indices = 0;
	unsigned verticesId = 0;
	unsigned indicesId = 0;
	unsigned normalsId = 0;
	int meshId = 0;
};

struct MaterialLevel 
{
	aiColor4D ambient = aiColor4D(1.0f,1.0f,1.0f,1.0f);
	aiColor4D diffuse = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
	aiColor4D specular = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
	float shiness = 0.0f;
	unsigned texture = 0;
};

class Level {

public:
	Node* root = nullptr;
	std::vector<MeshLevel> meshes;
	std::vector<MaterialLevel> materials;
	const aiScene* scene;

	Level();
	Level(std::string file);
	~Level();

	void Draw();
	void Clear();

	unsigned GetNumMeshes() const { return meshes.size(); }
	unsigned GetNumMaterials() const { return materials.size(); }

	MeshLevel& GetMesh(unsigned index) { return meshes[index]; }
	const MeshLevel& GetMesh(unsigned index) const { return meshes[index]; }

	MaterialLevel&  GetMaterial(unsigned index) { return materials[index]; }
	const MaterialLevel& GetMaterial(unsigned index) const { return materials[index]; }

	Node* GetRootNode() { return root; }
	const Node* GetRootNode()const { return root; }

	Node* FindNode(const char* name);
	void LinkNode(Node* node, Node* destination);

	void CreateMesh(aiNode * aiNode, Node* nodee);
	Node* CreateNodes(Node*father, aiNode* node);
	void CreateMaterials();
	void ClearNodes(Node * node);
	void DrawNodes(Node* node);

private:
	std::string directory;
};

#endif 

