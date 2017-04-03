#ifndef __COMPONENT_MATERIAL_H__
#define __COMPONENT_MATERIAL_H__

#include "assimp/include/assimp/scene.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include <vector>
#include "Globals.h"
#include "Component.h"
#include "Glew/include/GL/glew.h"
#include "DevIL/include/IL/il.h"

struct Material
{
  aiColor4D ambient = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
  aiColor4D diffuse = aiColor4D(1.0f, 1.0f, 1.0f, 1.0f);
  aiColor4D specular = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
  float shiness = 0.0f;
};

class ComponentMaterial : public Component
{
public:
  ComponentMaterial();
  ~ComponentMaterial();
  void CreateMaterial(aiNode * aiNode, GameObject* node, const aiScene* scene);

  GLuint textureCoordinatesId;
  GLuint textureId;
  GLuint materialIndex;
  std::string directory;
  std::vector<uint> texturesIds;
  std::vector<GLfloat> uvs;
  Material material;
};

#endif