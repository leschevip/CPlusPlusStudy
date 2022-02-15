// lesson6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;
using ushort = unsigned short;

template<typename T>
void PrintArr(const T* const arr, const size_t& size)
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
T GetInput(const string& varName)
{
    constexpr T max = numeric_limits<T>::max();
    constexpr T min = numeric_limits<T>::min();
    T v(max);
    do
    {
        cout << "Input " << varName << ": ";
        cin >> v;
        bool sign = (1 << (sizeof(T) * 8 - 1)) & v;

        if (cin.fail() || (min >= 0 && sign))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Unknown intput, repeat please.\n";
        }
        else
        {
            break;
        }
    } 
    while (true);
    return v;
}

ushort GetTask1ArraySize()
{
    const ushort MAX_ARR_COUNT = sizeof(int32_t) * 8 + 1;
    ushort size(0);
    do
    {
        size = GetInput<ushort>("Input array size");
        if (size > MAX_ARR_COUNT)
            cout << "Size of array can't be greater than " << MAX_ARR_COUNT << " for condition task.\n";
    } while (size > MAX_ARR_COUNT);
}

void FillArrayPowOfTwo(size_t* arr, size_t size)
{
    size_t v(1);
    for (ushort i = 0; i < size; i++)
    {
        arr[i] = v;
        v *= 2;
    }
}

void Task1()
{
    cout << "Task1:" << endl;
    size_t* arr(nullptr);
    try
    {
        ushort size = GetTask1ArraySize();
        arr = new size_t[size]{ 0 };
        FillArrayPowOfTwo(arr, size);
        PrintArr(arr, size);
        delete[] arr;
    }
    catch (exception e)
    {
        cout << e.what();
        if (arr == nullptr)
        {
            delete[] arr;
            arr = nullptr;
        }
    }
}

int main()
{
    Task1();
}