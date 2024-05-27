/* Copyright 2020, Philipp Albrecht */


#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <array>
#include "./Logic.h"

using std::vector;
using std::array;
using std::cout;
using std::endl;

// ===========================================================================


TEST(LOGIC, placeRandomTile) {
    Logic log;
    log.setGameSize(4);
    ASSERT_EQ(16, log._grid.size());
    for (int i = 0; i < log._grid.size(); i++) {
        ASSERT_EQ(0, log._grid[i]);
    }
    log.placeRandomTile();
    int freeTiles = 0;
     for (int i = 0; i < log._grid.size(); i++) {
        if (log._grid[i] == 0) { freeTiles++; }
    }
    ASSERT_EQ(15, freeTiles);

    log.placeRandomTile();
    freeTiles = 0;
     for (int i = 0; i < log._grid.size(); i++) {
        if (log._grid[i] == 0) { freeTiles++; }
    }
    ASSERT_EQ(14, freeTiles);

    log.placeRandomTile();
    freeTiles = 0;
     for (int i = 0; i < log._grid.size(); i++) {
        if (log._grid[i] == 0) { freeTiles++; }
    }
    ASSERT_EQ(13, freeTiles);
}


TEST(LOGIC, left) {
    Logic log;
    log.setGameSize(5);
    ASSERT_EQ(25, log._grid.size());
    for (int i = 0; i < log._grid.size(); i++) {
        ASSERT_EQ(0, log._grid[i]);
    }

    int test_grid[25] = {
        0, 2, 4, 0, 8,
        0, 2, 4, 0, 4,
        2, 2, 4, 8, 0,
        2, 2, 0, 4, 4,
        2, 4, 2, 0, 0};
    int test_sollution[25] = {
        2, 4, 8, 0, 0,
        2, 8, 0, 0, 0,
        4, 4, 8, 0, 0,
        4, 8, 0, 0, 0,
        2, 4, 2, 0, 0};
    for (int i = 0; i < log._grid.size(); i++) {
        log._grid[i] = test_grid[i];
    }

    ASSERT_EQ(true, log.left());

    for (int i = 0; i < log._grid.size(); i++) {
        ASSERT_EQ(test_sollution[i], log._grid[i]);
    }
    ASSERT_EQ(24, log._score);
    ASSERT_EQ(1, log._turn);
}

// ___________________________________________________________________________


TEST(LOGIC, right) {
    Logic log;
    log.setGameSize(5);
    ASSERT_EQ(25, log._grid.size());
    for (int i = 0; i < log._grid.size(); i++) {
        ASSERT_EQ(0, log._grid[i]);
    }
    int test_grid[25] = {
        8, 0, 4, 2, 0,
        4, 0, 4, 2, 0,
        0, 8, 4, 2, 2,
        4, 4, 0, 2, 2,
        4, 2, 0, 0, 2};
    int test_sollution[25] = {
        0, 0, 8, 4, 2,
        0, 0, 0, 8, 2,
        0, 0, 8, 4, 4,
        0, 0, 0, 8, 4,
        0, 0, 0, 4, 4};
    for (int i = 0; i < log._grid.size(); i++) {
        log._grid[i] = test_grid[i];
    }
    ASSERT_EQ(true, log.right());
    for (int i = 0; i < log._grid.size(); i++) {
        ASSERT_EQ(test_sollution[i], log._grid[i]);
    }
    ASSERT_EQ(28, log._score);
    ASSERT_EQ(1, log._turn);
}


// ___________________________________________________________________________


TEST(LOGIC, up) {
    Logic log;
    log.setGameSize(5);
    ASSERT_EQ(25, log._grid.size());
    for (int i = 0; i < log._grid.size(); i++) {
        ASSERT_EQ(0, log._grid[i]);
    }
    int test_grid[25] = {
        0, 0, 2, 2, 2,
        2, 2, 2, 2, 0,
        4, 4, 4, 0, 0,
        0, 0, 8, 4, 2,
        8, 4, 0, 4, 4};
    int test_sollution[25] = {
        2, 2, 4, 4, 4,
        4, 8, 4, 8, 4,
        8, 0, 8, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0};
    for (int i = 0; i < log._grid.size(); i++) {
        log._grid[i] = test_grid[i];
    }
    ASSERT_EQ(true, log.up());
    for (int i = 0; i < log._grid.size(); i++) {
        ASSERT_EQ(test_sollution[i], log._grid[i]);
    }
    ASSERT_EQ(28, log._score);
    ASSERT_EQ(1, log._turn);

    int test_sollution2[25] = {
        2, 2, 8, 4, 8,
        4, 8, 8, 8, 0,
        8, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0};

    ASSERT_EQ(true, log.up());
    for (int i = 0; i < log._grid.size(); i++) {
        ASSERT_EQ(test_sollution2[i], log._grid[i]);
    }
    ASSERT_EQ(44, log._score);
    ASSERT_EQ(2, log._turn);
    ASSERT_EQ(true, log.up());
    ASSERT_EQ(false, log.up());
}

