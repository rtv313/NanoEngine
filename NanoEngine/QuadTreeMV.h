#include "Cube.h"
struct QuadTreeNode 
{
	float x1, x2, y1, y2;
	QuadTreeNode* childs[4];
	int ID;
	Cube* cube;
};
class QuadTreeMV
{
public:
	QuadTreeNode* root;


	QuadTreeMV();
	~QuadTreeMV();
	void QuadTreeMV::Create(float x1,float x2,float y1,float y2);
	void QuadTreeMV::Clear();
	void QuadTreeMV::Insert();
	//void QuadTreeMV::Remove();
	void QuadTreeMV::CollectIntersections();
	void QuadTreeMV::DivideQuad(QuadTreeNode* node);
	void QuadTreeMV::DrawQuads(QuadTreeNode* node);
	void QuadTreeMV::TestQuads(QuadTreeNode* node);
private:
	
	int NumNodes;

};

