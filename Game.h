/* Copyright 2020, Philipp Albrecht */

#ifndef GAME_H_
#define GAME_H_

#include <gtest/gtest.h>
#include "./Logic.h"
#include "./Graphic.h"


class Game{
 public:
    Game();
    ~Game();

    void play();
    void parseArguments(const int& argc, char** argv);

 private:
    bool _running;
    Logic _logic;
    Graphic _graphic;

    void printUsageAndExit();
    void processKeyInput(const int key);
    void initialize();

    FRIEND_TEST(GAME, parseArgumentsLong);
    FRIEND_TEST(GAME, parseArgumentsShort);
};


#endif  // GAME_H_
