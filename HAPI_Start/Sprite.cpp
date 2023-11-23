#include "Sprite.h"

bool Sprite::Create(const std::string& filename)
{
	if (!HAPI.LoadTexture(filename, &m_texture, m_width, m_height))
	{
		HAPI.UserMessage("Texture not found", "Error");
		return false;
	}
	return true;
}

bool Sprite::Draw(int sx, int sy, BYTE* screen, Rectangle screenRect)
{

	Rectangle textureRect(0, m_width, 0, m_height);

	textureRect.Translate(sx, sy);

	textureRect.ClipTo(screenRect);

	textureRect.Translate(-sx, -sy);

	sx = std::max(0, sx);
	sy = std::max(0, sy);

	int screenOffset{ (sx + sy * screenWidth) * 4 };
	int texOffset{ (textureRect.top * m_width + textureRect.left) * 4 };

	int endOfLineScreenOffset{ (screenRect.Width() - textureRect.Width()) * 4 };
	int endOfLineTextureOffset{ (m_width - textureRect.Width()) * 4 };

	for (int y = 0; y < textureRect.Height(); y++)
	{
		for (int x = 0; x < textureRect.Width(); x++)
		{
			BYTE sourceAlpha = m_texture[texOffset + 3];
			//if source alpha is full then we can simply set the pixels to the source colour
			if (sourceAlpha == 255)
			{
				memcpy(screen + screenOffset, m_texture + texOffset, 4);
			}
			//if it is not then we will need to blend the source and background colours
			//if alpha is zero we dont have to do anything
			else if (sourceAlpha != 0)
			{
				//source
				BYTE sr = m_texture[texOffset];
				BYTE sg = m_texture[texOffset + 1];
				BYTE sb = m_texture[texOffset + 2];

				//background
				BYTE br = screen[screenOffset];
				BYTE bg = screen[screenOffset + 1];
				BYTE bb = screen[screenOffset + 2];

				float alpha = sourceAlpha / 255.0f;

				//final
				BYTE fr = alpha * sr + (1.0f - alpha) * br;
				BYTE fg = alpha * sg + (1.0f - alpha) * bg;
				BYTE fb = alpha * sb + (1.0f - alpha) * bb;

				//setting the pixels to the final rbg values
				screen[screenOffset] = fr;
				screen[screenOffset + 1] = fg;
				screen[screenOffset + 2] = fb;
			}
			texOffset += 4;//endOfLineTextureOffset;
			screenOffset += 4;//endOfLineScreenOffset;
		}
		screenOffset += endOfLineScreenOffset;//(screenWidth - m_width) * 4;
		texOffset += endOfLineTextureOffset;
	}

	return true;
}

Sprite::~Sprite()
{
	delete[] m_texture;
}
