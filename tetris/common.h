#pragma once
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <cstdlib>
#include "CRectangle.h"

using namespace std;

int GetRandomNumber(int min, int max);

CRectangle& GetVectorPointsBounds(vector<Point>& vector);

bool IsIntersectVectors(vector<Point>& v1, vector<Point>& v2);