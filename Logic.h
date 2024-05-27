/* Copyright 2020, Philipp Albrecht */

#ifndef LOGIC_H_
#define LOGIC_H_

#include <gtest/gtest.h>
#include "./Grid.h"
#include "./Seed.h"

// ___________________________________________________________________________
class Graphic;


class Logic{
 public:
    Logic();
    ~Logic();

    void resetGame();
    void checkWinOrLoss();
    void setAllowedUndo(unsigned const int& allowed);
    void setGameSize(int size);
    void undo();

    bool makeStep(const int& direction);
    int getStatus() const;

 private:
    unsigned int _undo;
    int _status;
    int _turn;
    int _score;

    Grid _grid;
    Seed _seed;

    void placeRandomTile();

    bool up();
    bool down();
    bool left();
    bool right();

    friend Graphic;

    FRIEND_TEST(LOGIC, left);
    FRIEND_TEST(LOGIC, right);
    FRIEND_TEST(LOGIC, up);
    FRIEND_TEST(LOGIC, down);
    FRIEND_TEST(LOGIC, placeRandomTile);
    FRIEND_TEST(LOGIC, checkWinOrLoss);
    FRIEND_TEST(LOGIC, makeStepAndUndo);
    FRIEND_TEST(LOGIC, makeStepAndUndo);
    FRIEND_TEST(GAME, parseArgumentsLong);
    FRIEND_TEST(GAME, parseArgumentsShort);
};

#endif  // LOGIC_H_
