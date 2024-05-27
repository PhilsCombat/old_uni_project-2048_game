/* Copyright 2020, Philipp Abrecht */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <array>
#include "./Logic.h"
#include "./Seed.h"

using std::vector;
using std::array;
using std::cout;
using std::endl;
using vecArray = vector<array<int, 4>>;

// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _


Logic::Logic() {
    _undo = 1;
    _turn = 0;
    _score = 0;
    _status = 0;
}

// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _


Logic::~Logic() {}


// ___________________________________________________________________________


int Logic::getStatus() const { return _status; }

// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

void Logic::setAllowedUndo(unsigned const int& allowed) { _undo = allowed; }

// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

void Logic::setGameSize(int size) {
    if (size < 3) { size = 3; }
    if (size > 8) { size = 8; }

    _grid.setSize(size);
    _seed.clear();

    _turn = 0;
    _score = 0;
    _status = -2;
}


// ___________________________________________________________________________

void Logic::resetGame() {
    _grid.clear();
    _seed.clear();
    placeRandomTile();
    placeRandomTile();

    _turn = 0;
    _score = 0;
    _status = -2;
}

// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _


void Logic::undo() {
    if (_seed.size() == 0) { return; }
    _seed.pop_back(&_grid, &_score);
    _turn--;
    if (_status == 1) {
        _status = 0;
        checkWinOrLoss();
        if (_status == 0) { _status = -2; }
    } else {
        if (_status == -1) { _status = -2; }
    }
}


// ___________________________________________________________________________


void Logic::placeRandomTile() {
    // get all indexes of free tiles
    vector<int> freeTiles;
    for (int i = 0; i < _grid.size(); i++) {
        if (_grid[i] == 0) { freeTiles.push_back(i); }
    }

    // pick random index of freeTiles
    std::srand(std::time(0));
    int a = std::rand() % 100;
    int number;
    if (a < 10) { number = 4; } else { number = 2; }
    a = std::rand() % freeTiles.size();
    _grid[freeTiles.at(a)] = number;
}

// ___________________________________________________________________________

void Logic::checkWinOrLoss() {
    // already Won or Lost?
    if (_status != 0) { return; }

    int gridSize = _grid.size();

    // check if won
    for (int i = 0; i < gridSize; i++) {
        if (_grid[i] >= 2048) {
            _status = 1;
            return;
        }
    }

    int fails = 0;
    int backupScore = _score;
    int backupTurn = _turn;
    int* backupGrid = new int[gridSize];

    // make backup
    for (int i = 0; i < gridSize; i++) {
        backupGrid[i] = _grid[i];
    }

    // left
    if (!left()) { fails++; }
    for (int i = 0; i < gridSize; i++) {
        _grid[i] = backupGrid[i];
    }

    // right
    if (!right()) { fails++; }
    for (int i = 0; i < gridSize; i++) {
        _grid[i] = backupGrid[i];
    }

    // up
    if (!up()) { fails++; }
    for (int i = 0; i < gridSize; i++) {
        _grid[i] = backupGrid[i];
    }

    // down
    if (!down()) { fails++; }
    for (int i = 0; i < gridSize; i++) {
        _grid[i] = backupGrid[i];
    }

    _turn = backupTurn;
    _score = backupScore;

    delete[] backupGrid;
    backupGrid = nullptr;
    // check if lost
    if (fails == 4) {
        _status = -1;
        return;
    }
}




// ___________________________________________________________________________


bool Logic::makeStep(const int& direction) {
    bool validMove = false;
    int backupScore = _score;
    Grid backup;
    backup = _grid;
    switch (direction) {
        case 1: validMove = up(); break;
        case 2: validMove = right(); break;
        case 3: validMove = down(); break;
        case 4: validMove = left(); break;
    }
    if (validMove) {
        placeRandomTile();
        checkWinOrLoss();
        if (_seed.size() < _undo) {
            _seed.push_back(backup, backupScore);
        } else {
            _seed.leftShift();
            _seed.push_back(backup, backupScore);
        }
    }
    return validMove;
}


// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

