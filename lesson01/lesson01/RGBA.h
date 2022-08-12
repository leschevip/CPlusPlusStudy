#pragma once

#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

class RGBA
{
private:
	uint8_t red;
	uint8_t blue;
	uint8_t green;
	uint8_t alpha;

public:
	
	RGBA(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255) : red(red), green(green), blue(blue), alpha(alpha)
	{

	}

	RGBA(RGBA& color)
	{
		this->red = color.red;
		this->green = color.green;
		this->blue = color.blue;
		this->alpha = color.alpha;
	}

	~RGBA()
	{

	}

	void print()
	{
		cout << "RGBA color: (" << +red << "," << +green << "," << +blue << "," << +alpha << ")" << endl;
	}

	friend std::ostream& operator<<(std::ostream& out, const RGBA& c)
	{
		out << "(" << +c.red << "," << +c.green << "," << +c.blue << "," << +c.alpha << ")";
		return out;
	}
};