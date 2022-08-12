#pragma once

#include <type_traits>

using namespace std;

template<typename T>
class Stack
{
private:
	int size;
	int pos;
	T* arr;
public:
	Stack(int size = 10) : size(size), pos(-1)
	{
		arr = new T[size];
	}

	~Stack()
	{
		delete[] arr;
	}

	// ����� reset ������ ���������� ������
	// ������: ����� �� ������� ��� ���� ������ ������? ���� ��, �� ��� ���������������� �������� ������� �� ������� ��� T?
	void reset()
	{
		pos = -1;
	}

	bool push(const T& value)
	{
		if (pos < size)
		{
			arr[++pos] = value;
		}
		else
		{
			cout << "warning: stack is full";
		}
		return pos < size;
	}

	// ����� �������� �������� �� �����
	// ����� �� ������� return � ����� else
	// ������: ���� �� ��������� ������ ��������� ����� throw exception � ������������ ������� ��������������, �� ����� ������� ��������� ������� �������� T � ����� else?
	T& pop()
	{
		if (pos >= 0)
		{
			return arr[pos--];
		}
		else
		{
			cout << "warning: stack is empty";
		}
	}

	void print()
	{
		cout << "(";
		for (int i = 0; i <= pos; i++)
		{
			cout << arr[i];
			if (i != pos)
				cout << ", ";
		}
		cout << ")" << endl;
	}
};