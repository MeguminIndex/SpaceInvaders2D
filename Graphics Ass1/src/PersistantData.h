#ifndef PERSISTANTDATA_H
#define PERSISTANTDATA_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "PersistantData.h"
//#include "Sprite.h"
#include <vector>


#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;


class PersistantData
{
public:
	//this class stores alot of the data used in my game.
	
	

	
	PersistantData();
	~PersistantData();
	
	bool closeApplication = false;
	bool resartGame;
	


	
	int windowW = 0, windowH = 0;
	float gameWorldW = 0, gameWorldH = 0;

	float windowWRatio = 0, windowHRatio = 0;

	bool paused = false;

	



	void gameToScreenRatio();

	bool windowResized = false;
	
	GLuint ReturnTexture(string file);

	float playerSize = 0;


	SDL_GameController * controller[2];

	//Audio
	//Mix_Music* backingMusic;
	//Mix_Chunk* pointPickUp;



	//textures
	GLuint enermieTexture;
	GLuint playerTexture;

	

	//window/render
	SDL_Window *window = nullptr;
	//SDL_Renderer *renderer = nullptr;
	
	void setGameWorldSize(float w,float h);



private:
	
	float gameWorldRw;//stores the value of the game worlds width (entire world)
	float gameWorldRh;//stores value of game worlds height

};


#endif