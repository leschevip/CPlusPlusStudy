
#include "figure.h"

void printFigure(const Figure* f)
{
	cout << typeid(*f).name() << ".area() = " << f->area() << endl;
}