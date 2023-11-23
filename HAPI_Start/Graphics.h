#pragma once

#include <HAPI_lib.h>
#include "Rectangle.h"

using namespace HAPISPACE;

#include <unordered_map>

class Sprite;

class Graphics
{
private:
	BYTE* screen{ nullptr };

	std::unordered_map<std::string, Sprite*> m_spriteMap;

	BYTE* backgroundTexture{ nullptr };
	int bTexWidth, bTexHeight;

	Rectangle screenRect;

public:
	Graphics();
	void Initialise();
	void ClearToColour(HAPI_TColour colour);
	bool CreateSprite(const std::string& filename, const std::string& name);
	void DrawBackground();
	void DrawSprite(const std::string& name, int sx, int sy); 
	void DeleteTextures();

	int getSpriteWidth(const std::string& name);
	int getSpriteHeight(const std::string& name);

	int width{ 1024 };
	int height{ 768 };

};

