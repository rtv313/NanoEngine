#ifndef __MODEL_H__
#define __MODEL_H__

#include <assimp/scene.h>
#include "MathGeoLib/include/MathGeoLib.h"
#include <vector>
#include "Globals.h"
class Model
{
	const aiScene* scene = 0;
public:
	Model();
	~Model();
	void Load(const char* file);
	void Clear();
	void Draw();

	float3 position;
	float3 scale;
	float3 rotation;

private:
	uint* my_id=nullptr;
	uint* my_indices = nullptr;
	uint my_textIndex = 0;
	std::vector <uint> indices;


};


#endif