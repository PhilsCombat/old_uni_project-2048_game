/* Copyright 2020, Philipp Albrecht */

#ifndef SEED_H_
#define SEED_H_

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "./Grid.h"
using std::vector;
using std::string;
using std::unordered_map;


class Seed{
 public:
    Seed();
    ~Seed();

    void clear();
    void leftShift();

    void pop_back(Grid* grid, int* score);
    void push_back(const Grid& grid, const int& score);


    const string* at(const size_t& index) const;
    const int scoreAt(const size_t& index) const;

    size_t size() const;

 private:
    unordered_map<char, int> CHAR_TO_INT = {
        {'0', 0}, {'1', 2}, {'2', 4}, {'3', 8}, {'4', 16}, {'5', 32},
        {'6', 64}, {'7', 128}, {'8', 256}, {'9', 512}, {'a', 1024},
        {'b', 2048}, {'c', 4096}, {'d', 8192}, {'e', 16384}, {'f', 32768},
        {'+', 65536}, {'*', 131072}
    };

    unordered_map<int, char> INT_TO_CHAR = {
        {0, '0'}, {2, '1'}, {4, '2'}, {8, '3'}, {16, '4'}, {32, '5'},
        {64, '6'}, {128, '7'}, {256, '8'}, {512, '9'}, {1024, 'a'},
        {2048, 'b'}, {4096, 'c'}, {8192, 'd'}, {16384, 'e'}, {32768, 'f'},
        {65536, '+'}, {131072, '*'}
    };

    vector<string*> _fieldHistory;
    vector<int> _scoreHistory;

    FRIEND_TEST(SEED, clear);
    FRIEND_TEST(SEED, push_back);
    FRIEND_TEST(SEED, leftShift);
};


#endif  // SEED_H_
