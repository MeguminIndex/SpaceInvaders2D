
#include "Sprite.h"

using namespace std;

	Sprite::Sprite()
	{

		//corrects position onto camera
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.0f, 1.5f, 0.0f));
		dead = false;
	}


	Sprite::~Sprite()
	{
	
		
		SDL_Log("Sprite destroyed");

	}