#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>


using namespace std;

using Glong = long long;
using Gdouble = long double;

//////////// Task1 объявление переменных разных типов данных и инициализация
void Task1()
{
    short si;
    si = numeric_limits<short>().max();
    short sj = 666;
    short sk{ 666 };

    int ii;
    ii = numeric_limits<int>().max();
    int ij = 999;
    int ik{ 999 };

    long li;
    li = numeric_limits<long>().max();
    long lj = 2022;
    long lk{ 2022 };

    Glong gi;
    gi = numeric_limits<Glong>().min();
    Glong gj = -20222022;
    Glong gk{ -20222022 };

    char echr;
    echr = numeric_limits<char>().min();
    char chr = 13;
    char schr{ 'G' };

    bool bi;
    bi = true;
    bool bj = true;
    bool bk{ false };

    float fi;
    fi = numeric_limits<float>().lowest();
    float fj = M_PI;
    float fk{ M_PI };

    double di;
    di = numeric_limits<double>().max();
    double dj = M_PI_4;
    double dk{ M_PI_2 };

    long double ldi;
    ldi = numeric_limits<long double>().max();
    long double ldj = M_E;
    long double ldk{ M_E };

    uint32_t uii;
    uii = numeric_limits<uint32_t>().max();
    uint32_t uij = 2200;
    uint32_t uik{ 2'100'000 };

    auto variable = 2'100'000UL;
}

//////////// Task2 перечисление
// enum class более безопасное объявление. Для использования значения еnum прежде необходимо указывать имя enum.
enum class ValueType
{
    EMPTY,
    CROSS,
    ZERO
};

//////////// Task3 создание массивов ValueType'ов
void Task3()
{
    ValueType arr[3][3]
    {
        { ValueType::EMPTY, ValueType::EMPTY, ValueType::EMPTY },
        { ValueType::EMPTY, ValueType::EMPTY, ValueType::EMPTY },
        { ValueType::EMPTY, ValueType::EMPTY, ValueType::EMPTY }
    };

    int n = 3;
    ValueType** arrPointer = new ValueType*[n];
    for (int i = 0; i < n; i++)
        *(arrPointer + i) = new ValueType[n] { ValueType::EMPTY, ValueType::EMPTY, ValueType::EMPTY };
    
    for (int i = 0; i < n; i++)
        delete[] arrPointer[i];
    delete[] arrPointer;

    ValueType arr2[3][3]{(ValueType)0};
}

//////////// Task3 модель игры. Struct
const string CHOICE_QUESTION = "Item Choice (1 - CROSS, 2 - ZERO): ";
const string START_QUESTION = "Who will start? (1 - first player, 2 - second player): ";

struct Player
{
    string Name;
    ValueType Item;

    friend ostream& operator<<(ostream& os, const Player& v)
    {
        os << "Player name: " << v.Name << "\n"
           << "Choice: " << (v.Item == ValueType::CROSS ? "CROSS" : "ZERO");

        return os;
    }
};

struct AreaXox
{
    ValueType Values[3][3] = 
    {
        { ValueType::EMPTY, ValueType::EMPTY, ValueType::EMPTY },
        { ValueType::EMPTY, ValueType::EMPTY, ValueType::EMPTY },
        { ValueType::EMPTY, ValueType::EMPTY, ValueType::EMPTY }
    };

    Player Players[2] =
    {
        Player { "Player1", ValueType::EMPTY },
        Player { "Player2", ValueType::EMPTY }
    };
    
    Player* Winner;
    Player* WhoStart;

    ~AreaXox(void)
    {
        Winner = 0;
        WhoStart = 0;
    }
};


// поинициализируем структуру
unsigned short GetAnswer(string question, unsigned short maxVariantAnswer)
{
    unsigned short choice{ 0 };
    while (true)
    {
        cout << question; // "Item Choice (1 - CROSS, 2 - ZERO): ";
        cin >> choice;
        if (choice > maxVariantAnswer || choice == 0)
        {
            cout << "Unknown answer, repeat input please.\n";
        }
        else
        {
            break;
        }
    }
    return choice;
}

