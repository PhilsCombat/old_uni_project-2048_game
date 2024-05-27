/* Copyright 2020, Philipp Albrecht */

#include "./Game.h"

int main(int argc, char** argv) {
    Game game;
    game.parseArguments(argc, argv);
    game.play();
}
