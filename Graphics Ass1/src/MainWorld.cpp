
#include "SDL.h"
#include "MainWorld.h"



using namespace std;

MainWorld::MainWorld()
{
	SDL_LogDebug(SDL_LOG_PRIORITY_DEBUG, "MainWorld Constructed");




}

void MainWorld::setUpEnermies(float entitieSize)
{
	float size = 0.2;
	float x = -1.85- size - -0.05, y= 1.5 - size -0.05;
	
	for (float i = y; i > 1;)
	{
		for (float j = x; j < 2;)
		{
		
			Sprite tmpSprite;
			
			tmpSprite.modelMatrix = glm::translate(tmpSprite.modelMatrix, glm::vec3(j, i, 0.0f));
			tmpSprite.modelMatrix = glm::scale(tmpSprite.modelMatrix, glm::vec3(size));
			
			tmpSprite.direction = movementInput::Left;//mobs start off going left
			
			enermieSp.push_back(tmpSprite);

			j += size + 0.04f;
		
		}

		x = -1.85;
		i -= size +0.04f;

		

	}


}

MainWorld::~MainWorld()
{
	SDL_LogDebug(SDL_LOG_PRIORITY_DEBUG, "MainWorld De-Constructed");


}



