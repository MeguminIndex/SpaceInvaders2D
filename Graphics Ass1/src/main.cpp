
#include <iostream>
#include <string>
//#include <GLFW/glfw3.h>

// // GLEW - OpenGL Extension Wrangler - http://glew.sourceforge.net/
// // NOTE: include before SDL.h
#include <GL/glew.h>

// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

// // - OpenGL Mathematics - https://glm.g-truc.net/
 #define GLM_FORCE_RADIANS // force glm to use radians
// // NOTE: must do before including GLM headers
// // NOTE: GLSL uses radians, so will do the same, for consistency
 #include <glm/glm.hpp>
 #include <glm/gtc/matrix_transform.hpp>
 #include <glm/gtc/type_ptr.hpp>


#include <CoreWindow.h>

#include "Sprite.h"
#include "MainWorld.h"
#include "PersistantData.h"
using namespace glm;

using namespace std;

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}







int createWin(int w, int h, SDL_Window* &win)
{

 win = SDL_CreateWindow("OpenGL Workshop",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,w, h, SDL_WINDOW_OPENGL |SDL_WINDOW_RESIZABLE);

	SDL_assert(win);

	return 0;
}

void input(MainWorld* &world,PersistantData* &persData,vec3 &colourValueGLMVector,bool &running)
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{

		switch (e.type)
		{
		case SDL_WINDOWEVENT:
		{
			switch (e.window.event)
			{
			case SDL_WINDOWEVENT_RESIZED:
				SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Window Resized");
				persData->windowResized = true;
				break;


			default:
				break;
			}

		}
		case SDL_KEYDOWN:
			if (!e.key.repeat)
			{
				switch (e.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					running = false;
					break;
				case SDL_SCANCODE_C:
					if (world->Applytexture == false)
					{
						colourValueGLMVector = vec3(0.20f, 0.29f, 0.33f);
						world->Applytexture = true;
					}
					else
					{
						colourValueGLMVector = vec3(0.255f, 0.64f, 0.100f);
						world->Applytexture = false;
					}
					break;

				case SDL_SCANCODE_W:
					world->player.direction = movementInput::Up;
					break;

				case SDL_SCANCODE_A:
					world->player.direction = movementInput::Left;
					break;

				case SDL_SCANCODE_S:
					world->player.direction = movementInput::Down;
					break;

				case SDL_SCANCODE_D:
					world->player.direction = movementInput::Right;
					break;

				case SDL_SCANCODE_0:
					if (world->ApplyRotate == false)
					{

						world->ApplyRotate = true;
					}
					else
					{

						world->ApplyRotate = false;
					}

					break;

				}

			}
			break;

		case SDL_KEYUP:
			world->player.direction = movementInput::None;
			break;



		}



		if (e.type == SDL_QUIT)
		{
			SDL_Log("Application Quit Requested");
			running = false;

		}

	}
}
void render(GLuint VAO, GLuint EBO,MainWorld* world,PersistantData* persData, vec3 &colourValueGLMVector, GLuint shaderProgram, mat4 viewMatrix, mat4 projectionMatrix)
{

#pragma region testrendering
	// pre-render	
	
	
	glClearColor(colourValueGLMVector.r, colourValueGLMVector.g, colourValueGLMVector.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBindTexture(GL_TEXTURE_2D, persData->playerTexture);//binds texture



														  //set up the rotation transformation matrix
	



	GLint modelLocation = glGetUniformLocation(shaderProgram, "modelMat");

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(world->player.modelMatrix*world->player.rotationMatrix));

	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);




	GLint viewLocation = glGetUniformLocation(shaderProgram, "viewMat");
	GLint projectionLocation = glGetUniformLocation(shaderProgram, "projectionMat");
	//set the uniforms in the shader


	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	
	


	


	for (const auto &enermy : world->enermieSp)
	{


		glBindTexture(GL_TEXTURE_2D, persData->enermieTexture);//binds texture
		GLint modelLocation2 = glGetUniformLocation(shaderProgram, "modelMat");

		glUniformMatrix4fv(modelLocation2, 1, GL_FALSE, glm::value_ptr(enermy.modelMatrix*enermy.rotationMatrix));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		



	}
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// post-render
	SDL_GL_SwapWindow(persData->window);

	
}

