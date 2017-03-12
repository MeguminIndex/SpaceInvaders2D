#include "gameSetUp.h"
#include "SDL.h"
#include "SDL_mixer.h"


#include "PersistantData.h"
#include "MainWorld.h"
//#include "fontManager.h"


#include <iostream>



using namespace std;
gameSetUp::gameSetUp()
{
}

void gameSetUp::setGameUp(PersistantData* persData,MainWorld* world)
{




	//Mix_PlayMusic(persData->backingMusic, -1);

	//order Top, Bottom,Left,Right



	//int boundryWallX[4] = { 13,13,13,35 };


	//represent  the walls y position
	//int boundryWallY[4] = { 3,35,3,3 };
	//represents width
	//int boundryWallWidth[4] = { 22,22,1,1 };
	//represents height
	//int boundryWallHeight[4] = { 1,1,33,33 };


	int topLeftGameX = -1;
	
	int topLeftGameY = 1;
	//world->topLeftGameY = topLeftGameY;

	float playerSizeS = persData->playerSize;

	/*for (int i = 0; i <= 4; i++)
	{
		Sprite tmpSprite(playerSizeS*boundryWallWidth[i], playerSizeS* boundryWallHeight[i], "BoundryWall " + (char)i);
		tmpSprite.gameWorldX = playerSizeS* boundryWallX[i];
		tmpSprite.gameWorldY = playerSizeS* boundryWallY[i];
		world->wallsSp.push_back(tmpSprite);
	}*/
	//numbers represent how many playersize it is
	//order left to right
	//represents the wals x pos 


	//keycode:
	/*
	0 == nothing
	1 == walls
	2 == points
	3 == enermy



	*/

	//possible impliment a mini map feature or allow users to input their own level design as a string of numbers to be pushed into the array
	int worldLayout[31][21] = {
		{ 3,2,2,2,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,3 },
		{ 2,1,1,1,2,2,1,1,2,1,2,1,1,1,1,1,1,1,1,1,2 },
		{ 2,1,1,1,1,2,1,1,2,2,2,1,1,1,1,2,2,2,2,2,2 },
		{ 2,1,2,2,2,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,2 },
		{ 2,1,2,1,1,2,1,1,1,1,2,1,1,1,1,2,2,2,2,2,2 },
		{ 2,1,2,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,1,1 },
		{ 2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2 },
		{ 1,1,2,1,1,2,1,2,2,2,2,1,1,1,1,1,2,1,1,1,2 },
		{ 1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2 },
		{ 1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2 },
		{ 2,2,2,1,1,2,2,2,2,2,4,2,2,2,2,1,1,1,1,1,2 },
		{ 2,1,2,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,2 },
		{ 2,1,2,1,1,1,2,1,1,1,1,1,1,1,2,2,2,2,2,2,2 },
		{ 2,1,2,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,2 },
		{ 2,1,2,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,2 },
		{ 2,1,2,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,2 },
		{ 2,1,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2 },
		{ 2,2,2,2,2,2,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2 },
		{ 2,1,1,1,1,1,2,1,1,1,1,2,1,1,1,1,1,2,2,2,2 },
		{ 2,1,1,1,1,1,2,1,1,1,1,2,2,2,2,2,2,2,1,1,1 },
		{ 2,1,1,1,1,1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,1 },
		{ 2,2,2,2,2,2,2,1,1,1,1,2,1,1,1,1,1,2,1,1,1 },
		{ 1,1,1,1,1,1,2,1,1,1,1,2,2,2,2,2,2,2,2,2,2 },
		{ 1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,2,1,1,1,2 },
		{ 2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,2,1,1,1,2 },
		{ 2,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,2,2,2,2,2 },
		{ 2,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,2,1,1,1,2 },
		{ 2,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,2,1,1,1,2 },
		{ 2,1,1,1,1,1,2,1,1,1,1,1,1,1,2,2,2,2,2,1,2 },
		{ 2,1,1,1,1,1,2,1,1,2,2,2,2,1,2,1,1,1,2,1,2 },
		{ 3,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,3 }


	};


	float gap = 2;
	float pointSize = playerSizeS / 4;
	float pointOffSet = (playerSizeS / 2) - pointSize / 2;

	int numberOfPoints = 0;
	int counter = 0;

	int numberOfPlayers = 1;

	
	//creates world layout based on the matrix
	int numberMobs = 1;
	for (int j = 0; j <= 30; j++)
	{
		for (int i = 0; i <= 20; i++)
		{
			if (worldLayout[j][i] == 1)//walls
			{
			//	Sprite tmpSprite(playerSizeS - gap, playerSizeS - gap, to_string(counter));
			//	tmpSprite.gameWorldX = playerSizeS*(topLeftGameX + (i + 1)) + (gap / 2);
			//	tmpSprite.gameWorldY = playerSizeS* (topLeftGameY + (j + 1)) + (gap / 2);
			//	world->wallsSp.push_back(tmpSprite);
			}
			else if (worldLayout[j][i] == 2)//coins/points
			{
			//	Sprite tmpPointSprite(pointSize, pointSize, to_string(counter),500,276,250,276);
			//	tmpPointSprite.gameWorldX = (playerSizeS*(topLeftGameX + (i + 1))) + pointOffSet;
			//	tmpPointSprite.gameWorldY = playerSizeS* (topLeftGameY + (j + 1)) + pointOffSet;
			//	tmpPointSprite.score = 5;
			//	world->pointSprites.push_back(tmpPointSprite);

			//	numberOfPoints++;
			}
			else if (worldLayout[j][i] == 3)//mobs
			{
			//	Sprite tmpEnermySprite();
				//tmpEnermySprite.setGameWorldPos((playerSizeS*(topLeftGameX + (i + 1))), playerSizeS* (topLeftGameY + (j + 1)));
		//		string filename = "mob" + to_string(numberMobs) + ".png";
		//		numberMobs++;
		//		if (numberMobs >4)
		//		{
		//			numberMobs = 1;
		//		}
		//		tmpEnermySprite.loadAddTexture(persData->renderer, filename);
		//		tmpEnermySprite.direction = movementInput::Left;
			//	tmpEnermySprite.score = 2000;
		//		world->enermiesSp.push_back(tmpEnermySprite);
			}
			else if (worldLayout[j][i] == 4)//player spot
			{
				for (int n = 0; n<numberOfPlayers; n++)
				{

			//		Sprite tmpPlayer(playerSizeS, playerSizeS, "Player" + to_string(n + 1));

					//sets game world position as well as a secondary variable to keep track of respawn point
			//		tmpPlayer.setGameWorldPos((playerSizeS*(topLeftGameX + (i + 1))), playerSizeS* (topLeftGameY + (j + 1)));

			//		string filename = "packMan" + to_string(n) + ".bmp";
			//		tmpPlayer.loadAddTexture(persData->renderer, filename);
			//		tmpPlayer.lives = 2;
			//		world->playerSp.push_back(tmpPlayer);

				}

			}

			counter++;
		}
	}

	//world->numberOfPoints = numberOfPoints;


	//Setting up fontManager
//	fontManager* fontManage = new fontManager();
	//loading in the font sheet


	//float fontPosX = playerSizeS;
	//float fontPosY = playerSizeS * 2;

	//string OnScreenText[] = { "Player","Score","Lives" };

	//for (auto player : world->playerSp)
	//{
	//	OnScreenText[0] = player.name;
	//	for (auto word : OnScreenText)
	//	{
	//		world->OnScreenText.push_back(fontManage->textGenerator(word, playerSizeS, fontPosX, fontPosY));
	//		//fontPosX += playerSizeS *  (boundryWallWidth[0]);
	//		fontPosY += playerSizeS * 2;
	//	}

	//	fontPosY += playerSizeS;

	//}


}
gameSetUp::~gameSetUp()
{
}
