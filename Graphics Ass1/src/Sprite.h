#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include "Sprite.h"
#include "SDL_image.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <chrono>
#include <string>

using namespace std;

enum class movementInput { Up, Down, Left, Right, None };


class Sprite
{

public:
	Sprite();
	


	~Sprite();
	
	
	float health;
	
	float size;
	
	glm::mat4 modelMatrix;
	glm::mat4 rotationMatrix;

	bool dead;

	movementInput direction = movementInput::None;
};
#endif // !#include "Sprite.h"