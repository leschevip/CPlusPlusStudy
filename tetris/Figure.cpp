#include "Figure.h"

Figure::Figure()
{

}

Figure::~Figure()
{
	Points.clear();
}

FigureInstance::FigureInstance(): Model(nullptr)
{
}

FigureInstance::FigureInstance(Figure* model, vector<Point>& points) : Model(model), Points(points), Size(nullptr)
{
	Size = new CRectangle(model->Size);
}

FigureInstance::~FigureInstance()
{
	Points.clear();
	delete Size;
	Model = nullptr;
}
