/* Copyright 2020, Philipp Albrecth */

#include <gtest/gtest.h>
#include "./Logic.h"
#include "./Game.h"

// ===========================================================================


TEST(GAME, parseArgumentsLong) {
    int argc = 5;
    char* argv[5] = {
        const_cast<char*>("./2048Main"),
        const_cast<char*>("--size"),
        const_cast<char*>("6"),
        const_cast<char*>("--undo"),
        const_cast<char*>("10")
    };

    Game game;
    game.parseArguments(argc, argv);
    ASSERT_EQ(6, game._logic._grid.edgeSize());

    ASSERT_EQ(10, game._logic._undo);
}

TEST(GAME, parseArgumentsShort) {
    int argc = 5;
    char* argv[5] = {
        const_cast<char*>("./2048Main"),
        const_cast<char*>("-s"),
        const_cast<char*>("6"),
        const_cast<char*>("-u"),
        const_cast<char*>("10")
    };

    Game game;
    game.parseArguments(argc, argv);
    ASSERT_EQ(6, game._logic._grid.edgeSize());

    ASSERT_EQ(10, game._logic._undo);
}

// ===========================================================================


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
