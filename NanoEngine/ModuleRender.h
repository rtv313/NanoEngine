#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Cube.h"
#include "Grid.h"
#include "Gizmo.h"
#include "Model.h"

#include "Module.h"
#include "Globals.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>


struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	SDL_Renderer* renderer = nullptr;
	
	//Cube *cube;
	Grid *grid;
	Gizmo gizmo;
	//Model batman;

};

#endif // __MODULERENDER_H__