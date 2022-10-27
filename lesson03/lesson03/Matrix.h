#pragma once
#include <array>
#include <random>
#include <iostream>
//#include <numeric>
//#include <algorithm>
//#include <ctime>
//#include <iomanip>

using namespace std;

template<typename T, int N>
class Matrix
{
private:
	array<array<T, N>, N> _data;
	int _size;
	
public:
	Matrix() : _size(N) 
	{
	}

	void FillRandom(T min, T max)
	{
		random_device rdm;
		mt19937_64 generator(rdm());
		uniform_int_distribution<T> dis(min, max);
		for (size_t i = 0; i < _size; i++)
		{
			for (size_t j = 0; j < _size; j++)
			{
				_data[i][j] = dis(generator);
			}
		}
	}

	int Det()
	{
		return 0;
	}

	iostream& operator << (iostream& in)
	{
		for (size_t i = 0; i < _size; i++)
		{
			for (size_t j = 0; j < _size; j++)
			{
				in << _data[i][j] << " ";
			}
			in << endl;
		}
	}
	
};
