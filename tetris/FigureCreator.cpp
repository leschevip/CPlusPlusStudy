#include "FigureCreator.h"

Figure* Figure1()
{
	auto f = new Figure();
	auto vect = f->Points;
	
	vect.push_back({ 1, -3});
	vect.push_back({ 2, -3 });
	vect.push_back({ 3, -3 });
	vect.push_back({ 1, -2 });
	vect.push_back({ 2, -2 });
	vect.push_back({ 3, -2 });
	vect.push_back({ -2, -1 });
	vect.push_back({ -1, -1 });
	vect.push_back({ 0, -1 });
	vect.push_back({ 1, -1 });
	vect.push_back({ 2, -1 });
	vect.push_back({ 3, -1 });
	vect.push_back({ -2, 0 });
	vect.push_back({ -1, 0 });
	vect.push_back({ 0, 0 });
	vect.push_back({ 1, 0 });
	vect.push_back({ 2, 0 });
	vect.push_back({ 3, 0 });
	vect.push_back({ -2, 1 });
	vect.push_back({ -1, 1 });
	vect.push_back({ 0, 1 });
	vect.push_back({ 1, 1 });
	vect.push_back({ 2, 1 });
	vect.push_back({ 3, 1 });
	vect.push_back({ -1, 2 });
	vect.push_back({ -2, 2 });
	vect.push_back({ 0, 2 });
	vect.push_back({ -1, 3 });
	vect.push_back({ -2, 3 });
	vect.push_back({ 0, 3 });
	

	f->Points = vect;
	f->Size = GetSize(vect);
	return f;
}

Figure* FigureCreator::Create(FigureType typ)
{
	if (typ == FigureType::F1)
	{
		return Figure1();
	}
	throw;
}