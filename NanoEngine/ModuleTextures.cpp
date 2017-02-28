#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

using namespace std;

ModuleTextures::ModuleTextures()
{
}

// Destructor
ModuleTextures::~ModuleTextures()
{
	CleanUp();
}

// Called before render is available
bool ModuleTextures::Init()
{
	

	return true;
}

// Called before quitting
bool ModuleTextures::CleanUp()
{
	LOG_GLOBALS("Freeing textures and Image library");

	for (auto it = textures.begin(); it != textures.end(); ++it)
	{
		glDeleteTextures(1, &it->second);
	}

	textures.clear();
	return true;
}

// Load new texture from file path
uint const ModuleTextures::Load(const char* path, std::string directory)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	ILuint imageId;
	ILboolean success;			// Create a flag to keep track of success/failure
	ILenum error;				// Create a flag to keep track of the IL error state
	ilGenImages(1, &imageId); 		// Generate the image ID
	ilBindImage(imageId); 			// Bind the image

	if (textures.count(filename) > 0) {
		return textures[filename];
	}

	success = ilLoadImage(filename.c_str());

	if (!success)
	{
		error = ilGetError();
		std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		exit(-1);
	}

	

	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	ILubyte * pixmap = ilGetData();

	//Generate Texture
	GLuint textureID;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureID);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, pixmap);
	glGenerateMipmap(GL_TEXTURE_2D);
	// Parameters

	glBindTexture(GL_TEXTURE_2D, 0); // clear texture
	ilBindImage(0);
	ilDeleteImage(imageId);

	textures[filename]=textureID;

	return textureID;

}

// Free texture from memory
void ModuleTextures::Unload()
{
	
	return;
}


