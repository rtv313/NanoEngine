#include "Globals.h"
#include "ModuleScene.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "assimp/include/assimp/cimport.h"
#include "assimp/include/assimp/postprocess.h"
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"

#pragma comment(lib, "assimp/lib/assimp.lib")

ModuleScene::ModuleScene()
{
  
}

ModuleScene::~ModuleScene()
{

}

bool ModuleScene::Init()
{

  return true;
}

update_status ModuleScene::PreUpdate()
{

  return UPDATE_CONTINUE;
}

update_status ModuleScene::Update()
{
  for (int i = 0; i < game_objects.size(); ++i) {
    game_objects[i]->Update();
  }
  return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate()
{

  return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{

  return true;
}

void ModuleScene::Draw()
{
  for (int i = 0; i < game_objects.size(); ++i) {
    DrawNodes(game_objects[i]);
  }
}

bool ModuleScene::LoadModel(std::string file)
{
  std::string directory = file.substr(0, file.find_last_of('/'));
  Uint32 flags;// = aiProcess_PreTransformVertices;
  //flags |= aiProcess_FlipUVs;
  flags |= aiProcess_Triangulate;
  const char * c = file.c_str();
  scene = aiImportFile(c, flags);

  GameObject* root;
  root = CreateGameObjects(nullptr, scene->mRootNode);

  game_objects.push_back(root);

  return true;
}

GameObject * ModuleScene::CreateGameObjects(GameObject * father, aiNode* currentNode)
{
  GameObject* node = new GameObject();
  node->active = true;
  // crear nuevo nodo 
  if (father == nullptr) { // si no existe se le accina al root 
    ComponentTransform* ct = (ComponentTransform*) node->CreateComponent(TRANSFORM);
    ct->transform = currentNode->mTransformation;
    node->components.push_back(ct);
  }
  else {
    node->parent = father;
    ComponentTransform* ct = (ComponentTransform*)node->CreateComponent(TRANSFORM);
    ComponentTransform* ctFather = (ComponentTransform*) father->FindComponentByType(TRANSFORM);
    ct->transform = currentNode->mTransformation * ctFather->transform;
    node->components.push_back(ct);
  }

  ComponentMesh* cm = (ComponentMesh*)node->CreateComponent(MESH);
  cm->CreateMesh(currentNode, node, scene); // create Meshes
  node->components.push_back(cm);

  ComponentMaterial* cmat = (ComponentMaterial*)node->CreateComponent(MATERIAL);
  cmat->CreateMaterial(currentNode, node, scene); // create Meshes
  node->components.push_back(cmat);

  for (int i = 0; i < currentNode->mNumChildren; i++)
  {
    node->children.push_back(CreateGameObjects(node, currentNode->mChildren[i]));
  }

  return node;
}

void ModuleScene::DrawNodes(GameObject* node) {

  ComponentMesh* cm = (ComponentMesh*) node->FindComponentByType(MESH);
  if (cm == nullptr) return;
  std::vector<MeshLevel> meshes = cm->meshes;

  ComponentMaterial* cmat = (ComponentMaterial*)node->FindComponentByType(MATERIAL);
  if (cmat == nullptr) return;

  for (int i = 0; i < meshes.size(); i++)
  {
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    glPushMatrix();
    glFrontFace(GL_CW);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, meshes[cm->meshesId[i]].verticesId);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[cm->meshesId[i]].indicesId);

    glBindBuffer(GL_NORMAL_ARRAY, meshes[cm->meshesId[i]].normalsId);
    glNormalPointer(GL_FLOAT, 0, NULL);

    glBindTexture(GL_TEXTURE_2D, 0);

    //Materials
    GLfloat ambient[] = { cmat->material.ambient.r, cmat->material.ambient.g, cmat->material.ambient.b, cmat->material.ambient.a };
    GLfloat diffuse[] = { cmat->material.diffuse.r, cmat->material.diffuse.g, cmat->material.diffuse.b, cmat->material.diffuse.a };
    GLfloat specular[] = { cmat->material.specular.r, cmat->material.specular.g, cmat->material.specular.b, cmat->material.specular.a };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &(cmat->material.ambient.r));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &(cmat->material.diffuse.r));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &(cmat->material.specular.r));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, cmat->material.shiness);

    if (cmat->texturesIds.size() > 0) {
      glBindBuffer(GL_ARRAY_BUFFER, cmat->textureCoordinatesId);
      glTexCoordPointer(2, GL_FLOAT, 0, NULL);

      for (int i = 0; i < cmat->texturesIds.size(); i++)
      {
        glTexCoordPointer(2, GL_FLOAT, 0, NULL);
        glBindTexture(GL_TEXTURE_2D, cmat->texturesIds[i]);
      }
    }

    //glEnable(GL_NORMALIZE);
    int numFaces = scene->mMeshes[meshes[cm->meshesId[i]].meshId]->mNumFaces;
    glDrawElements(GL_TRIANGLES, numFaces * 3, GL_UNSIGNED_INT, NULL);
  }

  glBindTexture(GL_TEXTURE_2D, 0); // Reset clear
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glPopMatrix();

  for (int x = 0; x < node->children.size(); x++)
  {
    DrawNodes(node->children[x]);
  }

  glDisable(GL_LIGHTING);
}
