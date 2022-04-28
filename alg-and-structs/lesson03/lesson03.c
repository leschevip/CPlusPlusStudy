#include <stdio.h>

#define X 5
#define Y 5
char obs[Y][X];


void translateRecursive(int v, int base)
{
	if (v == 0)
		return;

	translateRecursive(v / base, base);
	printf("%d", v % base);
}


int powerRecursive(int a, int b)
{
	if (b == 0)
		return 1;
	return a*powerRecursive(a, b-1);
}


int powerRecursive2(int a, int b)
{
	if (b == 0)
		return 1;

	if (!(b & 1))
	{
		return powerRecursive2(a*a, b / 2);
	}
	else
	{
		return a*powerRecursive2(a, b-1);
	}
}


void initObscales(int sizeX, int sizeY)
{
	for (int y = 0; y < sizeY; ++y)
		for (int x = 0; x < sizeX; ++x)
			obs[y][x] = 0;

	for (int y = 1; y < sizeY - 1; ++y)
		for (int x = 1; x < sizeX - 1; ++x)
			if (x == y)
				obs[y][x] = 1;
}

int routes(int x, int y)
{
	if (obs[y][x] == 1 || (x == 0 && y == 0))
		return 0;
	else if (x == 0 ^ y == 0)
		return 1;
	else
		return routes(x, y-1) + routes(x-1, y);
}


int main(int argv, char** argc)
{
	int v1 = 2057;
	int base = 2;
	printf("Value %d on base %d equal: ", v1, base);
	translateRecursive(v1, base);
	printf("\n");

	int a = 3;
	int b = 3;
	printf("Value %d to power %d equals %d\n", a, b, powerRecursive(a, b));

	a = 3;
	b = 4;
	printf("Value %d to power %d equals %d\n", a, b, powerRecursive2(a, b));


	initObscales(X, Y);
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			printf("%5d", routes(x,y));
		}
		printf("\n");
	}
}
