#ifndef __MODULETEXTURES_H__
#define __MODULETEXTURES_H__

#include<list>
#include "Module.h"
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"
#include "Globals.h"



class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	bool CleanUp();
	unsigned Load(const aiString& file);
	unsigned ForceLoad(const aiString& file);

	SDL_Texture* const Load(const char* path);
	void Unload(SDL_Texture* texture);

private:
	std::list<SDL_Texture*> textures;
};

#endif // __MODULETEXTURES_H__
