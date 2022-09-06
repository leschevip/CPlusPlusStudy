#pragma once

// количество очков в игре к которому нужно стремиться
extern const int MAX_SCORE = 21;

// минимальное количество очков в игре которое может прийти с картой
extern const int MIN_SCORE_VALUE = 1;

// пограничное значение очков, больше которого диллер не берет карты с колоды
extern const int MAX_HOUSE_SCORE = 16;

extern const int ACE_SCORE = 11;
extern const int KING_SCORE = 4;
extern const int LADY_SCORE = 3;
extern const int JACK_SCORE = 2;


enum ColorCode {
    FG_RED = 31,
    FG_GREEN = 32,
    FG_BLUE = 34,
    FG_YELLOW = 33,
    FG_DEFAULT = 39
};