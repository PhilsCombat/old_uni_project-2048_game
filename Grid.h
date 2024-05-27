/* Copyright 2020, Philipp Albrecht */

#ifndef GRID_H_
#define GRID_H_

#include <gtest/gtest.h>

class Grid {
 public:
    Grid();
    ~Grid();

    void setSize(int size);
    void clear();
    int size() const;
    int edgeSize() const;
    int& operator[](const int& index) const;
    void operator=(const Grid& grid);
 private:
    int _edgeSize;
    int _gridSize;

    int* _grid;

    FRIEND_TEST(GRID, setSize);
    FRIEND_TEST(GRID, subscript);
    FRIEND_TEST(GRID, copyEqual);
    FRIEND_TEST(GRID, clear);
};

#endif  // GRID_H_
