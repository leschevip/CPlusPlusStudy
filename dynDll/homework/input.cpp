#include "input.h"
#include "pch.h"

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
}