#ifndef __MODULETEXTURES_H__
#define __MODULETEXTURES_H__


#include<map>
#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	bool CleanUp();

	std::map <std::string, uint> textures;
	uint const Load(const char* path, std::string directory);
	void Unload();

private:
	
};

#endif // __MODULETEXTURES_H__