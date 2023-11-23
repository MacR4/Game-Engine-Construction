// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>

#include "Graphics.h"

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
void HAPI_Main()
{
	Graphics Graphics;

	Graphics.Initialise();

	int playerXPos{ 100 };
	int playerYPos{ 300 };

	const HAPI_TKeyboardData& keyData{ HAPI.GetKeyboardData() };

	while (HAPI.Update())
	{
		//clear the screen
		Graphics.ClearToColour(HAPI_TColour(0, 0, 0));

		//check if user has made an input

		//WASD keys for movement
		if (keyData.scanCode['W'] == true)
			if (playerYPos)//> 0)
				playerYPos--;
		if (keyData.scanCode['S'] == true)
			if (playerYPos)// < Graphics.height - Graphics.getSpriteHeight("playerSprite"))
				playerYPos++;
		if (keyData.scanCode['A'] == true)
			if (playerXPos)//> 0)
				playerXPos--;
		if (keyData.scanCode['D'] == true)
			if (playerXPos)//< Graphics.width - Graphics.getSpriteWidth("playerSprite"))
				playerXPos++;

		//drawing background to screen
		Graphics.DrawBackground();

		//drawing sprites to the screen 
		//make sure they have been created in Graphics.Initialise
		Graphics.DrawSprite("playerSprite", playerXPos, playerYPos);

	}

	//delete textures afterwards to avoid memory leak
	Graphics.DeleteTextures();
}

