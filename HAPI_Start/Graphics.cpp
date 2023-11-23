#include "Graphics.h"
#include "Sprite.h"
#include "Rectangle.h"


void Graphics::Initialise()
{
	if (!HAPI.Initialise(width, height, "Kieran Rice - Games Engine Construction ICA"))
		return;

	Rectangle screenRect(0, 1024, 0, 768);

	screen = HAPI.GetScreenPointer();

	HAPI.SetShowFPS(true);
	
	//load background
	if (!HAPI.LoadTexture("Data/background.tga", &backgroundTexture, bTexWidth, bTexHeight))
	{
		HAPI.UserMessage("Texture not found", "Error");
		return;
	}

	//load all other sprites
	if (!CreateSprite("Data/alphaThing.tga", "playerSprite"))
	{
		HAPI.UserMessage("Texture not found", "Error");
		return;
	}
}

void Graphics::ClearToColour(HAPI_TColour colour)
{
	int offset = 0;
	for (int x = 0; x < width * height; x++)
	{
		screen[offset] = colour.red;
		screen[offset + 1] = colour.green;
		screen[offset + 2] = colour.blue;

		offset += 4;

	}
}

bool Graphics::CreateSprite(const std::string& filename, const std::string& name)
{
	//create a new sprite
	Sprite* newSprite = new Sprite;
	//if requested file doesnt exist then return false
	if (!newSprite->Create(filename))
	{
		return false;
	}
	//add the new sprite to the spritemap
	m_spriteMap[name] = newSprite;

	return true;
}

void Graphics::DrawBackground()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = x * 4 + y * width * 4;

			if (index >= 0 && index < width * height * 4)
			{
				memcpy(screen + index, backgroundTexture + index, 4);
			}
		}
	}
}

Graphics::Graphics()
{
}

void Graphics::DrawSprite(const std::string& name,int sx, int sy)
{
	//check if sprite is within spritemap
	std::unordered_map<std::string, Sprite*>::iterator it = m_spriteMap.find(name);
	if (it == m_spriteMap.end())
	{
		HAPI.UserMessage("Texture not found", "Error");
		return;
	}
	else
		m_spriteMap[name]->Draw(sx, sy, screen, screenRect);
}

void Graphics::DeleteTextures()
{
	//delete each sprite in the map
	for (std::unordered_map<std::string, Sprite*>::iterator it = m_spriteMap.begin(); it != m_spriteMap.end(); ++it)
	{
		delete it->second;
	}
	//clear the map
	m_spriteMap.clear();

	delete[] backgroundTexture;

}

int Graphics::getSpriteWidth(const std::string& name)
{
	std::unordered_map<std::string, Sprite*>::iterator it = m_spriteMap.find(name);
	if (it == m_spriteMap.end())
	{
		HAPI.UserMessage("Texture not found", "Error");
		return 0;
	}
	else
		return m_spriteMap[name]->getWidth();
}

int Graphics::getSpriteHeight(const std::string& name)
{

	std::unordered_map<std::string, Sprite*>::iterator it = m_spriteMap.find(name);
	if (it == m_spriteMap.end())
	{
		HAPI.UserMessage("Texture not found", "Error");
		return 0;
	}
	else
		return m_spriteMap[name]->getHeight();
}

