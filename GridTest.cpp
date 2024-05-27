/* Copyright 2020, Philipp Albrecht */

#include <gtest/gtest.h>
#include "./Grid.h"

// ===========================================================================


TEST(GRID, setSize) {
    Grid grid;
    ASSERT_EQ(4, grid.edgeSize());
    ASSERT_EQ(16, grid.size());

    grid.setSize(6);
    ASSERT_EQ(6, grid.edgeSize());
    ASSERT_EQ(36, grid.size());

    grid.setSize(2);
    ASSERT_EQ(3, grid.edgeSize());
    ASSERT_EQ(9, grid.size());

    grid.setSize(9);
    ASSERT_EQ(8, grid.edgeSize());
    ASSERT_EQ(64, grid.size());
}


// ___________________________________________________________________________


TEST(GRID, subscript) {
    Grid grid;
    grid[5] = 20;
    ASSERT_EQ(20, grid._grid[5]);
    ASSERT_EQ(20, grid[5]);
}


// ___________________________________________________________________________


TEST(GRID, clear) {
    Grid grid;
    grid[5] = 20;
    grid[8] = 420;

    grid.clear();

    for (int i = 0; i < grid.size(); i++) {
        ASSERT_EQ(0, grid[i]);
    }
}


// ___________________________________________________________________________


TEST(GRID, copyEqual) {
    Grid grid1;
    grid1.setSize(6);
    grid1[6] = 420;
    grid1[30] = 666;

    Grid grid2;
    grid2 = grid1;

    ASSERT_EQ(grid1.size(), grid2.size());
    ASSERT_EQ(grid1.edgeSize(), grid2.edgeSize());

    for (int i = 0; i < grid1.size(); i++) {
        ASSERT_EQ(grid1[i], grid2[i]);
    }
}


// ===========================================================================


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
