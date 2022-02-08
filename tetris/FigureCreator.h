#pragma once
#include "Figure.h"
#include "Perspective.h"



class FigureCreator
{
public:
	static Figure* Create(const FigureType& typ);
};