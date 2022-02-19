#include "mylib.h"

using namespace std;
using namespace chrono;
using namespace input;

namespace mylib
{
    // �� ����� ������ �� ��� ���� �� �������
    void PrintArr(float* arr, const size_t size)
    {
        input::PrintArr<float>(arr, size);
    }

    float* InitArr(size_t size)
    {
        const float LOWER = -1.0f;
        const float UPPER = 1.0f;
        const auto seed = chrono::system_clock::now().time_since_epoch().count();

        float* arr = new float[size];
        for (size_t i = 0; i < size; i++)
            arr[i] = GetRandomNumber(LOWER, UPPER, seed);

        return arr;
    }

    void PositiveAndNegativeCountValues(const float* const arr, const size_t size, OUT size_t& positiveValuesCount, OUT size_t& negativeValuesCount)
    {
        for (size_t i = 0; i < size; i++)
        {
            if (arr[i] != 0)
                arr[i] < 0 ? negativeValuesCount++ : positiveValuesCount++;
        }
    }

    float GetRandomNumber(const float min, const float max, const int64_t seed)
    {
        static mt19937_64 generator(seed);
        uniform_real_distribution<float>dis(min, max);
        return dis(generator);
    }

    void SortArr(int32_t* const arr, size_t size)
    {
        for (size_t i = 1; i < size; i++)
        {
            for (size_t k = 0; k < size - i; k++)
            {
                if (arr[k] > arr[k + 1])
                {
                    SWAP(arr[k], arr[k + 1])
                }
            }
        }
    }
    
    Employee* NewEmployee()
    {
        Employee* empl = new Employee();
        empl->id = InputNumber<int32_t>("id");
        empl->age = InputNumber<unsigned short>("age");
        empl->expirienceYears = InputNumber<int64_t>("expirience years count");
        empl->childCount = InputNumber<unsigned char>("child count");
        return empl;
    }

    void SaveEmployeeToFile(const string& filename, const Employee* const empl)
    {
        ofstream fout(filename, ios::binary);
        if (fout.is_open())
        {
            fout.write((char*)empl, sizeof(Employee));
            cout << "Employee saved!";
            fout.close();
        }
        else
        {
            cout << "Something happened. Employee didn't save!";
        }
    }
}