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

	// метод reset просто сбрасывает индекс
	// вопрос: нужно ли чистить при этом массив данных? если да, то как инициализировать значения массива по дефолту для T?
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

	// метод возврата значения из стека
	// здесь не хватает return в ветке else
	// вопрос: если не прерывать работу программы через throw exception и ограничиться выводом предупреждения, то каким образом правильно вернуть значение T в ветке else?
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