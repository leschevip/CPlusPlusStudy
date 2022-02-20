#pragma once

#include <random>
#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include <chrono>
#include "input.h"

#define OUT
#define NAME_OF(v) #v
#define TRUE_STR "TRUE"
#define FALSE_STR "FALSE"
#define IS_POSITIVE_AND_LESS_THAN(val, upper) cout << (val >= 0 && val < upper ? TRUE_STR : FALSE_STR);
#define GET_ARRAY_SIZE input::InputNumber<size_t>("array size")
#define SWAP(val1, val2) \
auto tmp = val1; \
val1 = val2; \
val2 = tmp;


using namespace std;

namespace mylib
{

	void PrintArr(float* arr, const size_t size);

	float* InitArr(size_t size);

	void PositiveAndNegativeCountValues(const float* const arr, const size_t size, OUT size_t& positiveValuesCount, OUT size_t& negativeValuesCount);

	float GetRandomNumber(const float min, const float max, const int64_t seed);

	void SortArr(int32_t* const arr, size_t size);

	#pragma pack (push, 8)
	struct Employee
	{
		int32_t id;
		unsigned short age;
		int64_t expirienceYears;
		unsigned char childCount;
	};
	#pragma pack (pop)

	Employee* NewEmployee();
	void SaveEmployeeToFile(const string& filename, const Employee* const empl);

	int Task1and5();
	
	int Task2();

	int Task3();

	int Task4();
}