void update(MainWorld* &world, PersistantData* &persData, chrono::duration<double> t)
{
	if (persData->windowResized == true)
	{
		int w, h;
		SDL_GL_GetDrawableSize(persData->window,&w,&h);
		glViewport(0, 0, w, h);
		persData->windowResized = false;
	}

	if (world->ApplyRotate == true)
		world->player.rotationMatrix = glm::rotate(world->player.rotationMatrix, glm::radians(0.1f), glm::vec3(0.0f, 0.0f, 1.0f));

	float playerMoveSpeed = 0.5* t.count();

	float mobMoveSpeedm =0.4 * t.count(); // need to have the space invaders speed up over time 

	
	
	//player movement
	if (world->player.direction == movementInput::Up)
	{
		world->player.modelMatrix = glm::translate(world->player.modelMatrix, glm::vec3(0.0f, playerMoveSpeed, 0.0f));
	}
	else if (world->player.direction == movementInput::Down)
	{
		world->player.modelMatrix = glm::translate(world->player.modelMatrix, glm::vec3(0.0f, -playerMoveSpeed, 0.0f));

	}
	else if (world->player.direction == movementInput::Left)
	{
		world->player.modelMatrix = glm::translate(world->player.modelMatrix, glm::vec3(-playerMoveSpeed, 0.00f, 0.0f));

	}
	else if (world->player.direction == movementInput::Right)
	{
		world->player.modelMatrix = glm::translate(world->player.modelMatrix, glm::vec3(playerMoveSpeed, 0.00f, 0.0f));

	}

	bool dropDown =false;
	//update each enermy sprite position here  
	for (auto &enermy : world->enermieSp)
	{
		
		switch(enermy.direction)
		{
			case movementInput::Right:
					//		SDL_Log("Right");
					enermy.modelMatrix = glm::translate(enermy.modelMatrix, glm::vec3(mobMoveSpeedm, 0.00f, 0.0f));
					

					break;
				case movementInput::Left:
					//		SDL_Log("Left");
					enermy.modelMatrix = glm::translate(enermy.modelMatrix, glm::vec3(-playerMoveSpeed, 0.00f, 0.0f));
		}
		
		
		//
		
		
	}
	
	

}

int initialise(SDL_Window *win,SDL_GLContext &glcontext, GLint width, GLint height)
{
	// Set all the required options for OGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE);

	glcontext = SDL_GL_CreateContext(win);

	glewExperimental = GL_TRUE;
	//initialize GLEW
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Glew init error %s\n", glewGetErrorString(glewError));
		return 1;
	}
	SDL_Log("glewInit initialised OK!\n");

	GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}


	glViewport(0, 0, width, height);


	// SDL_Image initialise
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_image init error: %s\n",
			IMG_GetError());
		return 1;
	}
	SDL_Log("SDL_image initialised OK!\n");

	// SDL_ttf initialise
	if (TTF_Init() == -1) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_ttf init error: %s\n",
			SDL_GetError());
		return 1;
	}
	SDL_Log("SDL_ttf initialised OK!\n");

	// SDL_mixer initialise
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_mixer init error: %s\n   PERHAPS NO "
			"HEADPHONES/SPEAKERS CONNECTED\n",
			Mix_GetError());
		return 1;
	}
	SDL_Log("SDL_mixer initialised OK!\n");

	return 0;
}

int main(int argc, char *argv[]) {

	PersistantData* persData = new PersistantData();
	
#pragma region initialise
	// SDL initialise
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s\n",
			SDL_GetError());
		return 1;
	}
	SDL_Log("SDL initialised OK!\n");

	// Window Creation
	GLint width = 800, height = 600;
	//SDL_Window *win = nullptr;
	// win = SDL_CreateWindow("Hello World", 100, 100, 800, 600, 0);

	createWin(width, height,persData->window);

	if (persData->window == nullptr) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_CreateWindow init error: %s\n", SDL_GetError());
		return 1;
	}


	SDL_GLContext glcontext = SDL_GL_CreateContext(persData->window);

	int code = initialise(persData->window, glcontext, width, height);
	if (code != 0)
	{
		return 1;
	}
