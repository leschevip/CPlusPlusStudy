#include "common.h"

extern const uint32_t HEIGHT_SCORE_PANEL = 3;
extern const uint32_t WIDTH_PREWIEW_PANEL = 30;
extern const char8_t C_EMPTY_CHAR = ' ';
extern const char8_t C_BOUNDS_CHAR = '#';
extern const float H_FLOAT_MIN = 0.0f;
extern const float H_FLOAT_MAX = 1.0f;
extern const float V_FLOAT_MIN = 0.0f;
extern const float V_FLOAT_MAX = 1.0f;
extern const int32_t E_ESC = 27;
extern const int32_t E_SPACE_KEY = 32;

int GetRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // ���������� ������������ ��������� ����� � ����� ���������
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
CRectangle& GetVectorPointsBounds(vector<Point>& v)
{
	int l = 0, t = 0, r = 0, b = 0;
	if (v.size() > 0)
	{
		auto point = v.at(0);
		l = point.x;
		t = point.y; 
		r = point.x; 
		b = point.y;
		for (auto point : v)
		{
			if (l > point.x)
				l = point.x;
			if (r < point.x)
				r = point.x;
			if (t > point.y)
				t = point.y;
			if (b < point.y)
				b = point.y;
		}
	}
	
	CRectangle size(l, t, r, b);
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