// __________________________________________________________________________


TEST(LOGIC, down) {
    Logic log;
    log.setGameSize(5);
    ASSERT_EQ(25, log._grid.size());
    for (int i = 0; i < log._grid.size(); i++) {
        ASSERT_EQ(0, log._grid[i]);
    }
    int test_grid[25] = {
        8, 4, 4, 4, 4,
        0, 0, 8, 4, 2,
        4, 4, 4, 0, 0,
        2, 2, 2, 2, 0,
        0, 0, 2, 2, 2};
    int test_sollution[25] = {
        0, 0, 0, 0, 0,
        0, 0, 4, 0, 0,
        8, 0, 8, 0, 0,
        4, 8, 4, 8, 4,
        2, 2, 4, 4, 4};
    for (int i = 0; i < log._grid.size(); i++) {
        log._grid[i] = test_grid[i];
    }
    ASSERT_EQ(true,  log.down());
    for (int i = 0; i < log._grid.size(); i++) {
        ASSERT_EQ(test_sollution[i], log._grid[i]);
    }
    ASSERT_EQ(28, log._score);
    ASSERT_EQ(1, log._turn);
}

// ===========================================================================

TEST(LOGIC, checkWinOrLoss) {
    // check Win nor Loss
    Logic log;
    log.setGameSize(4);
    log._status = 0;
    int test_grid[16] = {
        2, 2, 0, 8,
        4, 2, 8, 4,
        8, 8, 8, 8,
        2, 0, 0, 2};

    for (int i = 0; i < 16; i++) {
        log._grid[i] = test_grid[i];
    }

    log.checkWinOrLoss();

    ASSERT_EQ(0, log._turn);
    ASSERT_EQ(0, log._score);
    ASSERT_EQ(0, log._status);

    for (int i = 0; i < 16; i++) {
        ASSERT_EQ(test_grid[i], log._grid[i]);
    }

    // check Win
    test_grid[5] = 2048;
    log._grid[5] = 2048;
    log.checkWinOrLoss();

    ASSERT_EQ(0, log._turn);
    ASSERT_EQ(0, log._score);
    ASSERT_EQ(1, log._status);

    for (int i = 0; i < 16; i++) {
        ASSERT_EQ(test_grid[i], log._grid[i]);
    }

    // ceck Loss
    /*  2, 4, 2, 8,
        4, 2, 8, 4,
        8, 4, 2, 8,
        2, 8, 4, 2
    */
    log._status = 0;
    test_grid[1] = 4;
    test_grid[2] = 2;
    test_grid[5] = 2;
    test_grid[9] = 4;
    test_grid[10] = 2;
    test_grid[13] = 8;
    test_grid[14] = 4;
    for (int i = 0; i < 16; i++) {
        log._grid[i] = test_grid[i];
    }

    log.checkWinOrLoss();

    ASSERT_EQ(0, log._turn);
    ASSERT_EQ(0, log._score);
    ASSERT_EQ(-1, log._status);

    for (int i = 0; i < 16; i++) {
        ASSERT_EQ(test_grid[i], log._grid[i]);
    }
}

// ___________________________________________________________________________


TEST(LOGIC, makeStepAndUndo) {
    Logic log;
    log.setGameSize(3);
    log._status = 0;
    log._undo = 10;

    int test_grid[9] = {1024, 8, 8, 1024, 2, 0, 0, 4, 0};
    for (int i = 0; i < 9; i++) {
        log._grid[i] = test_grid[i];
    }

    Grid grid0;
    Grid grid1;
    Grid grid2;
    Grid grid3;

    grid0 = log._grid;

    // up
    log.makeStep(1);
    ASSERT_EQ(1, log._status);
    grid1 = log._grid;
    // right
    log.makeStep(2);
    grid2 = log._grid;
    // down
    log.makeStep(3);
    grid3 = log._grid;
    // left
    log.makeStep(4);

    // undo
    log.undo();
    ASSERT_EQ(1, log._status);
    for (int i = 0; i < 9; i++) {
        ASSERT_EQ(grid3[i], log._grid[i]);
    }

    log.undo();
    ASSERT_EQ(1, log._status);
    for (int i = 0; i < 9; i++) {
        ASSERT_EQ(grid2[i], log._grid[i]);
    }

    log.undo();
    ASSERT_EQ(1, log._status);
    for (int i = 0; i < 9; i++) {
        ASSERT_EQ(grid1[i], log._grid[i]);
    }

    log.undo();
    ASSERT_EQ(-2, log._status);
    for (int i = 0; i < 9; i++) {
        ASSERT_EQ(grid0[i], log._grid[i]);
    }

    log.undo();
    ASSERT_EQ(-2, log._status);
    for (int i = 0; i < 9; i++) {
        ASSERT_EQ(grid0[i], log._grid[i]);
    }
}


// ===========================================================================
// ===========================================================================

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

