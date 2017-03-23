#include "Level.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "assimp/include/assimp/cimport.h"
#include "assimp/include/assimp/postprocess.h"
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"

Level::Level() {}

Level::~Level() {}

Level::Level(std::string file) 
{
	directory = file.substr(0, file.find_last_of('/'));
	Uint32 flags;// = aiProcess_PreTransformVertices;
	flags |= aiProcess_FlipUVs;
	flags |= aiProcess_Triangulate;
	const char * c = file.c_str();
	scene = aiImportFile(c, flags);
	
	CreateNodes(nullptr, scene->mRootNode);


}

void Level::CreateMesh(aiNode * aiNode,Node* node) {

	for (int i = 0; i < aiNode->mNumMeshes; i++)
	{
	
		int meshId = aiNode->mMeshes[i];
		node->meshes.push_back(meshId); // add ids to node 

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

Node* Level::CreateNodes(Node*father,aiNode* actualNode) 
{
	Node* node = new Node();
	// crear nuevo nodo 
	if (father == nullptr) { // si no existe se le accina al root 
		root = node;
		node->nodeAi = actualNode;
		node->position = root->position;
		node->transformMatrix = actualNode->mTransformation;
	}
	else {
		node->parent = father;
		node->nodeAi = actualNode;
		node->position = father->position;
		node->transformMatrix = father->transformMatrix * actualNode->mTransformation;
		node->position = node->transformMatrix * node->position;
		/*node->position.x += actualNode->mTransformation.a4/100;
		node->position.y += actualNode->mTransformation.b4/100;
		node->position.z += actualNode->mTransformation.c4/100;*/
	}

	CreateMesh(node->nodeAi,node); // create Meshes

	for (int i = 0; i < node->nodeAi->mNumChildren; i++) 
	{
		node->childs.push_back(CreateNodes(node,node->nodeAi->mChildren[i]));
	}

	return node;
}

void Level::CreateMaterials() 
{
	for (int i = 0; i < scene->mNumMaterials; i++) 
	{
		MaterialLevel material = MaterialLevel();
		scene->mMaterials[i]->Get(AI_MATKEY_COLOR_AMBIENT, material.ambient);
		scene->mMaterials[i]->Get(AI_MATKEY_COLOR_DIFFUSE, material.diffuse);
		scene->mMaterials[i]->Get(AI_MATKEY_COLOR_SPECULAR, material.specular);
		scene->mMaterials[i]->Get(AI_MATKEY_SHININESS, material.shiness);
		
		materials.push_back(material);
	}
}

void Level::ClearNodes(Node * node) 
{
	if (node->childs.size() == 0) {
		delete node->nodeAi;
		delete node;
		return;
	}

	for (int i = 0; i < node->childs.size(); i++)
	{
		ClearNodes(node->childs[i]);
	}
	delete node->nodeAi;
	delete node;
	return;
}

void Level::Clear() 
{
	ClearNodes(root);
	materials.clear();
	meshes.clear();
}

void Level::draw() {

	
	DrawNodes(root);

	
}
void Level::DrawHierarchy(Node* node) {
	if (node == root) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glColor3f(0.0f, 0.0f, 1.0f);
		glDisable(GL_LIGHTING);
		
	}
	
	
	if (node!=root) {
		glColor3f(0.0f, 0.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
		//glMultMatrixf(aiMatrix4x4toGLfloat(&node->parent->nodeAi->mTransformation));
		glBegin(GL_LINES);
			glDisable(GL_LIGHTING);
			glVertex3f(node->position.x, node->position.y, node->position.z);
			glVertex3f(node->parent->position.x, node->parent->position.y, node->parent->position.z);
		glEnd();

		//Drawing red squares on each node to easily see them
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(node->position.x + 0.025f, node->position.y + 0.025f, node->position.z);
			glVertex3f(node->position.x - 0.025f, node->position.y + 0.025f, node->position.z);
			glVertex3f(node->position.x - 0.025f, node->position.y - 0.025f, node->position.z);

			glVertex3f(node->position.x - 0.025f, node->position.y - 0.025f, node->position.z);
			glVertex3f(node->position.x + 0.025f, node->position.y - 0.025f, node->position.z);
			glVertex3f(node->position.x + 0.025f, node->position.y + 0.025f, node->position.z);
		glEnd();

	}
	for (int x = 0; x < node->childs.size(); x++)
	{	
		
		DrawHierarchy(node->childs[x]);
	}

}
void Level::DrawNodes(Node* node) {
  glEnable(GL_LIGHTING);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	
	for (int i = 0; i < node->meshes.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, meshes[node->meshes[i]].verticesId);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[node->meshes[i]].indicesId);

		glBindBuffer(GL_NORMAL_ARRAY, meshes[node->meshes[i]].normalsId);
		glNormalPointer(GL_FLOAT, 0, NULL);

		int numFaces = scene->mMeshes[meshes[node->meshes[i]].meshId]->mNumFaces;
		glDrawElements(GL_TRIANGLES, numFaces * 3, GL_UNSIGNED_INT, NULL);
	}

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	

	for (int x = 0; x < node->childs.size(); x++) 
	{
		DrawNodes(node->childs[x]);
	}

  glDisable(GL_LIGHTING);
}
GLfloat* Level::aiMatrix4x4toGLfloat(const aiMatrix4x4* from) {
	GLfloat result [4][4];
	result[0][0] = (GLfloat)from->a1; result[0][1] = (GLfloat)from->b1; result[0][2] = (GLfloat)from->c1; result[0][3] = (GLfloat)from->d1;
	result[1][0] = (GLfloat)from->a2; result[1][1] = (GLfloat)from->b2; result[1][2] = (GLfloat)from->c2; result[1][3] = (GLfloat)from->d2;
	result[2][0] = (GLfloat)from->a3; result[2][1] = (GLfloat)from->b3; result[2][2] = (GLfloat)from->c3; result[2][3] = (GLfloat)from->d3;
	result[3][0] = (GLfloat)from->a4; result[3][1] = (GLfloat)from->b4; result[3][2] = (GLfloat)from->c4; result[3][3] = (GLfloat)from->d4;
	GLfloat* result2 = &result[0][0];
	return result2;
}