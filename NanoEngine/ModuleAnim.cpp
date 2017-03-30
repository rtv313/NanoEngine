#include "ModuleAnim.h"



ModuleAnim::ModuleAnim()
{
}


ModuleAnim::~ModuleAnim()
{
}
void ModuleAnim::Load(const char* name, const char* path) {
	aiString auxString;
	auxString.Set(name);
	auto search = animations.find(auxString);
	if (search==animations.end()) {
		const aiScene* scene;
		
		Uint32 flags;// = aiProcess_PreTransformVertices;
		flags |= aiProcess_FlipUVs;
		flags |= aiProcess_Triangulate;

		scene = aiImportFile(path, flags);
		if (scene->HasAnimations())
		{
			Anim auxAnim;
			//auxAnim = malloc(sizeof(Anim));
			for (int i = 0; i < scene->mNumAnimations; i++) 
			{ // recorremos las distintas animaciones del fichero
				auxAnim.num_channels = scene->mAnimations[i]->mNumChannels;
				auxAnim.duration = scene->mAnimations[i]->mDuration;
				auxAnim.channels = (NodeAnim*)malloc(sizeof(NodeAnim)*scene->mAnimations[i]->mNumChannels);
				for (int p = 0; p < scene->mAnimations[i]->mNumChannels; p++) 
				{ // Recorremos los distitnos canales de cada animacion
					auxAnim.channels[p].name = scene->mAnimations[i]->mChannels[p]->mNodeName;
					auxAnim.channels[p].num_positions = scene->mAnimations[i]->mChannels[p]->mNumPositionKeys;
					auxAnim.channels[p].num_rotations = scene->mAnimations[i]->mChannels[p]->mNumRotationKeys;
					auxAnim.channels[p].positions = &scene->mAnimations[i]->mChannels[p]->mPositionKeys->mValue;
					auxAnim.channels[p].rotations = &scene->mAnimations[i]->mChannels[p]->mRotationKeys->mValue;
				}
				animations[auxString] = &auxAnim;
			}
		}
	}
}
nodeTransform* ModuleAnim::GetTransform(AnimInstance* instance, aiString channel_name, aiVector3D position, aiQuaternion rotation) {
	// This function returns the position and rotation of the node "channel_name", for the animation "instance"
	nodeTransform * transform = new nodeTransform;
	int a = -1;
	for (int i = 0;i<instance->anim->num_channels;i++) 
	{
		if (strcmp(instance->anim->channels[i].name.C_Str(),channel_name.C_Str()))
		{
			a = i;
			break;
		}
	}
	if (a == -1) 
	{
		//No se encuentra el nodo con el nombre channel_name
	}
	else {
		int frame = round((instance->time*instance->anim->channels[a].num_positions) / instance->anim->duration);
		transform->positions = instance->anim->channels[a].positions[frame];
		transform->rotations = instance->anim->channels[a].rotations[frame];
		return transform;
	}	
}
void ModuleAnim::UpdateInstances(float dt) 
{
	for (int i = 0; i < animationInstances.size();i++) 
	{
		animationInstances[i]->time += dt;
		if (animationInstances[i]->time > animationInstances[i]->anim->duration) 
		{
			animationInstances[i]->time = 0;
		}
	}
}
AnimInstance* ModuleAnim::GetAnimationInstance(aiString instanceName) 
{
	AnimInstance* newInstance = new AnimInstance;
	newInstance->anim = animations.find(instanceName)->second;
	animationInstances.push_back(newInstance);
	return newInstance;
}