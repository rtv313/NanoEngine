#include "ComponentMaterial.h"
#include "Application.h"
#include "ModuleTextures.h"

ComponentMaterial::ComponentMaterial()
{
  type = MATERIAL;
  active = true;
  my_go = nullptr;
}

ComponentMaterial::~ComponentMaterial()
{

}

void ComponentMaterial::CreateMaterial(aiNode * aiNode, GameObject* node, const aiScene* scene) {
  for (int i = 0; i < aiNode->mNumMeshes; i++)
  {
    materialIndex = scene->mMeshes[i]->mMaterialIndex;

    if (scene->mMeshes[i]->mTextureCoords[0]) {

      for (int j = 0; j < scene->mMeshes[i]->mNumVertices; j++) {

        uvs.push_back(scene->mMeshes[i]->mTextureCoords[0][j].x);
        uvs.push_back(scene->mMeshes[i]->mTextureCoords[0][j].y);
      }

      glGenBuffers(1, (GLuint*) &(textureCoordinatesId));
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureCoordinatesId);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat) * uvs.size(), &uvs[0], GL_STATIC_DRAW);
    }


    if (scene->mMeshes[i]->mMaterialIndex >= 0) {
      GLuint  materialIndex = scene->mMeshes[i]->mMaterialIndex;
      aiMaterial* mat = scene->mMaterials[materialIndex];
      aiString str;
      // Load materials

      mat->Get(AI_MATKEY_COLOR_AMBIENT, material.ambient);
      mat->Get(AI_MATKEY_COLOR_DIFFUSE, material.diffuse);
      mat->Get(AI_MATKEY_COLOR_SPECULAR, material.specular);
      mat->Get(AI_MATKEY_SHININESS, material.shiness);


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
  }
  uvs.clear();
}

