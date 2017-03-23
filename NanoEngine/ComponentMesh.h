#ifndef __COMPONENT_MESH_H__
#define __COMPONENT_MESH_H__

#include "assimp/include/assimp/scene.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include <vector>
#include "Globals.h"
#include "Component.h"
#include "Glew/include/GL/glew.h"
#include "DevIL/include/IL/il.h"

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

class ComponentMesh : public Component
{
public:
  ComponentMesh();
  ~ComponentMesh();

  std::vector<unsigned> meshesId;
  std::vector<MeshLevel> meshes;

  void CreateMesh(aiNode * aiNode, GameObject* node, const aiScene* scene);
};

#endif