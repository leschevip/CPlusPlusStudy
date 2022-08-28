#include <cassert>
#include <ostream>
#include <algorithm>
#include "sortalg.h"

using namespace std;

class ArrayInt
{
private:
	int m_length;
	int* m_data;

	int* cut(size_t from, size_t to)
	{
		assert(from >= 0 && from <= m_length && to >= 0 && to <= m_length && from <= to);

		if (from == 0 && to == m_length - 1)
		{
			return m_data;
		}

		int* newData = new int[to - from + 1];
		int i = 0;
		for (size_t idx = from; idx <= to; idx++)
		{
			newData[i] = m_data[idx];
			i++;
		}
		return newData;
	}

public:
	ArrayInt() : m_length(0), m_data(nullptr) { }

	ArrayInt(int length) : m_length(length)
	{
		assert(length >= 0);
		if (length > 0)
			m_data = new int[length];
		else
			m_data = nullptr;
	}

	ArrayInt(int length, int defv) : m_length(length)
	{
		if (length > 0)
		{
			m_data = new int[length];
			for (size_t i = 0; i < m_length; i++)
				m_data[i] = defv;
		}
		else
			m_data = nullptr;
	}

	~ArrayInt()
	{
		delete[] m_data;
	}

	void clear()
	{
		delete[] m_data;
		m_data = nullptr;
		m_length = 0;
	}

	int getLength() { return m_length; }

	int& operator[](int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}

	void resize(int newLength)
	{
		if (newLength == m_length)
			return;
		if (newLength <= 0)
		{
			clear();
			return;
		}

		int* data = new int[newLength];
		if (m_length > 0)
		{
			int elementsToCopy = (newLength > m_length) ? m_length : newLength;
			for (size_t index = 0; index < elementsToCopy; ++index)
				data[index] = m_data[index];
		}
		int* tmp = m_data;
		m_data = data;
		m_length = newLength;
		
		delete[] tmp;
	}

	void insert(int value, int index)
	{
		assert(index >= 0 && index <= m_length);
		int* data = new int[m_length + 1];
		for (size_t before = 0; before < index; ++before)
			data[before] = m_data[before];
		data[index] = value;
		
		for (size_t after = index; after < m_length; ++after)
			data[after + 1] = m_data[after];
		delete[] m_data;
		m_data = data;
		++m_length;
	}

	int popBack()
	{
		int v = m_data[m_length - 1];
		resize(m_length - 1);
		return v;
	}

	int popFront()
	{
		int v = m_data[0];
		if (m_length > 1)
		{
			int* newData = cut(1, m_length);
			delete[] m_data;
			m_data = newData;
			m_length--;
		}
		else
		{
			clear();
		}
		return v;
	}

	void sortAsc()
	{
		sortIntAscInserts(m_data, 0, m_length - 1);
	}

	friend ostream& operator<<(ostream& out, ArrayInt& arr)
	{
		for (size_t i = 0; i < arr.getLength(); i++)
		{
			out << arr[i] << (i < arr.getLength() ? " " : "");
		}	
		return out;
	}

};