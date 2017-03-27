#include "ComponentMesh.h"
#include "GameObject.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "assimp/include/assimp/cimport.h"
#include "assimp/include/assimp/postprocess.h"
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"

ComponentMesh::ComponentMesh()
{
  type = MESH;
  active = true;
  my_go = nullptr;
}

ComponentMesh::~ComponentMesh()
{

}

void ComponentMesh::CreateMesh(aiNode * aiNode, GameObject* node, const aiScene* scene) {
  for (int i = 0; i < aiNode->mNumMeshes; i++)
  {
    int meshId = aiNode->mMeshes[i];
    meshesId.push_back(meshId);
   
    aiMesh* meshScene = scene->mMeshes[meshId];

    MeshLevel  mesh = MeshLevel();
    mesh.vertices = meshScene->mVertices;
    mesh.num_vertices = meshScene->mNumVertices;
    mesh.tex_coords = meshScene->mTextureCoords[0];
    mesh.normals = meshScene->mNormals;
    mesh.material = meshScene->mMaterialIndex;
    mesh.meshId = meshId;

    //Buffer vertices
    glGenBuffers(1, (GLuint*) &(mesh.verticesId));
    glBindBuffer(GL_ARRAY_BUFFER, mesh.verticesId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh.num_vertices, mesh.vertices, GL_STATIC_DRAW);

    //Buffer normals
    if (mesh.normals) {
      glGenBuffers(1, (GLuint*) &(mesh.normalsId));
      glBindBuffer(GL_NORMAL_ARRAY, mesh.normalsId);
      glBufferData(GL_NORMAL_ARRAY, sizeof(aiVector3D) * mesh.normals->Length(), mesh.normals, GL_STATIC_DRAW);
    }

    //indices
    for (int x = 0; x < meshScene->mNumFaces; x++)
    {
      mesh.indices.push_back(meshScene->mFaces[x].mIndices[0]);
      mesh.indices.push_back(meshScene->mFaces[x].mIndices[1]);
      mesh.indices.push_back(meshScene->mFaces[x].mIndices[2]);
    }

    //Buffer Indices
    glGenBuffers(1, (GLuint*) &(mesh.indicesId));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indicesId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * mesh.indices.size(), &mesh.indices[0], GL_STATIC_DRAW);


    mesh.num_indices = mesh.indices.size();
    meshes.push_back(mesh); // add mesh to level
  }
}
