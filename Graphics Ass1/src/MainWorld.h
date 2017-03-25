#ifndef MAINWORLD_H
#define MAINWORLD_H

#include "SDL.h"
#include "MainWorld.h"
#include "Sprite.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

using namespace std;


class MainWorld
{
public:
	//this class stores alot of the data used in my game.
	

	
	MainWorld();
	void setUpEnermies(float entitieSize);

	~MainWorld();


	
	bool playerFire;
	bool rorate = false;

	float mobSpeed = 0.4f;
	
	vector<Sprite> enermieSp;
	vector<Sprite> bullets;
	vector<Sprite> enermieBullets;
	Sprite player;
	





};


#endif