void SetPlayer(const AreaXox* model, Player* player)
{
    cout << "Name: ";
    cin >> player->Name;

    for (int i = 0; i < 2; i++)
    {
        const Player *curPlayer = &model->Players[i];
        if (player != curPlayer && curPlayer->Item != ValueType::EMPTY)
        {
            if (curPlayer->Item == ValueType::CROSS)
            {
                player->Item = ValueType::ZERO;
            }
            else if (curPlayer->Item == ValueType::ZERO)
            {
                player->Item = ValueType::CROSS;
            }
        }
    }
    
    if (player->Item == ValueType::EMPTY)
    {
        player->Item = (ValueType)GetAnswer(CHOICE_QUESTION, 2);
    }
}

void SetPlayerWhoStart(AreaXox* model)
{
    auto answer = GetAnswer(START_QUESTION, 2);
    model->WhoStart = &model->Players[answer - 1];
}

void Task4()
{
    auto model = AreaXox();
    cout << "Player 1 info:\n";
    SetPlayer(&model, &model.Players[0]);

    cout << "Player 2 info:\n";
    SetPlayer(&model, &model.Players[1]);

    SetPlayerWhoStart(&model);

    cout << endl;
    cout << model.Players[0] << "\n" << model.Players[1] << "\n\n";
    cout << model.WhoStart->Name << " is starting the game.";
    cout << endl;
}

//////////// Task5 Struct + Union
struct MyVariant
{
    union MyData {
        int vInt;
        float vFloat;
        char vChar;
    };

    MyData Value;
    unsigned int IsInt : 1;
    unsigned int IsFloat : 1;
    unsigned int IsChar : 1;

    friend ostream& operator<<(ostream& os, const MyVariant& v)
    {
        if (v.IsInt)
            os << v.Value.vInt;
        else if (v.IsChar)
            os << v.Value.vChar;
        else if (v.IsFloat)
            os << v.Value.vFloat;

        return os;
    }

    MyVariant()
        : IsChar(0), IsInt(0), IsFloat(0)
    {
    }

    // как то бы сделать один метод конструктора с generic типом. Делается только через шаблоны?
    MyVariant(char v)
        : IsChar(0), IsInt(0), IsFloat(0)
    {
        Set(v);
    }

    MyVariant(float v)
        : IsChar(0), IsInt(0), IsFloat(0)
    {
        Set(v);
    }

    MyVariant(int v)
        : IsChar(0), IsInt(0), IsFloat(0)
    {
        Set(v);
    }

    // нужно возвращать всегда правильный тип через единый метод Get
    // использовать auto в такой реализации не могу
    // не совсем понятно как можно использовать битовые флаги и возврат конкретного значения из MyData на основе них в одном методе. Снова через шаблоны?
    // можно конкретизировать значения в наследниках от MyVariant, и возвращать в зависимости от типа конкретное значение, 
    // но это будет долго работать и тогда не нужны ни битовые флаги ни union.
    MyVariant::MyData /*auto*/ Get()
    {
        /*
        if (IsChar)
            return Value.vChar;
        else if (IsInt)
            return Value.vInt;
        else if (IsFloat)
            return Value.vFloat;
        */
        return Value;
    }

    void Set(int v)
    {
        Value.vInt = v;
        IsInt = 1;
        IsFloat = 0;
        IsChar = 0;
    }

    void Set(float v)
    {
        Value.vFloat = v;
        IsInt = 0;
        IsFloat = 1;
        IsChar = 0;
    }

    void Set(char v)
    {
        Value.vChar = v;
        IsInt = 0;
        IsFloat = 0;
        IsChar = 1;
    }    
};

void Task5()
{
    char chr;
    cout << "Char: ";
    cin >> chr;
    MyVariant var{ chr };
    cout << var;
    cout << endl;

    int vInt;
    cout << "Int: ";
    cin >> vInt;
    MyVariant var1{ vInt };
    cout << var1;
    cout << endl;

    float vFloat;
    cout << "Float: ";
    cin >> vFloat;
    MyVariant var2{ vFloat };
    cout << var2;
    cout << endl;
}

int main()
{
    Task1();
    Task3();
    Task4();
    Task5();
}
