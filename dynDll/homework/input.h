#pragma once
#include <random>
#include <iostream>
#include <functional>
#include <string>

using namespace std;

namespace input
{
    using ushort = unsigned short;

    string InputString(const string& varName);

    bool stringCheck(const istream& in, const string& val);

    bool stringNotEmptyCheck(const istream& in, const string& val);

#pragma region templates

    template<typename T>
    void PrintArr(T* arr, const size_t size)
    {
        if (arr == nullptr || size == 0)
        {
            cout << "Array is null or empty";
            return;
        }

        for (size_t i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    template<typename T>
    T GetInput(const string& varName, function<bool(const istream& in, const T& val)> check)
    {
        T v;
        do
        {
            cout << "Input " << varName << ": ";
            // если вводить данные через пробел, то обрабатывается первое значение до пробела, дальше буфер все равно чистится.
            cin >> v;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (check(cin, v))
            {
                cout << "Unknown intput, repeat please.\n";
            }
            else
            {
                break;
            }
        } while (true);
        return v;
    }


    template<typename T>
    bool numericCheck(const istream& in, const T& val)
    {
        const ushort BIT_PER_BYTE = 8;
        const constexpr T MIN = numeric_limits<T>::min();
        bool sign = ((T)1 << (sizeof(T) * BIT_PER_BYTE - 1)) & val;
        return cin.fail() || (MIN >= 0 && (MIN >= 0 && sign));
    }

    template<typename T>
    T InputNumber(const string& varName)
    {
        auto check = [](const istream& in, const T& val) { return numericCheck(in, val); };
        return GetInput<T>(varName, check);
    }

    template<typename T>
    void InputArrayNumber(T* const arr, size_t size,  const string& varName)
    {
        cout << varName << endl;
        auto check = [](const istream& in, const T& val) { return numericCheck(in, val); };

        for (size_t i = 0; i < size; i++)
        {
            arr[i] = GetInput<T>("v[" + to_string(i) + "]", check);
        }

        cout << endl;
    }

    template<typename T>
    T* InputNewArrayNumber(const string& varName, size_t size)
    {
        T* arr = new T[size];
        InputArrayNumber<T>(arr, size, varName);
        return arr;
    }

#pragma endregion

}
