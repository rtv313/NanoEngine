
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "Model.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include <algorithm>
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

using namespace std;

ModuleTextures::ModuleTextures()
{
}

// Destructor
ModuleTextures::~ModuleTextures()
{
	IMG_Quit();
}

// Called before render is available
bool ModuleTextures::Init()
{
	LOG_GLOBALS("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags)
	{
		LOG_GLOBALS("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before quitting
bool ModuleTextures::CleanUp()
{
	LOG_GLOBALS("Freeing textures and Image library");

	for(list<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
		SDL_DestroyTexture(*it);

	textures.clear();
	return true;
}

// Load new texture from file path
SDL_Texture* const ModuleTextures::Load(const char* path)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path);

	if(surface == nullptr)
	{
		LOG_GLOBALS("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(App->renderer->renderer, surface);

		if(texture == nullptr)
		{
			LOG_GLOBALS("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			textures.push_back(texture);
		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

// Free texture from memory
void ModuleTextures::Unload(SDL_Texture* texture)
{
	for(list<SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		if(*it == texture)
		{
			SDL_DestroyTexture(*it);
			textures.erase(it);
			break;
		}
	}
}

unsigned ModuleTextures::Load(const aiString& file)
{
	std::list<SDL_Texture>::const_iterator it = std::textures.find(file);

	if (it != textures.end())
	{
		return it->second;
	}

	return textures[file] = ForceLoad(file);
}


unsigned ModuleTextures::ForceLoad(const aiString& file)
{
	ILuint imageId;
	ilGenImages(1, &imageId);
	ilBindImage(imageId);

	if (ilLoadImage(file.data))
	{
		GLuint textureId = 0;
		glGenTextures(1, &textureId);

		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		int components = 3;
		int format = GL_RGB;

		switch (ilGetInteger(IL_IMAGE_FORMAT))
		{
		case IL_RGB:
			components = 3;
			format = GL_RGB;
			break;
		case IL_RGBA:
			components = 4;
			format = GL_RGBA;
			break;
		case IL_BGR:
			components = 3;
			format = GL_BGR_EXT;
			break;
		case IL_BGRA:
			components = 4;
			format = GL_BGRA_EXT;
			break;
		default:
			assert(false);
		}

		ILubyte* data = ilGetData();
		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);

		glTexImage2D(GL_TEXTURE_2D, 0, components, width,
			height, 0, format,
			GL_UNSIGNED_BYTE, data);

		ilDeleteImages(1, &imageId);

		glBindTexture(GL_TEXTURE_2D, 0);

		return textureId;
	}

	return 0;
}