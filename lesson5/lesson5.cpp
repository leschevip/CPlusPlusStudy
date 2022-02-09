#include <iostream>
#include <functional>
#include <ctime>

#define SIZE_STATIC_ARR(arr) sizeof(arr)/sizeof(*arr);

using namespace std;

double_t RandomVal(const double_t& from, const double_t& to)
{
    auto f = static_cast<double_t>(rand()) / RAND_MAX;
    return from + f * (to - from);
}

// удобно передавать константный указатель на изменяемый массив
// и инициализировать массивы
void InitRandArr(double_t* const arr, const double_t& from, const double_t& to, const uint32_t& SIZE)
{
    srand(time(nullptr));
    for (size_t i = 0; i < SIZE; i++)
        arr[i] = RandomVal(from, to);
}

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

void InvertArrVals(bool* const arr, const uint32_t& size)
{
    if (arr == nullptr || size == 0)
        return;

    for (size_t i = 0; i < size; i++)
        arr[i] = !arr[i];
}

void InitSecuenceArr(int32_t* const arr, int32_t start, const uint32_t& size)
{
    if (arr == nullptr || size == 0)
        return;

    const int32_t DISTANCE = 3;
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = start;
        start += DISTANCE;
    }
}

template<typename T>
void OffsetArr(T* const arr, const size_t& size, int32_t n)
{
    if (arr == nullptr || size == 0)
        return;

    const size_t MAX_ARR_INDEX = size - 1;
    // используем прямой и обратных ход по массиву в зависимости от знака значения n
    const size_t V_GET_INDEX = n < 0 ? 0 : MAX_ARR_INDEX;
    const size_t V_PUT_INDEX = n < 0 ? MAX_ARR_INDEX : 0;
    const int32_t START_INDEX = n < 0 ? 1 : MAX_ARR_INDEX - 1;
    const int32_t END_INDEX = n < 0 ? MAX_ARR_INDEX : 0;
    const short INC = n < 0 ? 1 : -1;

    const auto cond =  (n < 0) ? [](const int32_t& v1, const int32_t& v2) { return v1 <= v2; }
                               : [](const int32_t& v1, const int32_t& v2) { return v1 >= v2; };

    while (n != 0)
    {
        auto value = arr[V_GET_INDEX];

        for (int32_t i = START_INDEX; cond(i, END_INDEX); i+=INC)
            arr[i - INC] = arr[i];
        arr[V_PUT_INDEX] = value;

        n += INC;
    }
}

bool CheckBalance(int32_t* const arr, const size_t size)
{
    if (arr == nullptr || size == 0)
        return false;

    size_t l = 0;
    size_t r = size - 1;
    int32_t lSum = arr[l];
    int32_t rSum = arr[r];

    while (r - l > 1)
    {
        if (lSum <= rSum)
        {
            lSum += arr[++l];
        }
        else
        {
            rSum += arr[--r];
        }
    }
    return lSum == rSum;
}

void Task1()
{
    cout << "Task1:" << endl;
    const uint32_t SIZE = 10;
    const double_t VALUE_FROM = -10.0;
    const double_t VALUE_TO = 10.0;

    double arr[SIZE];
    InitRandArr(arr, VALUE_FROM, VALUE_TO, SIZE);

    cout << "PrintArr:" << endl;
    PrintArr(arr, SIZE);
    cout << endl;
}

void Task2()
{
    cout << "Task2:" << endl;
    bool arr[] = { 0, 0, 0, 1, 1, 1, 0, 1, 0, 1 };
    const uint32_t SIZE = SIZE_STATIC_ARR(arr);
    cout << "Array:" << endl;
    PrintArr(arr, SIZE);

    InvertArrVals(arr, SIZE);

    cout << "Inverted array:" << endl;
    PrintArr(arr, SIZE);
    cout << endl;
}

void Task3()
{
    cout << "Task3:" << endl;
    const int32_t SECUENCE_START = 1;
    const uint32_t SIZE = 8;
    int32_t arr[SIZE];
    InitSecuenceArr(arr, SECUENCE_START, SIZE);
    PrintArr(arr, SIZE);
    cout << endl;
}

void Task4()
{
    cout << "Task3:" << endl;
    int32_t arr[] = { 1, 2, 3, 4, 10, 23, 453, 54 };
    const size_t SIZE = SIZE_STATIC_ARR(arr);
    const int32_t offset = 21;
    OffsetArr(arr, SIZE, offset);
    PrintArr(arr, SIZE);
    cout << endl;
}

void Task5()
{
    cout << "Task5:" << endl;
    const string STR_TRUE = "TRUE";
    const string STR_FALSE = "FALSE";

    int32_t arr[] = { 10, 1, 2, 3, 4 };
    const size_t SIZE = SIZE_STATIC_ARR(arr);
    
    cout << "Array: ";
    PrintArr(arr, SIZE);
    cout << "Array is" << (!CheckBalance(arr, SIZE) ? " not " : " ") << "balanced" << endl;
}

int main()
{
    Task1();
    cout << endl;
    Task2();
    cout << endl;
    Task3();
    cout << endl;
    Task4();
    cout << endl;
    Task5();
}