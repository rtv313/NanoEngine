#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "Glew/include/GL/glew.h"
#include "SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment( lib, "opengl32.lib")
#pragma comment( lib, "glu32.lib")
#pragma comment( lib, "Glew/lib/Release/Win32/glew32.lib" )

ModuleRender::ModuleRender()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH * SCREEN_SIZE;
	camera.h = SCREEN_HEIGHT* SCREEN_SIZE;

}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG_GLOBALS("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

  renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == nullptr)
	{
		LOG_GLOBALS("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleRender::PreUpdate()
{
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	//SDL_RenderClear(renderer);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //glColor3f c = cam->background;
  //glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glFrustum(-1, 1, -1, 1, 1, 100);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glLoadMatrixf(cam->GetOpenGLViewMatrix());
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	// debug camera
	int speed = 0 * dt;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->renderer->camera.y += speed;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->renderer->camera.y -= speed;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->renderer->camera.x += speed;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->renderer->camera.x -= speed;

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	//SDL_RenderPresent(renderer);
  //glVertex3f(-0.5f, -0.5f, 0.5f); //A
  //glVertex3f(0.5f, -0.5f, 0.5f); //B
  //glVertex3f(-0.5f, 0.5f, 0.5f); //C
  //glVertex3f(0.5f, 0.5f, 0.5f); //D
  //glVertex3f(-0.5f, -0.5f, -0.5f); //E
  //glVertex3f(0.5f, -0.5f, -0.5f); //F
  //glVertex3f(-0.5f, 0.5f, -0.5f); //G
  //glVertex3f(0.5f, 0.5f, -0.5f); //H

  glColor3f(255.0, 0.0, 0.0);

  glTranslatef(0.0f, 0.0f, -5.0f);
  glRotatef(45.0f, 1.0f, 1.0f, 0.0f);

  //TODO: Declarar solo una vez (init/start) en vez de declarar en el loop
  uint my_id = 0;
  /*
  A1
  B2
  C3
  D4
  E5
  F6
  G7
  H8
  */
  GLfloat vertices[] = { 
	  -0.5f, -0.5f, 0.5f, // A
	  0.5f, -0.5f, 0.5f, // B
	  -0.5f, 0.5f, 0.5f, // C
	  0.5f, 0.5f, 0.5f, // D
	  -0.5f, -0.5f, -0.5f,//E
	  0.5f, -0.5f, -0.5f, // F
	  -0.5f, 0.5f, -0.5f,//G
	  0.5f, 0.5f, -0.5f, // H
  };

  uint indices[] = {
    0,1,2,
    1,3,2,
    5,7,3,
    3,1,5,
    4,6,7,
    4,7,5,
    2,6,4,
    4,0,2,
    6,2,3,
    7,6,3,
    0,4,1,
    4,5,1};

  /*GLfloat cubecolors[] = {
	  0.5f, 0.5f, 0.5f, // A
	  0.0f, 0.0f, 255.0f, // B
	  0.0f, 255.0f, 0.0f, // C
	  0.0f, 255.0f, 255.0f, // D
	  255.0f, 0.0f, 0.0f,//E
	  255.0f, 0.0f, 255.0f, // F
	  255.0f, 255.0f, 0.0f,//G
	  255.0f, 255.0f, 255.0f, // H
  };*/

  glGenBuffers(1, (GLuint*) &(my_id));
  glBindBuffer(GL_ARRAY_BUFFER, my_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*36* 3, vertices, GL_STATIC_DRAW);

  uint my_indices = 0;
  glGenBuffers(1, (GLuint*) &(my_indices));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*36, indices, GL_STATIC_DRAW);
  // End TODO
  /*glBegin(GL_TRIANGLES);
    glVertex3f(-0.5f, -0.5f, 0.5f); //A
    glVertex3f(0.5f, -0.5f, 0.5f); //B
    glVertex3f(-0.5f, 0.5f, 0.5f); //C

    glVertex3f(0.5f, -0.5f, 0.5f); //B
    glVertex3f(0.5f, 0.5f, 0.5f); //D
    glVertex3f(-0.5f, 0.5f, 0.5f); //C

    glVertex3f(0.5f, -0.5f, -0.5f); //F
    glVertex3f(0.5f, 0.5f, -0.5f); //H
    glVertex3f(0.5f, 0.5f, 0.5f); //D

    glVertex3f(0.5f, 0.5f, 0.5f); //D
    glVertex3f(0.5f, -0.5f, 0.5f); //B
    glVertex3f(0.5f, -0.5f, -0.5f); //F

    glVertex3f(-0.5f, -0.5f, -0.5f); //E
    glVertex3f(-0.5f, 0.5f, -0.5f); //G
    glVertex3f(0.5f, 0.5f, -0.5f); //H

    glVertex3f(-0.5f, -0.5f, -0.5f); //E
    glVertex3f(0.5f, 0.5f, -0.5f); //H
    glVertex3f(0.5f, -0.5f, -0.5f); //F

    glVertex3f(-0.5f, 0.5f, 0.5f); //C
    glVertex3f(-0.5f, 0.5f, -0.5f); //G
    glVertex3f(-0.5f, -0.5f, -0.5f); //E

    glVertex3f(-0.5f, -0.5f, -0.5f); //E
    glVertex3f(-0.5f, -0.5f, 0.5f); //A
    glVertex3f(-0.5f, 0.5f, 0.5f); //C

    glVertex3f(-0.5f, 0.5f, -0.5f); //G
    glVertex3f(-0.5f, 0.5f, 0.5f); //C
    glVertex3f(0.5f, 0.5f, 0.5f); //D

    glVertex3f(0.5f, 0.5f, -0.5f); //H
    glVertex3f(-0.5f, 0.5f, -0.5f); //G
    glVertex3f(0.5f, 0.5f, 0.5f); //D

    glVertex3f(-0.5f, -0.5f, 0.5f); //A
    glVertex3f(-0.5f, -0.5f, -0.5f); //E
    glVertex3f(0.5f, -0.5f, 0.5f); //B

    glVertex3f(-0.5f, -0.5f, -0.5f); //E
    glVertex3f(0.5f, -0.5f, -0.5f); //F
    glVertex3f(0.5f, -0.5f, 0.5f); //B

  glEnd();*/


  glEnableClientState(GL_VERTEX_ARRAY);
  
  glBindBuffer(GL_ARRAY_BUFFER, my_id);
  glVertexPointer(3, GL_FLOAT, 0, NULL);

  // ... draw other buffers
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
  
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
  //glDrawArrays(GL_TRIANGLES, 0, 36 * 3);

  glDisableClientState(GL_VERTEX_ARRAY);

  SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG_GLOBALS("Destroying renderer");

	//Destroy window
	if(renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed, bool flip)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE;

	if(section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	SDL_RendererFlip flipOption = SDL_FLIP_NONE;
	if (flip) 
		flipOption = SDL_FLIP_HORIZONTAL;
	
	if(SDL_RenderCopyEx(renderer, texture, section, &rect,0,NULL, flipOption) != 0)
	{
		LOG_GLOBALS("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * SCREEN_SIZE);
		rec.y = (int)(camera.y + rect.y * SCREEN_SIZE);
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG_GLOBALS("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}