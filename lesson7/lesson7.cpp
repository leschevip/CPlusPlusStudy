#include <iostream>
#include "mylib.h"

using namespace std;
using namespace input;
using namespace mylib;

void Task1and5()
{
    cout << "Task1" << endl;
    const size_t SIZE = InputNumber<size_t>(NAME_OF(SIZE));
    float* arr = InitArr(SIZE);
    cout << "Array: ";
    PrintArr(arr, SIZE);
    cout << endl;

    size_t positiveCountValues = 0, negativeCountValues = 0;
    PositiveAndNegativeCountValues(arr, SIZE, positiveCountValues, negativeCountValues);
    cout << "Positive values count: " << positiveCountValues << ". Negative values count: " << negativeCountValues;

    delete[] arr;
    cout << endl;
}

void Task2()
{
    cout << "Task2" << endl;
    int32_t upperBound = InputNumber<int32_t>(NAME_OF(upperBound));
    int32_t value = InputNumber<int32_t>(NAME_OF(value));
    IS_POSITIVE_AND_LESS_THAN(value, upperBound);
    cout << endl;
}

void Task3()
{
    cout << "Task3" << endl;
    const size_t SIZE = GET_ARRAY_SIZE;
    int* arr = InputNewArrayNumber<int>("Create array from keyboard:", SIZE);
    PrintArr(arr, SIZE);

    delete[] arr;
    cout << endl;
}


int main()
{
 //   Task1and5();
    
 //   Task2();

    Task3();
}
