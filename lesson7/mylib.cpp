#include "mylib.h"

using namespace std;
using namespace input;

namespace mylib
{
    // он здесь лишний но так надо по заданию
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
}