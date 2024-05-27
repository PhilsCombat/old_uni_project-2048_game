/* Copyright 2020, Philipp Albrecht */


#include <ncurses.h>
#include <math.h>
#include <vector>
#include <array>
#include "./Game.h"
#include "./Logic.h"
#include "./Graphic.h"


Graphic::Graphic() {
    _edgeSize = 4;
    _currentPallet = 0;
}

Graphic::~Graphic() {}

// ___________________________________________________________________________

void Graphic::initTerminal(Logic* logic) {
    // ncurses
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(false);
    keypad(stdscr, true);

    // orange-red
    init_color(31, 970, 610, 190);
    init_color(32, 940, 540, 80);
    init_color(33, 850, 430, 0);
    init_color(34, 850, 340, 0);
    init_color(35, 850, 270, 0);
    init_color(36, 850, 160, 0);
    init_color(37, 810, 0, 0);
    init_color(38, 620, 0, 0);
    init_color(39, 500, 0, 0);
    init_color(40, 370, 0, 0);
    init_color(41, 310, 0, 0);
    init_color(42, 250, 0, 0);
    init_color(43, 0, 0, 0);        // black
    init_color(44, 999, 999, 999);  // white
    // blue-purple
    init_color(51, 0, 620, 810);
    init_color(52, 0, 500, 690);
    init_color(53, 0, 310, 620);
    init_color(54, 60, 250, 620);
    init_color(55, 120, 180, 620);
    init_color(56, 250, 0, 620);
    init_color(57, 370, 0, 620);
    init_color(58, 500, 0, 620);
    init_color(59, 500, 0, 500);
    init_color(60, 370, 0, 370);
    init_color(61, 310, 0, 310);
    init_color(62, 250, 0, 250);
    // yellow-green
    init_color(71, 960, 830, 560);
    init_color(72, 940, 810, 370);
    init_color(73, 940, 810, 180);
    init_color(74, 810, 750, 60);
    init_color(75, 750, 690, 0);
    init_color(76, 620, 620, 0);
    init_color(77, 500, 620, 0);
    init_color(78, 370, 620, 0);
    init_color(79, 0, 620, 0);
    init_color(80, 0, 500, 0);
    init_color(81, 0, 370, 0);
    init_color(82, 0, 250, 0);


    init_pair(40, 13, 13);  // white

    for (int i = 1; i < 1 + 12; i++) { init_pair(i +  0, 44, i + 30); }
    for (int i = 1; i < 1 + 12; i++) { init_pair(i + 12, 44, i + 50); }
    for (int i = 1; i < 1 + 12; i++) { init_pair(i + 24, 44, i + 70); }

    for (int i = 1; i < 12; i++) { _colors[0][pow(2, i)] = i; }
    for (int i = 12; i < 18; i++) { _colors[0][pow(2, i)] = 12; }

    for (int i = 1; i < 12; i++) { _colors[1][pow(2, i)] = i + 12; }
    for (int i = 12; i < 18; i++) { _colors[1][pow(2, i)] = 24; }

    for (int i = 1; i < 12; i++) { _colors[2][pow(2, i)] = i + 24; }
    for (int i = 12; i < 18; i++) { _colors[2][pow(2, i)] = 36; }

    // terminal
    mvprintw(5, 32, "score:");
    mvprintw(6, 32, "turn:");

    logic -> resetGame();
    _edgeSize = logic -> _grid.edgeSize();

    drawFrame();
    drawControlls();
    drawStatistics(logic);
    drawBoxes(logic);
    refresh();
}

// ___________________________________________________________________________

void Graphic::rotateColor() {
    _currentPallet = (_currentPallet + 1) % _colors.size();
}


void Graphic::drawControlls() {
    mvprintw(9, 4, "Controls:");
    mvprintw(11, 4, "esc = exit");
    mvprintw(12, 5, "n  = restart");
    mvprintw(13, 5, "u  = undo");
    mvprintw(15, 4, "key up");
    mvprintw(16, 4, "key down");
    mvprintw(17, 4, "key left");
    mvprintw(18, 4, "key right");
    mvprintw(20, 4, "3-8: set Size");
    mvprintw(21, 4, "does restart!");
    mvprintw(23, 4, "c: change");
    mvprintw(24, 7, "color");
}


void Graphic::drawStatistics(Logic* logic) {
    mvprintw(5, 39, "        ");
    mvprintw(6, 39, "        ");
    mvprintw(5, 39, "%d", logic -> _score);
    mvprintw(6, 39, "%d", logic -> _turn);
    refresh();
}


