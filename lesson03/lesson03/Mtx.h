#pragma once
#include <array>
#include <cmath>
#include <random>
#include <iostream>
#include <tuple>
#include <numeric>
#include <algorithm>
//#include <ctime>
//#include <iomanip>

using namespace std;

template<typename T, int N>
class Mtx
{
private:
	array<array<T, N>, N> _data;
	int _size;

	T Det(vector<int>& rows, vector<int>& cols, const int& newSize)
	{
		if (newSize == 1)
		{
			return _data[0][0];
		}
		else if (newSize == 2)
		{
			return _data[rows[0]][cols[0]] * _data[rows[1]][cols[1]] - _data[rows[0]][cols[1]] * _data[rows[1]][cols[0]];
		}
		else
		{
			if (rows.size() == 0)
			{
				rows.reserve(newSize);
				for (size_t i = 0; i < newSize; i++)
					rows.push_back(i);
			}

			if (cols.size() == 0)
			{
				cols.reserve(newSize);
				for (size_t i = 0; i < newSize; i++)
					cols.push_back(i);
			}

			T det = 0;
			for (size_t k = 0; k < newSize; k++)
			{
				vector<int> newRows;
				vector<int> newCols;
				newRows.reserve(newSize - 1);
				newCols.reserve(newSize - 1);

				for (size_t i = 1; i < newSize; i++)
					newRows.push_back(rows[i]);

				for (size_t i = 0; i < newSize; i++)
				{
					if (i == k)
						continue;
					newCols.push_back(cols[i]);
				}

				det += pow(-1, k + 2) * _data[rows[0]][cols[k]] * Det(newRows, newCols, newSize - 1);
			}

			return det;
		}
		return 0;
	}
	

public:
	Mtx() : _size(N)
	{
		
	}

	void FillRandom(T min, T max)
	{
		random_device rdm;
		mt19937_64 generator(rdm());
		uniform_int_distribution<T> dis(min, max);
		for (size_t i = 0; i < _size; i++)
			for (size_t j = 0; j < _size; j++)
				_data[i][j] = dis(generator);
	}

	T Det()
	{
		vector<int> r, c;
		return Det(r, c, _size);
	}

	template<typename T, int N>
	friend ostream& operator << (ostream& out, const Mtx<T, N>& m);

};

template<typename T, int N>
ostream& operator << (ostream& out, const Mtx<T, N>& m)
{
	for (size_t i = 0; i < m._size; i++)
	{
		for (size_t j = 0; j < m._size; j++)
			out << m._data[i][j] << " ";
		out << endl;
	}
	return out;
}
