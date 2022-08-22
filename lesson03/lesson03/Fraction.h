#pragma once

#include <exception>
#include <ostream>
#include <string>

using namespace std;

class Fraction
{
private:
	int up;
	int down;

public:
	Fraction(int up, int down) : up(up), down(down)
	{
		if (down == 0)
			throw exception("Zero denominator fraction!");
	}

	Fraction operator+(Fraction& fraction)
	{
		int newUp = 0, newDown = 0;

		if (down == fraction.down)
		{
			newUp = up + fraction.up;
			newDown = down;
		}
		else
		{
			newUp = up * fraction.down + fraction.up * down;
			newDown = fraction.down * down;
		}

		return Fraction(newUp, newDown);
	}

	Fraction operator-(Fraction& fraction)
	{
		int newUp = 0, newDown = 0;

		if (down == fraction.down)
		{
			newUp = up - fraction.up;
			newDown = down;
		}
		else
		{
			newUp = up * fraction.down - fraction.up * down;
			newDown = fraction.down * down;
		}

		return Fraction(newUp, newDown);
	}

	Fraction operator*(Fraction& fraction)
	{
		return Fraction(up*fraction.up, down*fraction.down);
	}

	Fraction operator/(Fraction& fraction)
	{
		return Fraction(up * fraction.down, down * fraction.up);
	}

	Fraction operator-()
	{
		return Fraction(-up, down);
	}

	bool operator==(Fraction& fraction)
	{
		return down == fraction.down && up == fraction.up;
	}

	bool operator!=(Fraction& fraction)
	{
		return down != fraction.down || up != fraction.up;
	}

	bool operator>(Fraction& fraction)
	{
		return up / down > fraction.up / fraction.down;
	}

	bool operator<(Fraction& fraction)
	{
		return up / down < fraction.up / fraction.down;
	}

	bool operator>=(Fraction& fraction)
	{
		return !(*this > fraction);
	}

	bool operator<=(Fraction& fraction)
	{
		return !(*this > fraction);
	}

	friend ostream& operator<<(ostream& in, Fraction& fraction)
	{
		in << fraction.up << "/" << fraction.down;
		return in;
	}
};