void Graphic::resize(Logic* logic, int size) {
    if (size == _edgeSize) { return; }
    if (size < 3) { size = 3; }
    int startX;
    int startY;
    if (size < _edgeSize) {
        startX = _gridAnchorX - 2;
        startY = _gridAnchorY + 6 * size;
        for (int row = startY; row < startY + 6 * _edgeSize; row++) {
            for (int col = startX; col < startX + 12 * _edgeSize + 2; col++) {
                mvprintw(row, col, " ");
            }
        }
        startX = _gridAnchorX + 12 * size;
        startY = _gridAnchorY - 2;
        for (int row = startY; row < _gridAnchorY + 6 * size; row++) {
            for (int col = startX; col < _gridAnchorX + 12 * _edgeSize;
                col++) {
                mvprintw(row, col, " ");
            }
        }
    } else {
        startY = _gridAnchorY + 6 * _edgeSize - 1;
        for (int col = _gridAnchorX; col < _gridAnchorX + 12 * _edgeSize;
            col++) {
            mvprintw(startY, col, " ");
        }
        startX = _gridAnchorX + 12 * _edgeSize - 2;
        for (int row = _gridAnchorY; row < _gridAnchorY + 6 * _edgeSize;
            row++) {
            mvprintw(row, startX, " ");
            mvprintw(row, startX + 1, " ");
        }
    }
    _edgeSize = size;
    logic -> setGameSize(size);
    logic -> resetGame();
    drawFrame();
    drawStatistics(logic);
    drawWinLoseScreen(logic);
    drawBoxes(logic);
}


void Graphic::drawFrame() {
    attron(A_REVERSE);

    // <tile hight> * <tiles> + <tiles + 1>
    int lastRow = _gridAnchorY - 1 + 5 * _edgeSize + _edgeSize;

    // <tile width> * <tiles> + <tiles + 1> * <spacing>
    int lastCol = _gridAnchorX - 2 + 10 * _edgeSize + (_edgeSize + 1) * 2;

    // print row frame
    for (int col = _gridAnchorX - 2; col < lastCol; col++) {
        mvprintw(_gridAnchorY - 1, col, " ");
    }
     for (int col = _gridAnchorX - 2; col < lastCol; col++) {
        mvprintw(lastRow, col, " ");
    }

    // print column frame
    for (int row = _gridAnchorY - 1; row < lastRow; row++) {
        mvprintw(row, _gridAnchorX - 2, " ");
        mvprintw(row, _gridAnchorX - 1, " ");
    }
     for (int row = _gridAnchorY - 1; row < lastRow; row++) {
        mvprintw(row, lastCol - 2, " ");
        mvprintw(row, lastCol - 1, " ");
    }

    attroff(A_REVERSE);
}


void Graphic::drawWinLoseScreen(Logic* logic) {
    if (logic -> getStatus() == -1) {
        mvprintw(2, 2, "@@     @@@@   @@@@@ @@@@@@");
        mvprintw(3, 2, "@@    @@  @@ @@       @@  ");
        mvprintw(4, 2, "@@    @@  @@  @@@@    @@  ");
        mvprintw(5, 2, "@@    @@  @@     @@   @@  ");
        mvprintw(6, 2, "@@@@@  @@@@  @@@@@    @@  ");
    }
    if (logic -> getStatus() > 0) {
        mvprintw(2, 2, "@@     @@  @@@@  @@@@@  @@");
        mvprintw(3, 2, "@@     @@ @@  @@ @@ @@  @@");
        mvprintw(4, 2, " @@   @@  @@  @@ @@ @@@ @@");
        mvprintw(5, 2, " @@ @ @@  @@  @@ @@  @@ @@");
        mvprintw(6, 2, "  @@@@@    @@@@  @@  @@@@@");
    }
    if (logic -> getStatus() == -2) {
        logic -> _status = 0;
        for (int i = 2; i < 7; i++) {
            mvprintw(i, 2, "                          ");
        }
    }
    refresh();
}


void Graphic::drawBoxes(const Logic* logic) {
    const Grid& grid = logic -> _grid;
    for (int i = 0; i < grid.size(); i++) {
        int numberPos = 5;
        int skip = 0;
        if (10 <= grid[i] && grid[i] <= 999) {
            if (grid[i] < 100) { skip = 1; } else { skip = 2; }
            numberPos = 3;
        }
        if (1000 <= grid[i] && grid[i] <= 99999) {
            if (grid[i] < 10000) { skip = 3; } else { skip = 4; }
            numberPos = 3;
        }
        if (grid[i] >= 100000) {
            numberPos = 2;
            skip = 5;
        }
        // spacing included
        int startX = _gridAnchorX + 12 * (i % grid.edgeSize());
        int startY = _gridAnchorY + 6 * (i / grid.edgeSize());

        attron(COLOR_PAIR(_colors[_currentPallet][grid[i]]));

        for (int row = startY; row < startY + 5; row++) {
            for (int col = startX; col < startX + 10; col++) {
                if (row == startY + 2 && col == startX + numberPos
                    && grid[i] != 0) {
                    mvprintw(row, col, "%d", grid[i]);
                    col += skip;
                } else {
                    mvprintw(row, col, " ");
                }
            }  // endfor col
        }  // endfor row
        attroff(COLOR_PAIR(_colors[_currentPallet][grid[i]]));
    }  // endfor iterate grid
    refresh();
}
