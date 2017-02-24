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

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f, bool flip = false);
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera = true);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
	//Cube *cube;
	Grid *grid;
	//Gizmo gizmo;
	//Model batman;

};

#endif // __MODULERENDER_H__