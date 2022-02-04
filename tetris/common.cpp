#include "common.h"

int GetRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
CRectangle& GetSize(vector<Point>& v)
{
	auto minx = (*std::min_element(v.begin(), v.end(), [](const Point p1, const Point p2) {
		return p1.x < p2.x;
		})).x;
	auto miny = (*std::min_element(v.begin(), v.end(), [](const Point p1, const Point p2) {
		return p1.y < p2.y;
		})).y;
	auto maxx = (*std::min_element(v.begin(), v.end(), [](const Point p1, const Point p2) {
		return p1.x > p2.x;
		})).x;
	auto maxy = (*std::min_element(v.begin(), v.end(), [](const Point p1, const Point p2) {
		return p1.y > p2.y;
		})).y;

	/*auto topLeft = *std::min(v.begin(), v.end(), compare);
	auto rightBottom = *std::max(v.begin(), v.end(), compare);*/
	CRectangle size(minx, miny, maxx, maxy);
	return size;
}

bool IsIntersectVectors(vector<Point> &v1, vector<Point> &v2)
{
	auto iterV1 = v1.begin();
	while (iterV1 != v1.end())
	{
		auto iterV2 = v2.begin();
		while (iterV2 != v2.end())
		{
			if (*iterV1 == *iterV2)
				return true;
			++iterV2;
		}
		++iterV1;
	}

	return false;
};