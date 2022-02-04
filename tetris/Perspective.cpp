#include "Perspective.h"
#include "CRectangle.h"

const int HEIGHT_SCORE_PANEL = 3;
const int WIDTH_PREWIEW_PANEL = 30;

Perspective::Perspective(CRectangle rect)
    : _rect(rect), _left(0), _top(0), _right(1.0f), _bottom(1.0f), _charW(0), _charH(0), _maxCharWCount(0), _maxCharHCount(0)
{
    _charW = 1 / (float)(_rect.Width());
    _charH = 1 / (float)(_rect.Height());

    Score = CreateOutputArea( AreaType::SCORE, 0.0f, 0.0f, 1.0f, HEIGHT_SCORE_PANEL * _charH);
    Preview = CreateOutputArea(AreaType::PREVIEW, 1.0f - WIDTH_PREWIEW_PANEL * _charW, HEIGHT_SCORE_PANEL * _charH, 1.0f, 1.0f);
    Game = CreateOutputArea(AreaType::GAME, 0.0f, HEIGHT_SCORE_PANEL * _charH, 1.0f - WIDTH_PREWIEW_PANEL * _charW, 1.0f);
    Full = CreateOutputArea(AreaType::SCREEN, 0.0f, 0.0f, 1.0f, 1.0f);
}

Perspective::~Perspective()
{
    delete Score;
    Score = nullptr;
    delete Preview;
    Preview = nullptr;
    delete Game;
    Game = nullptr;
    delete Full;
    Full = nullptr;
}

float Perspective::CharW()
{
    return _charW;
}

float Perspective::CharH()
{
    return _charH;
}

int Perspective::MaxCharWidthCount()
{
    return _rect.Width();
}

int Perspective::MaxCharHeightCount()
{
    return _rect.Height();
}

OutputArea* Perspective::CreateOutputArea(AreaType type, float left, float top, float right, float bottom)
{
    int l = left != 0 ? left / _charW - 1 : 0;
    int t = top != 0 ? top / _charH - 1 : 0;
    int r = right / _charW - 1;
    int b = bottom / _charH - 1;
    CRectangle rect(l, t, r, b);
    OutputArea* area = new OutputArea(type, rect);
    return area;
}