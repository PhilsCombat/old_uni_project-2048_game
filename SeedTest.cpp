/* Copyright 2020, Philipp Albrecht */

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "./Grid.h"
#include "./Seed.h"

// ===========================================================================


TEST(SEED, clear) {
    Grid grid;
    Seed seed;

    seed.push_back(grid, 1);
    seed.push_back(grid, 2);

    ASSERT_EQ(2, seed.size());
    ASSERT_EQ(2, seed._fieldHistory.size());
    ASSERT_EQ(2, seed._scoreHistory.size());

    seed.clear();

    ASSERT_EQ(0, seed.size());
    ASSERT_EQ(0, seed._fieldHistory.size());
    ASSERT_EQ(0, seed._scoreHistory.size());
}


// ___________________________________________________________________________


TEST(SEED, push_back) {
    const int test_grid1[25] = {
        0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384,
        32768, 65536, 131072, 0, 0, 16, 0, 0, 128, 0
    };

    const int test_grid2[9] = {2, 2, 16, 128, 2, 0, 2, 2, 2};

    string test_string1 = "0123456789abcdef+*0040070";
    string test_string2 = "114710111";

    Seed seed;
    Grid grid;
    grid.setSize(5);
    ASSERT_EQ(0, seed.size());

    for (int i = 0; i < 25; i++) { grid[i] = test_grid1[i]; }

    seed.push_back(grid, 420);
    ASSERT_EQ(1, seed.size());
    ASSERT_EQ(test_string1, *(seed._fieldHistory[0]));
    ASSERT_EQ(420, seed._scoreHistory[0]);

    grid.setSize(3);
    for (int i = 0; i < 9; i++) { grid[i] = test_grid2[i]; }
    seed.push_back(grid, 69);
    ASSERT_EQ(2, seed.size());
    ASSERT_EQ(test_string2, *(seed._fieldHistory[1]));
    ASSERT_EQ(69, seed._scoreHistory[1]);
}


// ___________________________________________________________________________


TEST(SEED, pop_back) {
    const int test_grid1[25] = {
        0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384,
        32768, 65536, 131072, 0, 0, 16, 0, 0, 128, 0
    };

    const int test_grid2[9] = {2, 2, 16, 128, 2, 0, 2, 2, 2};

    string test_string1 = "0123456789abcdef+*0040070";
    string test_string2 = "114710111";

    Seed seed;
    Grid grid;

    grid.setSize(5);
    for (int i = 0; i < 25; i++) { grid[i] = test_grid1[i]; }
    seed.push_back(grid, 25);

    grid.setSize(3);
    for (int i = 0; i < 9; i++) { grid[i] = test_grid2[i]; }
    seed.push_back(grid, 9);

    ASSERT_EQ(test_string1, *(seed.at(0)));
    ASSERT_EQ(test_string2, *(seed.at(1)));

    grid.clear();

    int score;
    seed.pop_back(&grid, &score);
    ASSERT_EQ(9, score);
    for (int i = 0; i < 9; i++) {
        ASSERT_EQ(test_grid2[i], grid[i]);
    }

    grid.setSize(5);
    seed.pop_back(&grid, &score);
    ASSERT_EQ(25, score);
    for (int i = 0; i < 25; i++) {
        ASSERT_EQ(test_grid1[i], grid[i]);
    }
}


// __________________________________________________________________________


TEST(SEED, leftShift) {
    Seed seed;
    Grid grid1;
    Grid grid2;
    Grid grid3;

    grid1.setSize(3);
    grid2.setSize(3);
    grid3.setSize(3);

    grid1[0] = 2;
    grid2[0] = 4;
    grid3[0] = 8;

    seed.push_back(grid1, 111);
    seed.push_back(grid2, 222);
    seed.push_back(grid3, 333);

    ASSERT_EQ(3, seed.size());

    seed.leftShift();
    ASSERT_EQ(2, seed.size());
    ASSERT_EQ("200000000", *(seed.at(0)));
    ASSERT_EQ("300000000", *(seed.at(1)));
    ASSERT_EQ(222, seed.scoreAt(0));
    ASSERT_EQ(333, seed.scoreAt(1));

    seed.leftShift();
    ASSERT_EQ(1, seed.size());
    ASSERT_EQ("300000000", *(seed.at(0)));
    ASSERT_EQ(333, seed.scoreAt(0));

    seed.leftShift();
    ASSERT_EQ(0, seed.size());

    // see if Test crashes
    seed.leftShift();
}


// ===========================================================================


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
