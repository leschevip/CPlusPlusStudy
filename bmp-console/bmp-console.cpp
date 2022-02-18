// bmp-console.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <windows.h>
#include <vector>
#include "Rect.h"

typedef unsigned char BYTE;
typedef unsigned short ushort;

using namespace std;

const ushort BMPTYPE = 0x4D42;

struct Bmp24bitData
{
    ifstream* fin;
    size_t pos;
    size_t len;
    BITMAPINFOHEADER fileInfo;
    BITMAPFILEHEADER file;
    RGBTRIPLE** colors;

    ~Bmp24bitData()
    {
        fin->close();
        fin = nullptr;
    }
};

struct Position
{
    size_t pos;
    size_t len;
};

struct SymbolBox
{
    size_t x;
    size_t xCount;
    size_t y;
    size_t yCount;
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
            dataPtr->fin->read((char*)&dataPtr->fileInfo, sizeof(BITMAPINFOHEADER));
            dataPtr->pos = static_cast<size_t>(dataPtr->fin->tellg()) + 1024 * sizeof(BYTE);
            dataPtr->len = dataPtr->fileInfo.biSize - dataPtr->pos;

            dataPtr->colors = new RGBTRIPLE * [dataPtr->fileInfo.biHeight];
            for (size_t y = 0; y < dataPtr->fileInfo.biHeight; y++)
            {
                dataPtr->colors[y] = new RGBTRIPLE[dataPtr->fileInfo.biWidth];
                dataPtr->fin->read((char*)dataPtr->colors[y], dataPtr->fileInfo.biWidth * sizeof(RGBTRIPLE));
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
    auto count = static_cast<size_t>(floor(static_cast<double>(pixels) / symbolCount));
    if (count > 0)
    {
        for (size_t i = 0; i < symbolCount; i++)
            pos[i] = { i * count, count };

        leaf = pixels - count * symbolCount;
    }
    else
    {
        auto idx = static_cast<size_t>(floor(static_cast<double>(symbolCount) / pixels));
        for (size_t i = idx - 1; i < symbolCount; i += idx)
        {
            pos[i].len++;
            for (size_t k = i + 1; k < symbolCount; k++)
                pos[k].pos++;
        }

        leaf = symbolCount - idx * pixels;
    }
    
    if (leaf != 0)
    {
        GetSymbolPositions(leaf, symbolCount, pos);
    }
}

void OutputBmp(const string& filePath, const Rect& output)
{
    auto data = GetBmp24bitInfo(filePath);

    Position* xPositions = new Position[output.Xmax - output.Xmin + 1];
    Position* yPositions = new Position[output.Ymax - output.Ymin + 1];
    GetSymbolPositions(data->fileInfo.biWidth, output.Xmax - output.Xmin + 1, xPositions);
    GetSymbolPositions(data->fileInfo.biWidth, output.Ymax - output.Ymin + 1, yPositions);

    char** chars = new char*[output.Ymax - output.Ymin + 1];
    for (size_t y = output.Ymin; y <= output.Ymax; y++)
    {
        auto yPos = yPositions[y];
        chars[y] = new char[output.Xmax - output.Xmin + 1];
        for (size_t x = output.Xmin; x <= output.Xmax; x++)
        {
            auto xPos = xPositions[x];
            char ch(' ');
            for (size_t h = yPos.pos; h < yPos.pos + yPos.len; h++)
            {
                for (size_t w = xPos.pos; w < xPos.pos + xPos.len; w++)
                {
                    auto color = data->colors[h][w];
                    if (color.rgbtBlue == 0 && color.rgbtGreen == 0 && color.rgbtRed == 0)
                    {
                        ch = '@';
                        goto print;
                    }
                }
            }
            print:
            cout << ch;
            //chars[y][x] = ch;
        }
        cout << endl;
    }

    delete data;
}

Rect GetOutputWindow(const size_t x, const size_t y, const size_t w, const size_t h)
{
    HWND hwnd = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(hwnd, 1);
    MoveWindow(hwnd, x, y, w, h, TRUE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    !GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return { info.srWindow.Left, info.srWindow.Top, info.srWindow.Right, info.srWindow.Bottom };
}

int main()
{
    auto output = GetOutputWindow(0, 0, 1024, 768);
    OutputBmp("1.bmp", output);
}