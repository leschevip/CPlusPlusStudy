
#include <iostream>
#include <string>
#define NAME_OF(v) #v

using namespace std;

int GetInput(string varName)
{
    int v{ 0 };
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

void Task1()
{
    // Task 1
    cout << "Task1: " << endl;
    int a = GetInput(NAME_OF(a));
    int b = GetInput(NAME_OF(b));
    int c = GetInput(NAME_OF(c));
    int d = GetInput(NAME_OF(d));

    float resC = a * (b + (float)c / d);
    float resCpp = a * (b + c / static_cast<float>(d));
    cout << "resC = " << resC << endl;
    cout << "resCpp = " << resCpp << endl;
}

const int CONST_VALUE = 21;
void Task2()
{
    // Task 2
    cout << "Task2: " << endl;
    int k = GetInput(NAME_OF(k));
    int diff = (k < CONST_VALUE) ? k - CONST_VALUE
                                 : 2 * (k - CONST_VALUE);
    cout << "Difference between " << k << " and " << CONST_VALUE << " equals " << diff;
}

void Task3()
{
    cout << "Task3: " << endl;
    cout << "static init...";
    int arr[3][3][3] =
    {
        { {1,2,3}, {4,5,6}, {7,8,9} },
        { {10,11,12}, {13,14,15}, {16,17,18} },
        { {19,20,21}, {22,23,24}, {25,26,27} }
    };

    // access as index
    cout << "access as index: arr[1][1][1] = " << arr[1][1][1] << endl;
    
    // access as pointer
    cout << "access as pointer: arr[1][1][1] = " << *(*(*(arr + 1) + 1) + 1) << endl;

    cout << "dynamic init...";
    int v = 0;
    int*** arrPointer = new int**[3];
    for (int i = 0; i < 3; i++)
    {
        *(arrPointer + i) = new int*[3];
        for (int j = 0; j < 3; j++)
        {
            *(*(arrPointer + i) + j) = new int[3]
            {
               ++v,
               ++v,
               ++v
            };
        }
    }
    // access as index
    cout << "access as index: arr[1][1][1] = " << arrPointer[1][1][1] << endl;

    // access as pointer
    cout << "access as pointer: arr[1][1][1] = " << *(*(*(arrPointer + 1) + 1) + 1) << endl;

}

extern int a1;
extern int b1;
extern int c1;
extern int d1;

extern const int CONST_A1;
extern const int CONST_B1;
extern const int CONST_C1;
extern const int CONST_D1;

void Task4()
{
    cout << "Task4: " << endl;
    cout << "variable declared but not initialized in other cpp: " << endl;
    a1 = GetInput(NAME_OF(a1));
    b1 = GetInput(NAME_OF(b1));
    c1 = GetInput(NAME_OF(c1));
    d1 = GetInput(NAME_OF(d1));

    float resC = a1 * (b1 + (float)c1 / d1);
    float resCpp = a1 * (b1 + c1 / static_cast<float>(d1));
    cout << "resC = " << resC << endl;
    cout << "resCpp = " << resCpp << endl;

    cout << "constants declared and initialized in other cpp: " << endl;
    resC = CONST_A1 * (CONST_B1 + (float)CONST_C1 / CONST_D1);
    resCpp = CONST_A1 * (CONST_B1 + CONST_C1 / static_cast<float>(CONST_D1));
    cout << NAME_OF(CONST_A1) << " = " << CONST_A1 << endl;
    cout << NAME_OF(CONST_B1) << " = " << CONST_B1 << endl;
    cout << NAME_OF(CONST_C1) << " = " << CONST_C1 << endl;
    cout << NAME_OF(CONST_D1) << " = " << CONST_D1 << endl;
    cout << "resC = " << resC << endl;
    cout << "resCpp = " << resCpp << endl;
}

int main()
{
    Task1();
    Task2();
    Task3();
    Task4();
}
