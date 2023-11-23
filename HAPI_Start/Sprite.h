#pragma once

#include <HAPI_lib.h>

#include "Rectangle.h"

using namespace HAPISPACE;

class Sprite
{
private:
	int m_width;
	int m_height;
	BYTE* m_texture{ nullptr };
	

public:
	bool Create(const std::string& filename);
	bool Draw(int sx, int sy, BYTE* screen, Rectangle screenRect);
	int screenWidth{ 1024 };
	int screenHeight{ 768 };
	int getWidth() const { return m_width; };
	int getHeight() const { return m_height; };
	~Sprite();
};

