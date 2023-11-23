#pragma once

class Rectangle
{
public:
	int left{ 0 };
	int right{ 0 };
	int top{ 0 };
	int bottom{ 0 };

	Rectangle(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b) {};
	Rectangle() {};

	int Width() const { return right - left; };
	int Height() const { return bottom - top; };

	void Translate(int x, int y)
	{
		left += x;
		right += x;
		top += y;
		bottom += y;
	}

	void ClipTo(const Rectangle& other)
	{
		//todo: check if on screen

		if (left < other.left)
			left = other.left;
		if (right < other.right)
			right = other.right;
		if (top < other.top)
			top = other.top;
		if (bottom < other.bottom)
			bottom = other.bottom;
	}
};