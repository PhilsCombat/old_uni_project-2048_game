/* Copyright 2020, Philipp Albrecht */

#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <ncurses.h>
#include <array>
#include <unordered_map>
#include "./Grid.h"

class Logic;
class Game;

class Graphic{
 public:
    Graphic();
    ~Graphic();

 private:
    static const int _gridAnchorX = 23;
    static const int _gridAnchorY = 10;
    int _edgeSize;
    int _currentPallet;
    std::array<std::unordered_map<int, int>, 3> _colors;

    void rotateColor();
    void drawFrame();
    void drawControlls();
    void resize(Logic* logic, int size);
    void initTerminal(Logic* logic);
    void drawStatistics(Logic* logic);
    void drawBoxes(const Logic* logic);
    void drawWinLoseScreen(Logic* logic);

    friend Game;
};


#endif  // GRAPHIC_H_
