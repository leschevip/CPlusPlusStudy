#include "Perspective.h"
#include "CRectangle.h"

extern const uint32_t HEIGHT_SCORE_PANEL;
extern const uint32_t WIDTH_PREWIEW_PANEL;
extern const float H_FLOAT_MIN;
extern const float H_FLOAT_MAX;
extern const float V_FLOAT_MIN;
extern const float V_FLOAT_MAX;

Perspective::Perspective(const CRectangle& rect)
    : _rect(rect), _charW(0), _charH(0), _maxCharWCount(0), _maxCharHCount(0)
{
    _charW = 1 / (float)(_rect.Width());
    _charH = 1 / (float)(_rect.Height());

    Score = CreateOutputArea( AreaType::SCORE, H_FLOAT_MIN, V_FLOAT_MIN, H_FLOAT_MAX, HEIGHT_SCORE_PANEL * _charH);
    Preview = CreateOutputArea(AreaType::PREVIEW, H_FLOAT_MAX - WIDTH_PREWIEW_PANEL * _charW, HEIGHT_SCORE_PANEL * _charH, H_FLOAT_MAX, V_FLOAT_MAX);
    Game = CreateOutputArea(AreaType::GAME, H_FLOAT_MIN, HEIGHT_SCORE_PANEL * _charH, H_FLOAT_MAX - WIDTH_PREWIEW_PANEL * _charW, V_FLOAT_MAX);
    Full = CreateOutputArea(AreaType::SCREEN, H_FLOAT_MIN, V_FLOAT_MIN, H_FLOAT_MAX, V_FLOAT_MAX);
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

uint32_t Perspective::MaxCharWidthCount()
{
    return _rect.Width();
}

uint32_t Perspective::MaxCharHeightCount()
{
    return _rect.Height();
}

OutputArea* Perspective::CreateOutputArea(const AreaType& type, const float& left, const float& top, const float& right, const float& bottom)
{
    int l = left != 0 ? left / _charW - 1 : 0;
    int t = top != 0 ? top / _charH - 1 : 0;
    int r = right / _charW - 1;
    int b = bottom / _charH - 1;
    CRectangle rect(l, t, r, b);
    OutputArea* area = new OutputArea(type, rect);
    return area;
}

OutputArea* Perspective::Output(const AreaType& type)
{
    switch (type)
    {
    case AreaType::EMPTY:
        return nullptr;
    case AreaType::SCORE:
        return Score;
    case AreaType::GAME:
        return Game;
    case AreaType::PREVIEW:
        return Preview;
    case AreaType::SCREEN:
        return Full;
    default:
        break;
    }
    return nullptr;
}