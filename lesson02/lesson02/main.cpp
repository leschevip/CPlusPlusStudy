#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <chrono>


using namespace std;


template<typename T>
void swap(const T** x, const T** y)
{
	const T** t = x;
	x = y;
	y = t;
}

template<typename T>
void SortPointers(vector<T*>* vec)
{
	sort(vec->begin(), vec->end(), [](T* lItem, T* rItem) { return *lItem < *rItem; });
}

void Task1()
{
	cout << "Task1:" << endl;
	int x = 10;
	int y = 100;
	const int* xPtr = &x;
	const int* yPtr = &y;
	cout << "values: x = " << *xPtr << " y = " << *yPtr << endl;
	cout << "pointers x = " << xPtr << " y = " << yPtr << endl;
	swap(xPtr, yPtr);
	cout << "pointers x = " << xPtr << " y = " << yPtr << endl;
	cout << "values: x = " << *xPtr << " y = " << *yPtr << endl;
	cout << endl;
}

void Task2()
{
	cout << "Task2:" << endl;
	vector<int*>* v = new vector<int*>
	{
		new int(11),
		new int(10),
		new int(6),
		new int(7),
		new int(9),
		new int(1)
	};

	cout << "before sort:" << endl;
	for (int* val : *v)
		cout << *val << " ";
	cout << endl;
	
	SortPointers(v);
	cout << "after sort:" << endl;
	for (int* val : *v)
		cout << *val << " ";
	cout << endl;
	cout << endl;
}

int count_if_find_func(wstring& letters, wstring& str)
{
	return count_if(str.begin(), str.end(), [&letters](wchar_t& l) -> bool
	{
		return find(letters.begin(), letters.end(), l) != letters.end();
	});
}

int count_if_for_func(wstring& letters, wstring& str)
{
	return count_if(str.begin(), str.end(), [&letters](wchar_t& l) -> bool
	{
		for (size_t i = 0; i < letters.size(); i++)
		{
			if (letters[i] == l)
				return true;
		}
		return false;
	});
}

int for_find_func(wstring& letters, wstring& str)
{
	int count = 0;
	for (size_t i = 0; i < str.size();  i++)
	{
		if (find(letters.begin(), letters.end(), str[i]) != letters.end())
			count++;
	}
	return count;
}

int for_for_func(wstring& letters, wstring& str)
{
	int count = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		for (size_t k = 0; k < letters.size(); k++)
		{
			if (letters[k] == str[i])
			{
				count++;
				break;
			}
		}
	}
	return count;
}

void calculate()
{
	wstring letters = L"אף‏מו¸‎ט";
	
	std::locale::global(std::locale("en_US.utf8"));
	wifstream f;
	f.imbue(locale("en_EN.utf8"));
	f.open("WarAndPeace.txt");

	if (f.is_open())
	{
		wstring str;
		long count_if_find_letters_count = 0;
		long count_if_for_letters_count = 0;
		long for_find_letters_count = 0;
		long for_for_letters_count = 0;

		chrono::steady_clock::time_point start;
		chrono::steady_clock::time_point end;
		chrono::duration<double, ratio<1, 1>> time;
		double count_if_find_duration = 0;
		double count_if_for_duration = 0;
		double for_find_duration = 0;
		double for_for_duration = 0;

		while (getline(f, str))
		{
			start = chrono::steady_clock::now();
			count_if_find_letters_count += count_if_find_func(letters, str);
			end = chrono::steady_clock::now();
			time = end - start;
			count_if_find_duration += time.count();

			start = chrono::steady_clock::now();
			count_if_for_letters_count += count_if_for_func(letters, str);
			end = chrono::steady_clock::now();
			time = end - start;
			count_if_for_duration += time.count();

			start = chrono::steady_clock::now();
			for_find_letters_count += for_find_func(letters, str);
			end = chrono::steady_clock::now();
			time = end - start;
			for_find_duration += time.count();

			start = chrono::steady_clock::now();
			for_for_letters_count += for_for_func(letters, str);
			end = chrono::steady_clock::now();
			time = end - start;
			for_for_duration += time.count();
		}

		cout << "count_if_find_count = " << count_if_find_letters_count << " with time: " << count_if_find_duration << "s" << endl;
		cout << "count_if_for_count = " << count_if_for_letters_count << " with time: " << count_if_for_duration << "s" << endl;
		cout << "for_find_count = " << for_find_letters_count << " with time: " << for_find_duration << "s" << endl;
		cout << "for_for_count = " << for_for_letters_count << " with time: " << for_for_duration << "s" << endl;
	}

	f.close();
}

void Task3()
{
	calculate();
}

int main()
{
	Task1();
	Task2();
	Task3();
}