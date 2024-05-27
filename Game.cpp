/* Copyright 2020, Philipp Albrecht */

#include <ncurses.h>
#include <stdio.h>
#include <getopt.h>
#include <iostream>
#include "./Game.h"

using std::cerr;
using std::endl;

Game::Game() { _running = false; }
Game::~Game() {}



// ===========================================================================


void Game::play() {
    _running = true;
    _graphic.initTerminal(&_logic);

    while (_running) {
        const int c = getch();
        processKeyInput(c);
        _graphic.drawStatistics(&_logic);
        _graphic.drawWinLoseScreen(&_logic);
    }
    endwin();
}


// ===========================================================================


void Game::processKeyInput(const int key) {
    if (key == KEY_UP) {
        if (_logic.makeStep(1)) {
            _graphic.drawBoxes(&_logic);
        }
        return;
    }
     if (key == KEY_RIGHT) {
        if (_logic.makeStep(2)) {
            _graphic.drawBoxes(&_logic);
        }
        return;
    }
    if (key == KEY_DOWN) {
        if (_logic.makeStep(3)) {
            _graphic.drawBoxes(&_logic);
        }
        return;
    }
    if (key == KEY_LEFT) {
        if (_logic.makeStep(4)) {
            _graphic.drawBoxes(&_logic);
        }
        return;
    }
    switch (key) {
        case 27: _running = false; return;
        case 'c': _graphic.rotateColor();
                  _graphic.drawBoxes(&_logic);
                  return;
        case 'n': _logic.resetGame();
                  _graphic.drawBoxes(&_logic);
                  return;
        case 'u': _logic.undo(); _graphic.drawBoxes(&_logic); return;
        case '3': _graphic.resize(&_logic, 3); return;
        case '4': _graphic.resize(&_logic, 4); return;
        case '5': _graphic.resize(&_logic, 5); return;
        case '6': _graphic.resize(&_logic, 6); return;
        case '7': _graphic.resize(&_logic, 7); return;
        case '8': _graphic.resize(&_logic, 8); return;
    }
}


// ===========================================================================

void Game::printUsageAndExit() {
    cerr << "Usage ./Game:" << endl
         << "--size <int>: short: -s  set size of playingfield" << endl
         << "--undo <int>: short: -u  set possible number of undo's"
         << endl;
    exit(1);
}


void Game::parseArguments(const int& argc, char** argv) {
    struct option options[] = {
        {"size", 1, NULL, 's'},
        {"undo", 1, NULL, 'u'},
        {NULL, 0, NULL, 0}
    };
    optind = 1;
    bool customSize = false;
    while (true) {
        char c = getopt_long(argc, argv, "s:u:", options, NULL);
        if (c == -1) { break; }

        switch (c) {
            case 's':
                _logic.setGameSize(atoi(optarg));
                customSize = true;
                break;
            case 'u': _logic.setAllowedUndo(atoi(optarg)); break;
            case '?': printUsageAndExit(); break;
        }
        if (optind > argc) { printUsageAndExit(); }
        if (!customSize) { _logic.setGameSize(4); }
    }
}