bool Logic::left() {
    // Left-directed calculation of playingfield
    int edgeSize = _grid.edgeSize();
    int gridSize = _grid.size();
    bool changed = false;

    for (int row = 0; row < gridSize; row += edgeSize) {
        bool add = false;
        int last = row;
        int zero = -1;
        if (_grid[row] == 0) { zero = row; } else { add = true; }

        for (int col = row; col < row + edgeSize; col++) {
            if (_grid[col] != 0) {
                if (add && _grid[last] == _grid[col] && last < col) {
                    // grid changed
                    changed = true;
                    // grid calculation
                    _grid[last] += _grid[col];
                    _score += _grid[last];
                    _grid[col] = 0;
                    add = false;
                } else {
                    if (0 <= zero && zero < col) {
                        // grid changed
                        changed = true;
                        // grid calculation
                        _grid[zero] = _grid[col];
                        _grid[col] = 0;
                        last = zero;
                        add = true;
                        zero++;
                    } else {
                        last = col;
                    }
                }
            }
            if (zero < 0 && _grid[col] == 0) { zero = col; }
        }  // end inner for
    }  // end outer for
    if (changed) { _turn++; }
    return changed;
}

// ___________________________________________________________________________

bool Logic::right() {
    // Right-directed calculation of playingfield
    int edgeSize = _grid.edgeSize();
    int gridSize = _grid.size();
    bool changed = false;

    for (int row = gridSize - 1; row > -1; row -= edgeSize) {
        bool add = false;
        int last = row;
        int zero = -1;
        if (_grid[row] == 0) { zero = row; } else { add = true; }

        for (int col = row; col > row - edgeSize; col--) {
            if (_grid[col] != 0) {
                if (add && _grid[last] == _grid[col] && last > col) {
                    // grid changed
                    changed = true;
                    // grid calculation
                    _grid[last] += _grid[col];
                    _score += _grid[last];
                    _grid[col] = 0;
                    add = false;
                } else {
                    if (0 <= zero && zero > col) {
                        // grid changed
                        changed = true;
                        // grid calculation
                        _grid[zero] = _grid[col];
                        _grid[col] = 0;
                        last = zero;
                        add = true;
                        zero--;
                    } else {
                        last = col;
                    }
                }
            }
            if (zero < 0 && _grid[col] == 0) { zero = col; }
        }  // end inner for
    }  // end outer for
    if (changed) { _turn++; }
    return changed;
}

// ___________________________________________________________________________

bool Logic::up() {
    // Up-directed calculation of playingfield
    int edgeSize = _grid.edgeSize();
    int gridSize = _grid.size();
    bool changed = false;

    for (int col = 0; col < edgeSize; col++) {
        bool add = false;
        int last = col;
        int zero = -1;
        if (_grid[col] == 0) { zero = col; } else { add = true; }

        for (int row = col; row < gridSize; row += edgeSize) {
            if (_grid[row] != 0) {
                if (add && _grid[last] == _grid[row] && last < row) {
                    // grid changed
                    changed = true;
                    // grid calculation
                    _grid[last] += _grid[row];
                    _score += _grid[last];
                    _grid[row] = 0;
                    add = false;
                } else {
                    if (0 <= zero && zero < row) {
                        // grid changed
                        changed = true;
                        // grid calculation
                        _grid[zero] = _grid[row];
                        _grid[row] = 0;
                        last = zero;
                        add = true;
                        zero += edgeSize;
                    } else {
                        last = row;
                    }
                }
            }
            if (zero < 0 && _grid[row] == 0) { zero = row; }
        }  // end inner for
    }  // end outer for
    if (changed) { _turn++; }
    return changed;
}

// ___________________________________________________________________________

bool Logic::down() {
    // Up-directed calculation of playingfield
    int edgeSize = _grid.edgeSize();
    int gridSize = _grid.size();
    bool changed = false;

    for (int col = gridSize - 1; col >= gridSize - edgeSize; col--) {
        bool add = false;
        int last = col;
        int zero = -1;
        if (_grid[col] == 0) { zero = col; } else { add = true; }

        for (int row = col; row > -1; row -= edgeSize) {
            if (_grid[row] != 0) {
                if (add && _grid[last] == _grid[row] && last > row) {
                    // grid changed
                    changed = true;
                    // grid calculation
                    _grid[last] += _grid[row];
                    _score += _grid[last];
                    _grid[row] = 0;
                    add = false;
                } else {
                    if (0 <= zero && zero > row) {
                        // grid changed
                        changed = true;
                        // grid calculation
                        _grid[zero] = _grid[row];
                        _grid[row] = 0;
                        last = zero;
                        add = true;
                        zero -= edgeSize;
                    } else { last = row; }
                }
            }
            if (zero < 0 && _grid[row] == 0) { zero = row; }
        }  // end inner for
    }  // end outer for
    if (changed) { _turn++; }
    return changed;
}
