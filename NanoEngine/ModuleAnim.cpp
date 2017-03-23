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
			for (int i = 0; i < scene->mNumAnimations; i++) { // recorremos las distintas animaciones del fichero
				auxAnim.num_channels = scene->mAnimations[i]->mNumChannels;
				auxAnim.duration = scene->mAnimations[i]->mDuration;
				//auxAnim.channels = malloc(sizeof(Anim));
				for (int p = 0; p < scene->mAnimations[i]->mNumChannels; p++) { // Recorremos los distitnos canales de cada animacion
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