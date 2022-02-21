// bmp-console.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <windows.h>
#include <vector>
#include "Rect.h"

#pragma warning(disable: 26451 6386 6385)

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
    size_t pos;
    size_t len;
    vector<size_t> idx;
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
            const size_t PALLETE_SIZE = 1024;
            const size_t BIT24 = 24;
            dataPtr->fin->read((char*)&dataPtr->fileInfo, sizeof(BITMAPINFOHEADER));

            if (dataPtr->fileInfo.biBitCount != BIT24)
                throw new exception("not supported");

            dataPtr->pos = static_cast<size_t>(dataPtr->fin->tellg()) + PALLETE_SIZE * sizeof(BYTE);
            dataPtr->len = dataPtr->fileInfo.biSizeImage;
            dataPtr->fin->seekg(dataPtr->pos, ios::beg);
            dataPtr->colors = new RGBTRIPLE * [dataPtr->fileInfo.biHeight];

            const size_t shiftBytes = dataPtr->fileInfo.biWidth % 4;
            size_t k(0);
            for (int32_t y = dataPtr->fileInfo.biHeight - 1; y >= 0 ; y--)
            {
                dataPtr->colors[k] = new RGBTRIPLE[dataPtr->fileInfo.biWidth];
                dataPtr->fin->read((char*)dataPtr->colors[k], dataPtr->fileInfo.biWidth * sizeof(RGBTRIPLE));
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




void GetSymbolPositions(/*const size_t maxPixelsCount, */const size_t pixels, const size_t symbolCount, Position* pos)
{
    size_t leaf;
    size_t count(0);
    if (pixels >= symbolCount)
    {
        count = static_cast<size_t>(floor(static_cast<double>(pixels) / symbolCount));
        //size_t k(0);
        for (size_t i = 0; i < symbolCount; i++)
        {
            pos[i] = { i * count, count };
            /*for (size_t p = 0; p < count; p++)
                pos[i].idx.push_back(k);*/
        }
            

        leaf = pixels - count * symbolCount;
    }
    else
    {
        auto idx = static_cast<size_t>(ceil(static_cast<double>(symbolCount) / pixels));
        for (size_t i = idx - 1; i < symbolCount; i += idx)
        {
            pos[i].len++;
            for (size_t k = i + 1; k < symbolCount; k++)
                pos[k].pos++;
        }

        leaf = pixels - symbolCount / idx;
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
    GetSymbolPositions(data->fileInfo.biHeight, output.Ymax - output.Ymin + 1, yPositions);

    char** chars = new char*[output.Ymax - output.Ymin + 1];
    for (size_t y = output.Ymin; y <= output.Ymax; y++)
    {
        auto yPos = yPositions[y];
        chars[y] = new char[output.Xmax - output.Xmin + 1];
        for (size_t x = output.Xmin; x <= output.Xmax; x++)
        {
            auto xPos = xPositions[x];
            char ch(' ');
            for (size_t h = yPos.pos; h < (yPos.pos + yPos.len); h++)
            {
                for (size_t w = xPos.pos; w < (xPos.pos + xPos.len); w++)
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
        }
        cout << endl;
    }

    delete data;
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
    auto output = GetOutputWindow(0, 0, 1024, 768);
    OutputBmp("1.bmp", output);
    return 0;
}