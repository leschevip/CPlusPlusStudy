#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <functional>
#include <cstdlib>
#include <filesystem>


using namespace std;
using ushort = unsigned short;
namespace fs = std::filesystem;

#pragma region Helper

template<typename T>
void PrintArr(const T* const arr, const size_t size)
{
    if (arr == nullptr || size == 0)
    {
        cout << "Array is null or empty";
        return;
    }

    for (size_t i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

template<typename T>
void PrintArr(T** const arr, const size_t sizeX, const size_t sizeY)
{
    if (arr == nullptr || sizeX == 0 || sizeY == 0)
    {
        cout << "Array is null or empty";
        return;
    }

    for (size_t i = 0; i < sizeY; i++)
    {
        for (size_t j = 0; j < sizeX; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

template<typename T>
bool numericCheck(const istream& in, const T& val)
{
    const ushort BIT_PER_BYTE = 8;
    const constexpr T MIN = numeric_limits<T>::min();
    bool sign = ((T)1 << (sizeof(T) * BIT_PER_BYTE - 1)) & val;
    return cin.fail() || (MIN >= 0 && (MIN >= 0 && sign));
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

template<typename T>
T GetInput(const string& varName, function<bool(const istream& in, const T& val)> check)
{
    T v;
    do
    {
        cout << "Input " << varName << ": ";
        // если вводить данные через пробел, то обрабатывается первое значение до пробела, дальше буфер все равно чистится.
        cin >> v;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (check(cin, v))
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
T InputNumber(const string& varName)
{
    auto check = [](const istream& in, const T& val) { return numericCheck(in, val); };
    return GetInput<T>(varName, check);
}

string InputString(const string& varName)
{
    return GetInput<string>(varName, stringCheck);
}

string InputNotEmptyString(const string& varName)
{
    return GetInput<string>(varName, stringNotEmptyCheck);
}

size_t InputArraySize(const size_t max = numeric_limits<size_t>::max())
{
    size_t size(0);
    bool condition(true);
    do
    {
        size = InputNumber<size_t>("Array size");

        condition = size > max || size <= 0;
        if (condition)
            cout << "Size of array must by greater than 0 and less than " << max << "\n";

    } while (condition);

    return size;
}

int64_t GetRandomNumber(const int64_t min, const int64_t max, const int64_t seed)
{
    static mt19937_64 generator(seed);
    uniform_int_distribution<int64_t>dis(min, max);
    return dis(generator);
}

#pragma endregion



void FillArrayPowOfTwo(size_t* const arr, const size_t size)
{
    arr[0] = 1;
    const size_t MAX_POW = sizeof(size_t) * 8;
    for (size_t i = 1; i < size; i++)
    {
        arr[i] = i != MAX_POW ? arr[i - 1] * 2 : numeric_limits<size_t>::max();
    }
}

void Task1()
{
    cout << "Task1:" << endl;
    // возвести двойку в степень, большую чем позволяет тип нельзя, поэтому запрашиваем размер массива с учетом верхней границы
    const size_t MAX_ARR_COUNT = sizeof(size_t) * 8 + 1;
    auto size = InputArraySize(MAX_ARR_COUNT);
    size_t* arr = new (nothrow) size_t[size];
    if (arr != nullptr)
    {
        FillArrayPowOfTwo(arr, size);
        PrintArr(arr, size);
        delete[] arr;
    }
    cout << endl;
}

void DisposeTask2Matrix(int64_t** const arr, const size_t sizeY)
{
    for (size_t i = 0; i < sizeY; i++)
        delete[] arr[i];
    delete[] arr;
}

int64_t** CreateTask2Matrix(const size_t sizeX, const size_t sizeY, const int64_t min, const int64_t max, const int64_t seed)
{
    int64_t** arr = new (nothrow) int64_t * [sizeY];
    
    if (arr != nullptr)
    {
        for (size_t i = 0; i < sizeY; i++)
        {
            arr[i] = new (nothrow) int64_t[sizeX];
            if (arr[i] != nullptr)
            {
                for (size_t j = 0; j < sizeX; j++)
                    arr[i][j] = GetRandomNumber(min, max, seed);
            }
            else
            {
                DisposeTask2Matrix(arr, i - 1);
                return nullptr;
            }
            
        };
    }
    
    return arr;
}

void Task2()
{
    cout << "Task2:" << endl;
    const size_t SIZE = 4;
    const constexpr auto max = numeric_limits<int64_t>::max();
    const constexpr auto min = numeric_limits<int64_t>::min();
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    
    int64_t **arr = CreateTask2Matrix(SIZE, SIZE, min, max, seed);
    if (arr != nullptr)
    {
        PrintArr(arr, SIZE, SIZE);
        DisposeTask2Matrix(arr, SIZE);
    }
    else
    {
        cout << "Error allocation memory!";
    }
    
    cout << endl;
}

//создаем файл с записью через write, данных непонятно зачем так генерируемых
void CreateTxtFile(const string& filename, const char start, const char end)
{
    const int FILE_SYMBOL_SIZE = 200;
    const char ENTER = '\n';
    auto st = static_cast<int32_t>(start);
    auto en = static_cast<int32_t>(end);
    const int32_t LENGTH = en - st + 1;
    const size_t parts = static_cast<size_t>(FILE_SYMBOL_SIZE) / LENGTH;
    char* chars = new (nothrow) char[LENGTH];
    if (chars != nullptr)
    {
        for (int32_t i = 0; i < LENGTH; i++)
            chars[i] = start + i;

        ofstream file(filename);
        if (file.is_open())
        {
            for (size_t i = 0; i < parts; i++)
            {
                file.write(chars, LENGTH);
                file.put(ENTER);
            }
        }
        else
        {
            cout << "Something doing: file is not opened for write";
        }
        delete[] chars;
        file.close();
    }
    else
    {
        cout << "Error allocation memory!";
    }
    
}

// создаем файл с записью через <<, данных из строки.
void CreateTxtFile(const string& filename, const string& str)
{
    ofstream file(filename);
    if (file.is_open())
    {
        file << str;
        file.close();
    }
    else
    {
        cout << "Something doing: file is not opened for write";
    }
}

string InputFileName(const string& header, const string& extension)
{
    const string EMPTY = "";
    // вообще не только расширение txt конечно, но пусть будет так
    string fileName(EMPTY);
    bool condition(true);
    do
    {
        fileName = InputString(header);

        fs::path path(fileName);
        auto ext = path.extension().string();

        condition = fileName == EMPTY || ext != extension;
        if (condition)
            cout << "Input correct filename please.\n";

    } while (condition);

    return fileName;
}

void Task3()
{
    cout << "Task3:" << endl;
    const string FILE_EXTENSION = ".txt";

    const constexpr char CHAR_START = 'a';
    const constexpr char CHAR_END = 'z';
    string filename;
    filename = InputFileName("file name 1", FILE_EXTENSION);
    CreateTxtFile(filename, CHAR_START, CHAR_END);

    const string LONG_LONG_TXT = "The class template basic_ofstream implements high-level output operations on file based streams. It interfaces a file-based streambuffer (std::basic_filebuf) with the high-level interface of (std::basic_ostream).\nA typical implementation of std::basic_ofstream holds only one non - derived data member : an instance of";
    filename = InputFileName("file name 2", FILE_EXTENSION);
    CreateTxtFile(filename, LONG_LONG_TXT);
    cout << endl;
}

// файлики текстовые, для примера делаем построчное чтение входных файлов, результат будем отправлять как форматированный текст в out
void MergeTxtFiles(const size_t count, const string* const filePath, string& result)
{
    ofstream fout(result);
    if (fout.is_open())
    {
        for (size_t i = 0; i < count; ++i)
        {
            ifstream fin(filePath[i]);
            if (fin.is_open())
            {
                string instr;
                while (!fin.eof())
                {
                    getline(fin, instr);
                    fout << instr;
                    if (!fin.eof())
                        fout << endl;
                }
                fin.close();
            }
            else
            {
                fout.close();
                cout << "Something doing: file " << filePath[i] << " is not opened for read. MergeFiles abort.";
            }
        }
        fout.close();
    }
    else
    {
        cout << "Something doing: file " << result << " is not opened for write";
    }
}


void Task4()
{
    cout << "Task4:" << endl;
    const size_t FILE_COUNT = 2;
    const string FILE_EXTENSION = ".txt";
    string filePath[FILE_COUNT];
    for (size_t i = 1; i <= FILE_COUNT; i++)
        filePath[i-1] = InputFileName("File name " + to_string(i), FILE_EXTENSION);

    auto result = InputFileName("Merged File name", FILE_EXTENSION);
    
    // работа с потоками вообще должна в try catch оборачиваться чтобы закрывать потоки при ошибках?
    // или не обязательно, и без указателя на поток close() выполнится самостоятельно при уничтожении объекта?
    MergeTxtFiles(FILE_COUNT, filePath, result);
    cout << endl;
}

bool FindPhrase(const string& filename, const string& phrase)
{
    ifstream finBin(filename, ios::binary);
    if (finBin.is_open())
    {
        string str;
        getline(finBin, str, '\0');
        finBin.close();
        return str.find(phrase) != string::npos;
    }
    else
    {
        cout << "Something doing: file " << filename << " is not opened for read";
    }
    return false;

    /*
    bool isFinded(false);
    ifstream fin(filename);
    if (fin.is_open())
    {
        string str;
        while (!fin.eof())
        {
            getline(fin, str);
            auto pos = str.find(phrase);
            isFinded = pos != string::npos;
            if (isFinded)
                break;
        }
        fin.close();
    }
    else
    {
        cout << "Something doing: file " << filename << " is not opened for read";
    }
    return isFinded;
    */
}

void Task5()
{
    cout << "Task 5" << endl;
    const string FILE_EXTENSION = ".txt";
    string phrase = InputNotEmptyString("Phrase for search");
    string filename = InputFileName("File name for search", FILE_EXTENSION);
    bool isFound = FindPhrase(filename, phrase);
    cout << "Phrase \"" << phrase << "\" is" << (isFound ? "" : " not") << " found in file \"" << filename << "\"" << endl;
    cout << endl;
}

int main()
{
    Task1();

    Task2();

    Task3();

    Task4();

    Task5();
}