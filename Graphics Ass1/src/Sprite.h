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
	void loadTexture(string file);
	~Sprite();
	
	//stores pointer to texture
	GLuint texture;

	

	//declare the transform matrix once
	glm::mat4 _transRotate;
	glm::mat4 _transTranslate;
	glm::mat4 _transScale;


	movementInput direction = movementInput::None;
};
#endif // !#include "Sprite.h"