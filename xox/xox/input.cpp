#include "input.h"

namespace input
{
    string InputString(const string& varName)
    {
        return GetInput<string>(varName, stringCheck);
    }

    bool stringCheck(const istream& in, const string& val)
    {
        return cin.fail();
    }

    bool stringNotEmptyCheck(const istream& in, const string& val)
    {
        const string EMPTY = "";
        return cin.fail() && val != EMPTY;
    }

    int32_t GetRandomNum(int32_t min, int32_t max)
    {
        const static auto seed = chrono::system_clock::now().time_since_epoch().count();
        static mt19937_64 generator(seed);
        uniform_int_distribution<int32_t> dis(min, max);
        return dis(generator);
    }
}