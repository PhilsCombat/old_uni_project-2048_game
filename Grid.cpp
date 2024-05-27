/* Copyright 2020, Philipp Albrecht */

#include "./Grid.h"

// ===========================================================================


Grid::Grid() {
    _edgeSize = 4;
    _gridSize = 16;

    _grid = new int[16];
    for (int i = 0; i < 16; i++) { _grid[i] = 0; }
}


void Grid::operator=(const Grid& grid) {
    setSize(grid._edgeSize);

    for (int i = 0; i < _gridSize; i++) {
        _grid[i] = grid._grid[i];
    }
}


// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _


Grid::~Grid() {
    delete[] _grid;
    _grid = nullptr;
}


// ___________________________________________________________________________


int Grid::size() const {
    return _gridSize;
}

// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

int Grid::edgeSize() const {
    return _edgeSize;
}

// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _


int& Grid::operator[](const int& index) const {
    return _grid[index];
}


// ___________________________________________________________________________


void Grid::clear() {
    for (int i = 0; i < _gridSize; i++) { _grid[i] = 0; }
}


// ___________________________________________________________________________


void Grid::setSize(int size) {
    if (size < 3) { size = 3; }
    if (size > 8) { size = 8; }

    _edgeSize = size;
    _gridSize = size * size;

    delete[] _grid;
    _grid = new int[_gridSize];

    clear();
}
