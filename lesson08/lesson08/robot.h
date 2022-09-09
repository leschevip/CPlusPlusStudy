#pragma once

#include <exception>
#include <iostream>
#include <string>

using namespace std;

enum Direction
{
	TOP = 72,
	BOTTOM = 80,
	LEFT = 75,
	RIGHT = 77
};

class IllegalCommand : public exception
{
private:
	string message;
public:
	IllegalCommand(char c) 
		: message("Key <" + to_string(c) + "> is unknown direction")
	{
	}

	virtual char const* what() const
	{
		return message.c_str();
	}
};

class OffTheField : public exception
{
private:
	string message;
public:
	OffTheField(int x, int y, Direction d) 
		: message("Direction: " + getDirectionName(d) + ". Position (" + to_string(x) + ", " + to_string(y) + ")" + " is out of field")
	{
	}

	virtual char const* what() const
	{
		return message.c_str();
	}

	string getDirectionName(Direction d) const
	{
		string s = "";
		switch (d)
		{
		case Direction::TOP:
			s = "TOP";
			break;
		case Direction::BOTTOM:
			s = "BOTTOM";
			break;
		case Direction::LEFT:
			s = "LEFT";
			break;
		case Direction::RIGHT:
			s = "RIGHT";
			break;
		default:
			break;
		}
		return s;
	}
};


class Robot
{
private:
	int width;
	int height;
	int posX;
	int posY;

public:
	Robot(int width, int height, int x, int y) : width(width), height(height), posX(x), posY(y)
	{

	}

	void move(const char& chr)
	{
		short dx, dy;
		switch (chr)
		{
		case Direction::TOP:
			dy = -1;
			dx = 0;
			break;
		case Direction::BOTTOM:
			dy = 1;
			dx = 0;
			break;
		case Direction::LEFT:
			dx = -1;
			dy = 0;
			break;
		case Direction::RIGHT:
			dx = 1;
			dy = 0;
			break;
		default:
			throw IllegalCommand(chr);
		}
		
		if ((posX + dx >= width || posX + dx < 0) ||
			(posY + dy >= height || posY + dy < 0))
			throw OffTheField(posX + dx, posY + dy, (Direction)chr);

		posX += dx;
		posY += dy;

	}

	friend ostream& operator << (ostream& in, Robot& r)
	{
		for (int y = 0; y < r.height; y++)
		{
			string row;
			for (int x = 0; x < r.width; x++)
			{
				if (x == r.posX && y == r.posY)
				{
					row.append("[X] ");
				}
				else
					row.append("[ ] ");
			}
			in << row << endl;
		}

		return in;
	}

};