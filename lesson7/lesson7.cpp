#include <iostream>
#include "mylib.h"

using namespace std;
using namespace input;
using namespace mylib;

void Task1and5()
{
    cout << "Task1and5" << endl;
    const size_t SIZE = GET_ARRAY_SIZE;
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
    int* arr = InputNewArrayNumber<int32_t>("Create array:", SIZE);
    cout << "Before sort:" << endl;
    PrintArr(arr, SIZE);
    SortArr(arr, SIZE);
    cout << "After sort:" << endl;
    PrintArr(arr, SIZE);

    delete[] arr;
    cout << endl;
}

void Task4()
{
    cout << "Task4" << endl;
    Employee* empl = NewEmployee();
    cout << " size of employee: " << sizeof(*empl) << endl;
    string filename = InputString("file name for employee");
    SaveEmployeeToFile(filename, empl);
    delete empl;
    cout << endl;
}

int main()
{
    Task1and5();   
    Task2();
    Task3();
    Task4();
}
