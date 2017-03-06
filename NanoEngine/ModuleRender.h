#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Cube.h"
#include "Grid.h"
#include "Gizmo.h"
#include "Model.h"
#include "Level.h"

#include "Module.h"
#include "Globals.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>



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
	
	Cube *cube;
	Grid *grid;
	Gizmo gizmo;
	Model batman;
	Model magneto;
	//Level city;
  Model city;
};

#endif // __MODULERENDER_H__