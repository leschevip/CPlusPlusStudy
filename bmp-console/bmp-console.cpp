// bmp-console.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define NOMINMAX

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <windows.h>
#include <vector>

#pragma warning(disable: 26451 6386 6385)

typedef unsigned char BYTE;
typedef unsigned short ushort;

using namespace std;

const ushort BMPTYPE = 0x4D42;

struct Rect
{
    int32_t Xmin;
    int32_t Ymin;
    int32_t Xmax;
    int32_t Ymax;
};

struct Bmp24bitData
{
    ifstream* fin;
    BITMAPINFOHEADER fileInfo;
    BITMAPFILEHEADER file;
    RGBTRIPLE** colors;

    ~Bmp24bitData()
    {
        fin->close();
        fin = nullptr;
        if (colors != nullptr)
        {
            for (size_t i = 0; i < fileInfo.biHeight; i++)
                delete colors[i];
            delete colors;
        }
        colors = nullptr;
    }
};

struct Position
{
    vector<size_t> idx;

    ~Position()
    {
        idx.clear();
    }
};

Bmp24bitData* GetBmp24bitInfo(const string& filePath)
{
    
    Bmp24bitData* dataPtr = new Bmp24bitData();
    dataPtr->fin = new ifstream(filePath);
    bool isSeccess(dataPtr->fin->is_open());
    if (isSeccess)
    {
        dataPtr->fin->read((char*)&dataPtr->file, sizeof(BITMAPFILEHEADER));
        if (dataPtr->file.bfType == BMPTYPE)
        {
            const size_t BIT24 = 24;
            dataPtr->fin->read((char*)&dataPtr->fileInfo, sizeof(BITMAPINFOHEADER));

            if (dataPtr->fileInfo.biBitCount != BIT24)
                throw new exception("not supported");

            dataPtr->fin->seekg(dataPtr->file.bfOffBits, ios::beg);
            dataPtr->colors = new RGBTRIPLE * [dataPtr->fileInfo.biHeight];

            const size_t shiftBytes = dataPtr->fileInfo.biWidth % 4;
            size_t k(0);
            for (int32_t y = dataPtr->fileInfo.biHeight - 1; y >= 0 ; y--)
            {
                dataPtr->colors[k] = new RGBTRIPLE[dataPtr->fileInfo.biWidth];
                dataPtr->fin->read((char*)dataPtr->colors[k], dataPtr->fileInfo.biWidth * sizeof(RGBTRIPLE));
                if (shiftBytes != 0)
                    dataPtr->fin->seekg(shiftBytes, ios::cur);
                k++;
            }
            
        }
        else
        {
            isSeccess = false;
        }
    }
    if (isSeccess)
    {
        return dataPtr;
    }
    else
    {
        delete dataPtr;
        return nullptr;
    }
}

void GetSymbolPositions(const size_t pixels, const size_t symbolCount, Position* pos)
{
    size_t leaf;
    size_t count(0);
    if (pixels >= symbolCount)
    {
        count = static_cast<size_t>(floor(static_cast<double>(pixels) / symbolCount));
        size_t k(0);
        for (size_t i = 0; i < symbolCount; i++)
        {
            for (size_t p = 0; p < count; p++)
            {
                pos[i].idx.push_back(k);
                k++;
            }
        }
            
        leaf = pixels - count * symbolCount;
    }
    else
    {
        auto count = static_cast<size_t>(ceil(static_cast<double>(symbolCount) / pixels));
        for (size_t i = count - 1; i < symbolCount; i += count)
        {
            size_t k = pos[i].idx.at(pos[i].idx.size() - 1) + 1;
            pos[i].idx.push_back(k);

            for (size_t t = i + 1; t < symbolCount; t++)
            {
                for (size_t g = 0; g < pos[t].idx.size(); g++)
                {
                    pos[t].idx[g]++;
                }
            }
        }

        leaf = pixels - symbolCount / count;
    }
    
    if (leaf != 0)
    {
        GetSymbolPositions(leaf, symbolCount, pos);
    }
}

void OutputBmp(const string& filePath, Rect& output)
{
    auto data = GetBmp24bitInfo(filePath);

    if (data->fileInfo.biWidth <= output.Xmax - output.Xmin + 1)
        output.Xmax = data->fileInfo.biWidth - 1;
    if (data->fileInfo.biHeight <= output.Ymax - output.Ymin + 1)
        output.Ymax = data->fileInfo.biHeight - 1;

    Position* xPositions = new Position[output.Xmax - output.Xmin + 1];
    Position* yPositions = new Position[output.Ymax - output.Ymin + 1];
    GetSymbolPositions(data->fileInfo.biWidth, output.Xmax - output.Xmin + 1, xPositions);
    GetSymbolPositions(data->fileInfo.biHeight, output.Ymax - output.Ymin + 1, yPositions);

    const char space = ' ';
    const char pixel = '@';
    char** chars = new char*[output.Ymax - output.Ymin + 1];
    for (size_t y = output.Ymin; y <= output.Ymax; y++)
    {
        auto yPos = yPositions[y];
        chars[y] = new char[output.Xmax - output.Xmin + 1];
        for (size_t x = output.Xmin; x <= output.Xmax; x++)
        {
            auto xPos = xPositions[x];
            char ch(space);

            for (auto h : yPos.idx)
            {
                for (auto w : xPos.idx)
                {
                    auto color = data->colors[h][w];
                    if (color.rgbtBlue == 0 && color.rgbtGreen == 0 && color.rgbtRed == 0)
                    {
                        ch = pixel;
                        goto print;
                    }
                }
            }
            print:
            cout << ch;
        }
        cout << endl;
    }

    delete data;
    delete[] xPositions;
    delete[] yPositions;
}

Rect GetOutputWindow(const int x, const int y, const int w, const int h)
{
    HWND hwnd = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(hwnd, 1);
    MoveWindow(hwnd, x, y, w, h, TRUE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return { info.srWindow.Left, info.srWindow.Top, info.srWindow.Right, info.srWindow.Bottom };
}

int main()
{
    string fname;
    const string Y = "y";
    const string N = "n";
    while (true)
    {
        system("cls");
        cout << "Input file name: ";
        cin >> fname;

        auto output = GetOutputWindow(150, 100, 1024, 768);
        OutputBmp(fname, output);
        string retry = Y;
        while (true)
        {
            cout << "Do you want to try other file? ("<< Y << "/" << N << "):";
            cin >> retry;
            if (retry != Y && retry != N)
            {
                cout << "Try again to answer, please" << endl;
            }
            else
            {
                break;
            }    
        }
        if (retry == N)
            break;
    }
    
    return 0;
}