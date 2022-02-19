#pragma once

#include <random>
#include <chrono>
#include <iostream>
#include <functional>
#include <string>
#include "input.h"

#define OUT
#define NAME_OF(v) #v
#define TRUE_STR "TRUE"
#define FALSE_STR "FALSE"
#define IS_POSITIVE_AND_LESS_THAN(val, upper) cout << (val >= 0 && val < upper ? TRUE_STR : FALSE_STR);
#define GET_ARRAY_SIZE input::InputNumber<size_t>("array size")

using namespace std;

namespace mylib
{
	
	void PrintArr(float* arr, const size_t size);

	float* InitArr(size_t size);

	void PositiveAndNegativeCountValues(const float* const arr, const size_t size, OUT size_t& positiveValuesCount, OUT size_t& negativeValuesCount);

	float GetRandomNumber(const float min, const float max, const int64_t seed);
}