#pragma endregion


  

  vec3 colourValueGLMVector = vec3(0.255f, 0.64f, 0.100f);


  GLfloat vertices[] = {
	  // Positions          // Colors           // Texture Coords
	  0.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Top Right
	  0.0f, -0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Bottom Right
	  -1.0f, -0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
	  -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,  // Top Left 


	 
  };


  GLuint indices[] = {  // Note that we start from 0!
	  0, 1, 3, // First Triangle
	  1, 2, 3  // Second Triangle
	 
  };

#pragma region GLBuffers/Shaders ect..
  //try finding reading from a seperate file
  const GLchar* vertexShaderSource = R"(
		#version 430 core
  		layout (location = 0) in vec3 position;
		layout (location = 1) in vec3 color;
		layout (location = 2) in vec2 texCoord;

		out vec3 ourColor;
		out vec2 TexCoord;
		
		uniform mat4 modelMat;
		uniform mat4 viewMat;
		uniform mat4 projectionMat;
		void main()
		{
			gl_Position = projectionMat * viewMat * modelMat * vec4(position.x, position.y, position.z, 1.0);
			ourColor = color;
			TexCoord = vec2(texCoord.x, 1.0f - texCoord.y);
		}
  )";

  const GLchar* fragmentShaderSource = R"(
	#version 430 core
	in vec3 ourColor;
	in vec2 TexCoord;

	out vec4 color;

    uniform sampler2D ourTexture;	

	void main()
	{
	  color = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f) ;
	}

	)";

  // Vertex shader
  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  //check for errors
  GLint success;//variable to store success state
  GLchar infoLog[512];//stores error msg
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//gets succes status
  if (!success)
  {
	  glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	  std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILD\n" << infoLog << std::endl;


  }

  // Fragment shader
  GLuint fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // check for errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);//gets succes status
  if (!success)
  {
	  glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	  std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILD\n" << infoLog << std::endl;


  }

  // Link Shaders
  GLuint shaderProgram;
  shaderProgram = glCreateProgram();//creating program and returns id of it
									//attaching and linking shaders
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  //check if it failed/succeded
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)//if fails
  {
	  // glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
  }


  glDeleteShader(vertexShader);//deltes the shader object now that we dont need it
  glDeleteShader(fragmentShader);
  //  glDeleteShader(fragmentShader2);

  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  //OpenGL Buffers
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  //Bind Vertex Array Object
  glBindVertexArray(VAO);

  // Copy our vertices array in a buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  //texture attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  //Element Buffer object
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


  //unbind array buf
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  //unbind element array buff
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  //Unbind the VAO
  glBindVertexArray(0);

#pragma endregion

  
  MainWorld* world = new MainWorld();

  //GLuint texture; 
  //loadSurface("assets\\wall2.png", texture);
  
 world->player = Sprite();
  

  persData->playerTexture = persData->ReturnTexture("assets\\wall2.png");

 // world->enermieSp.push_back(Sprite());

  persData->enermieTexture = persData->ReturnTexture("assets\\enermy.png");

  world->setUpEnermies(4);


  glm::mat4 viewMatrix;

  glm::mat4 projectionMatrix;

  
  SDL_GetWindowSize(persData->window, &width, &height);

	//left, right, bottom, top, near clip plane, far clip plane
  projectionMatrix = glm::ortho(0.0f, 4.0f, 0.0f, 3.0f, -1.0f, 100.0f);


  SDL_Log("Game Loop Started");

  bool running = true;


  chrono::milliseconds skipTicks(1000 / 120);

  chrono::high_resolution_clock::time_point next_Game_Tick = chrono::high_resolution_clock::now();

  chrono::duration<double> lastdt = chrono::milliseconds(0);
  while (running == true)
  {
	 
	  chrono::high_resolution_clock::time_point t = chrono::high_resolution_clock::now();
	
	  //input
	  input(world,persData,colourValueGLMVector,running);

	  //updating 
	  update(world,persData,lastdt);

	  if (chrono::high_resolution_clock::now() > next_Game_Tick)
	  {
		  //rendering
		

		  render(VAO,EBO,world,persData,colourValueGLMVector,shaderProgram,viewMatrix,projectionMatrix);

		  next_Game_Tick += skipTicks;
	  }


	  chrono::high_resolution_clock::time_point dt = chrono::high_resolution_clock::now();
	  lastdt = chrono::duration_cast<chrono::duration<double>>(dt - t);



  }
  // Exit Game loop


  //de-allocate resorces
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  SDL_Quit();

  //Program Exits
  return 0;
}
