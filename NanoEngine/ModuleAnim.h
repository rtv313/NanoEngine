#ifndef __MODULEANIM__
#define __MODULEANIM__
#include "assimp/include/assimp/scene.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "assimp/include/assimp/cimport.h"
#include "assimp/include/assimp/postprocess.h"
#include "Globals.h"
#include<map>

struct nodeTransform 
{
	aiVector3D positions;
	aiQuaternion rotations;
};
struct NodeAnim
{
	aiString name;
	aiVector3D* positions = nullptr;
	aiQuaternion* rotations = nullptr;
	unsigned num_positions = 0;
	unsigned num_rotations = 0;
};
struct Anim
{
	unsigned duration = 0;
	unsigned num_channels = 0;
	NodeAnim * channels = nullptr;
};
struct AnimInstance 
{
	Anim* anim;
	unsigned time = 0;
	bool loop = true;

	AnimInstance* next = nullptr;
	unsigned blend_duration = 0;
	unsigned blend_time = 0;
};
class ModuleAnim
{
	struct LessString
	{
		bool operator()(const aiString& left, const aiString& right)const
		{
			return ::strcmp(left.data, right.data) < 0;
		}
	};
	typedef std::map<aiString, Anim*, LessString> AnimMap;
public:
	ModuleAnim();
	~ModuleAnim();
	void ModuleAnim::Load(const char* name, const char* path);
	void ModuleAnim::UpdateInstances(float dt);
	AnimInstance* ModuleAnim::GetAnimationInstance(aiString instanceName );
	nodeTransform* GetTransform(AnimInstance* instance, aiString channel_name, aiVector3D position, aiQuaternion rotation);
private:
	std::vector<AnimInstance*> animationInstances;
	AnimMap animations;
	
};
#endif