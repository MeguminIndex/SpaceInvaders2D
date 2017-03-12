#ifndef MAINWORLD_H
#define MAINWORLD_H

#include "SDL.h"
#include "MainWorld.h"
#include "Sprite.h"

#include <vector>
#include <iostream>

using namespace std;


class MainWorld
{
public:
	//this class stores alot of the data used in my game.
	

	
	MainWorld();
	void setUpEnermies(int ammount);

	~MainWorld();


	bool Applytexture;
	bool ApplyRotate;
	

	
	vector<Sprite> enermieSp;
	Sprite player;






};


#endif