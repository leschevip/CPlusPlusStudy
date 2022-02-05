#include <iostream>
#include <string>
#include <functional>
#define NAME_OF(v) #v

using namespace std;


int32_t GetInput(const string& varName)
{
    int32_t v{ 0 };
    do
    {
        cout << "Input " << varName << ": ";
        cin >> v;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            v = 0;
            cout << "Unknown intput, repeat please.\n";
        }
    } while (v == 0);
    return v;
}

const string STR_TRUE = "true";
const string STR_FALSE = "false";

// if else
void Task1()
{
    cout << NAME_OF(Task1:) << endl;
    auto a = GetInput(NAME_OF(a));
    auto b = GetInput(NAME_OF(b));
    auto sum = a + b;
    cout << NAME_OF(a+b=) << (sum >= 10 && sum <= 20 ? STR_TRUE : STR_FALSE) << endl;

    /*if (sum >= 10 && sum <= 20)
        cout << STR_TRUE << endl;
    else
        cout << STR_FALSE << endl;*/
};

// if else
void Task2()
{
    cout << NAME_OF(Task2:) << endl;
    const int32_t RES = 10;
    const int32_t A = 5;
    const int32_t B = 5;
    const bool resBool = (A == RES && B == RES) || (A + B == RES);
    
    if (resBool)
        cout << STR_TRUE << endl;
    else
        cout << STR_FALSE << endl;

    cout << NAME_OF(result=) << (resBool ? STR_TRUE : STR_FALSE) << endl;
};

// output odd numbers;
void Task3()
{
    cout << NAME_OF(Task3:) << endl;
    const string COMMA = ",";
    const string EMPTY = "";
    const size_t FROM = 1;
    const size_t TO = 50;

    cout << "Your numbers: \n";
    cout << "method 1: ";
    string out(EMPTY);
    for (auto i = FROM; i <= TO; i++)
    {
        if (i & 1)
            out += to_string(i) + COMMA;
    }
    out.pop_back();
    cout << out << endl;
    cout << "method 2: ";
    out = EMPTY;
    for (auto i = FROM; i <= TO; i++)
    {
        if (i % 2 != 0)
            out += to_string(i) + COMMA;
    }
    out.pop_back();
    cout << out << endl;
};

// simple value check

void Task4()
{
    cout << NAME_OF(Task4:) << endl;
    const uint32_t START = 2;

    uint32_t value = GetInput(NAME_OF(value));
    uint32_t dd = START;
    while (value % dd != 0)
    {
        dd++;
    }
    cout << "Value is" << (value != dd ? " not " : " ") << "simple";
}

void Task5()
{
    cout << NAME_OF(Task5:) << endl;
    const uint32_t START_YEAR = 1;
    const uint32_t END_YEAR = 3000;
    const uint32_t EACH_4 = 4;
    const uint32_t EACH_100 = 100;
    const uint32_t EACH_400 = 400;
    int32_t year(0);
    bool condition(true);
    do
    {
        year = GetInput(NAME_OF(year));
        condition = year <= START_YEAR || year >= END_YEAR;
        if (condition)
            cout << "Please enter again." << endl;
    } while (condition);
    
    bool isLeap = (year % EACH_400 == 0) || ((year % EACH_4 == 0) && (year % EACH_100 != 0));
    cout << year << (isLeap ? " " : " not ") << "leap year" << endl;
}


int main()
{
    Task1();
    Task2();
    Task3();
    Task4();
    Task5();
}
