#pragma once

#include <iostream>
#include <functional>
#include <string>

using namespace std;

#define NAME_OF(v) #v

template<typename T>
T GetInputNumber(const string& varName, function<bool(const T& val)> check)
{
    T v;
    do
    {
        cout << "Input " << varName << ": ";
        cin >> v;
        
        bool state = check(v) || cin.fail();
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        if (state)
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
bool numericCheck(const T& val)
{
    const unsigned short BIT_PER_BYTE = 8;
    const constexpr T MIN = numeric_limits<T>::min();
    bool sign = ((T)1 << (sizeof(T) * BIT_PER_BYTE - 1)) & val;
    return (MIN >= 0 && (MIN >= 0 && sign));
}

string GetInputString(const string& varName)
{
    string v;
    cout << "Input " << varName << ": ";
    getline(cin, v);
    return v;
}




template<typename T>
T Input(const string& varName)
{
    auto check = [](const T& val) { return numericCheck(val); };
    return GetInputNumber<T>(varName, check);
}

template<>
string Input(const string& varName)
{
    return GetInputString(varName);
}