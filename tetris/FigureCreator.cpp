#include "FigureCreator.h"

Figure* Figure1()
{
	auto f = new Figure();
	auto vect = f->Points();
	vect->push_back({ 1, -4 });
	vect->push_back({ 2, -4 });
	vect->push_back({ 3, -4 });
	vect->push_back({ 1, -3});
	vect->push_back({ 2, -3 });
	vect->push_back({ 3, -3 });
	vect->push_back({ 1, -2 });
	vect->push_back({ 2, -2 });
	vect->push_back({ 3, -2 });
	vect->push_back({ -2, -1 });
	vect->push_back({ -1, -1 });
	vect->push_back({ 0, -1 });
	vect->push_back({ 1, -1 });
	vect->push_back({ 2, -1 });
	vect->push_back({ 3, -1 });
	vect->push_back({ -2, 0 });
	vect->push_back({ -1, 0 });
	vect->push_back({ 0, 0 });
	vect->push_back({ 1, 0 });
	vect->push_back({ 2, 0 });
	vect->push_back({ 3, 0 });
	vect->push_back({ -2, 1 });
	vect->push_back({ -1, 1 });
	vect->push_back({ 0, 1 });
	vect->push_back({ 1, 1 });
	vect->push_back({ 2, 1 });
	vect->push_back({ 3, 1 });
	vect->push_back({ -1, 2 });
	vect->push_back({ -2, 2 });
	vect->push_back({ 0, 2 });
	vect->push_back({ -1, 3 });
	vect->push_back({ -2, 3 });
	vect->push_back({ 0, 3 });
	vect->push_back({ -1, 4 });
	vect->push_back({ -2, 4 });
	vect->push_back({ 0, 4 });

	return f;
}

Figure* Figure2()
{
	auto f = new Figure();
	auto vect = f->Points();
	vect->push_back({ -6, -1 });
	vect->push_back({ -5, -1 });
	vect->push_back({ -4, -1 });
	vect->push_back({ -3, -1 });
	vect->push_back({ -2, -1 });
	vect->push_back({ -1, -1 });
	vect->push_back({ 0, -1 });
	vect->push_back({ 1, -1 });
	vect->push_back({ 2, -1 });
	vect->push_back({ 3, -1 });
	vect->push_back({ 4, -1 });
	vect->push_back({ 5, -1 });
	vect->push_back({ 6, -1 });
	vect->push_back({ 7, -1 });
	vect->push_back({ -6, 0 });
	vect->push_back({ -5, 0 });
	vect->push_back({ -4, 0 });
	vect->push_back({ -3, 0 });
	vect->push_back({ -2, 0 });
	vect->push_back({ -1, 0 });
	vect->push_back({ 0, 0 });
	vect->push_back({ 1, 0 });
	vect->push_back({ 2, 0 });
	vect->push_back({ 3, 0 });
	vect->push_back({ 4, 0 });
	vect->push_back({ 5, 0 });
	vect->push_back({ 6, 0 });
	vect->push_back({ 7, 0 });
	vect->push_back({ -6, 1 });
	vect->push_back({ -5, 1 });
	vect->push_back({ -4, 1 });
	vect->push_back({ -3, 1 });
	vect->push_back({ -2, 1 });
	vect->push_back({ -1, 1 });
	vect->push_back({ 0, 1 });
	vect->push_back({ 1, 1 });
	vect->push_back({ 2, 1 });
	vect->push_back({ 3, 1 });
	vect->push_back({ 4, 1 });
	vect->push_back({ 5, 1 });
	vect->push_back({ 6, 1 });
	vect->push_back({ 7, 1 });

	return f;
}

Figure* Figure3()
{
	auto f = new Figure();
	auto vect = f->Points();
	vect->push_back({ -6, -1 });
	vect->push_back({ -5, -1 });
	vect->push_back({ -4, -1 });
	vect->push_back({ -3, -1 });
	vect->push_back({ -2, -1 });
	vect->push_back({ -1, -1 });
	vect->push_back({ 0, -1 });
	vect->push_back({ 1, -1 });
	vect->push_back({ 2, -1 });
	vect->push_back({ 3, -1 });
	vect->push_back({ 4, -1 });
	vect->push_back({ 5, -1 });
	vect->push_back({ 6, -1 });
	vect->push_back({ 7, -1 });
	vect->push_back({ -6, 0 });
	vect->push_back({ -5, 0 });
	vect->push_back({ -4, 0 });
	vect->push_back({ -3, 0 });
	vect->push_back({ -2, 0 });
	vect->push_back({ -1, 0 });
	vect->push_back({ 0, 0 });
	vect->push_back({ 1, 0 });
	vect->push_back({ 2, 0 });
	vect->push_back({ 3, 0 });
	vect->push_back({ 4, 0 });
	vect->push_back({ 5, 0 });
	vect->push_back({ 6, 0 });
	vect->push_back({ 7, 0 });
	vect->push_back({ -6, 1 });
	vect->push_back({ -5, 1 });
	vect->push_back({ -4, 1 });
	vect->push_back({ -3, 1 });
	vect->push_back({ -2, 1 });
	vect->push_back({ -1, 1 });
	vect->push_back({ 0, 1 });
	vect->push_back({ 1, 1 });
	vect->push_back({ 2, 1 });
	vect->push_back({ 3, 1 });
	vect->push_back({ 4, 1 });
	vect->push_back({ 5, 1 });
	vect->push_back({ 6, 1 });
	vect->push_back({ 7, 1 });
	vect->push_back({ -2, 2 });
	vect->push_back({ -1, 2 });
	vect->push_back({ 0, 2 });
	vect->push_back({ 1, 2 });
	vect->push_back({ 2, 2 });
	vect->push_back({ -2, 3 });
	vect->push_back({ -1, 3 });
	vect->push_back({ 0, 3 });
	vect->push_back({ 1, 3 });
	vect->push_back({ 2, 3 });
	vect->push_back({ -2, 4 });
	vect->push_back({ -1, 4 });
	vect->push_back({ 0, 4 });
	vect->push_back({ 1, 4 });
	vect->push_back({ 2, 4 });

	return f;
}

Figure* FigureCreator::Create(const FigureType& typ)
{
	if (typ == FigureType::F1)
	{
		return Figure1();
	}
	else if (typ == FigureType::F2)
	{
		return Figure2();
	}
	else if (typ == FigureType::F3)
	{
		return Figure3();
	}
	throw;
}