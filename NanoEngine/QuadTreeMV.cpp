#include "QuadTreeMV.h"



QuadTreeMV::QuadTreeMV()
{
}


QuadTreeMV::~QuadTreeMV()
{
}

void QuadTreeMV::Create(float x1, float x2, float y1, float y2) 
{
	root = new QuadTreeNode;
	root->x1 = x1;
	root->x2 = x2;
	root->y1 = y1;
	root->y2 = y2;
	root->childs[0] = nullptr;
	root->childs[1] = nullptr;
	root->childs[2] = nullptr;
	root->childs[3] = nullptr;
	root->ID = 1;
	root->cube = new Cube();
	NumNodes = 0;
}
void QuadTreeMV::DivideQuad(QuadTreeNode* node) 
{
	QuadTreeNode* aux1, *aux2, *aux3, *aux4;
	aux1 = new QuadTreeNode;
	aux2 = new QuadTreeNode;
	aux3 = new QuadTreeNode;
	aux4 = new QuadTreeNode;

	/*
	A = X1Y1	B = X2Y1
			E = (X1+X2)/2 (Y1+Y2)/2;
	C = X2Y2	D = X1Y2
	*/

	float ex = (node->x1 + node->x2) / 2;
	float ey = (node->y1 + node->y2) / 2;

	aux1->x1 = node->x1;
	aux1->x2 = ex;
	aux1->y1 = node->y1;
	aux1->y2 = ey;
	aux1->cube = new Cube();
	aux1->cube->posX = (aux1->x1 + aux1->x2 ) / 2;
	aux1->cube->posZ = (aux1->y1 + aux1->y2) / 2;
	aux1->cube->posY = 0.5;
	aux1->cube->scaleX = aux1->x2 - aux1->x1;
	aux1->cube->scaleZ = aux1->y2 - aux1->y1;

	++NumNodes;
	aux1->ID = NumNodes;
	
	aux2->x1 = ex;
	aux2->x2 = node->x2;
	aux2->y1 = node->y1;
	aux2->y2 = ey;
	aux2->cube = new Cube();
	++NumNodes;
	aux2->ID = NumNodes;
	aux2->cube->posX = (aux2->x1 + aux2->x2) / 2;
	aux2->cube->posZ = (aux2->y1 + aux2->y2) / 2;
	aux2->cube->posY = 0.5;
	aux2->cube->scaleX = aux2->x2 - aux2->x1;
	aux2->cube->scaleZ = aux2->y2 - aux2->y1;

	aux3->x1 = ex;
	aux3->x2 = node->x2;
	aux3->y1 = ey;
	aux3->y2 = node->y2;
	aux3->cube = new Cube();
	++NumNodes;
	aux3->ID = NumNodes;
	aux3->cube->posX = (aux3->x1 + aux3->x2) / 2;
	aux3->cube->posZ = (aux3->y1 + aux3->y2) / 2;
	aux3->cube->posY = 0.5;
	aux3->cube->scaleX = aux3->x2 - aux3->x1;
	aux3->cube->scaleZ = aux3->y2 - aux3->y1;

	aux4->x1 = node->x1;
	aux4->x2 = ex;
	aux4->y1 = ey;
	aux4->y2 = node->y2;
	aux4->cube = new Cube();
	++NumNodes;
	aux4->ID = NumNodes;
	aux4->cube->posX = (aux4->x1 + aux4->x2) / 2;
	aux4->cube->posZ = (aux4->y1 + aux4->y2) / 2;
	aux4->cube->posY = 0.5;
	aux4->cube->scaleX = aux4->x2 - aux4->x1;
	aux4->cube->scaleZ = aux4->y2 - aux4->y1;

	for (int i = 0; i <= 3;i++) {
		aux1->childs[i] = nullptr;
		aux2->childs[i] = nullptr;
		aux3->childs[i] = nullptr;
		aux4->childs[i] = nullptr;
	}
	

	node->childs[0] = new QuadTreeNode;
	node->childs[1] = new QuadTreeNode;
	node->childs[2] = new QuadTreeNode;
	node->childs[3] = new QuadTreeNode;

	node->childs[0] = aux1;
	node->childs[1] = aux2;
	node->childs[2] = aux3;
	node->childs[3] = aux4;
	
}
void QuadTreeMV::DrawQuads(QuadTreeNode* node) 
{
	node->cube->draw();
	if (node->childs[0] != nullptr) {
		for (int i = 0; i <= 3; i++) {
			DrawQuads(node->childs[i]);
		}
	}
}
void QuadTreeMV::TestQuads(QuadTreeNode* node)
{
	DivideQuad(node);
	for (int i = 0; i <= 3; i++) {
		DivideQuad(node->childs[i]);
		for (int p = 0; p <= 3; p++) {
			DivideQuad(node->childs[i]->childs[p]);
		}
	}
}
