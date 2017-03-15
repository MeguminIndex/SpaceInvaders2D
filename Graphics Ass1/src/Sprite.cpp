
#include "Sprite.h"

using namespace std;

	Sprite::Sprite()
	{

		//corrects position onto camera
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.0f, 1.5f, 0.0f));
	}


	void Sprite::loadTexture(string file)
	{

		//SDL_Surface* image = IMG_Load(file.c_str());
		//if (!image)
		//{
		//	SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load error: %s\n", IMG_GetError());

		//}

		//glGenTextures(1, &texture);
		//glBindTexture(GL_TEXTURE_2D, texture);


		////texture paramiters
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		////applying image to the texture
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
		//glGenerateMipmap(GL_TEXTURE_2D);

		//glBindTexture(GL_TEXTURE_2D, 0);
		//SDL_FreeSurface(image);

	}

	Sprite::~Sprite()
	{
	
		
		SDL_Log("Sprite destroyed");

	}