#pragma once
#include <vector>
#include <exception>
#include "MyIterator.h"

template<typename T>
class MyContainer
{
private:
	T* _values;
	int _size;
public:

	MyContainer(int size) : _size(size)
	{
		_values = new T[_size];
	}

	MyIterator<T> begin()
	{
		return MyIterator<T>(_values);
	}

	MyIterator<T> end()
	{
		return MyIterator<T>(_values + _size);
	}

	T& operator[](int i)
	{
		if (i >= _size)
			throw exception("index out of range");

		return _values[i];
	}
};