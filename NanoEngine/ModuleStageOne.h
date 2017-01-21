
#ifndef  _MODULESCENESTAGEONE_H_
#define  _MODULESCENESTAGEONE_H_

#include "Module.h"
#include "Animation.h"
struct SDL_Texture;

class ModuleStageOne :public Module
{
public:
	ModuleStageOne(bool active = true);
	~ModuleStageOne();
	bool Start();
	update_status Update();
	bool CleanUp();
	
	
public :
	SDL_Texture* levelOne = nullptr;
	Animation background;

private:

	
};
#endif // _MODULESCENESTAGEONE_H_
