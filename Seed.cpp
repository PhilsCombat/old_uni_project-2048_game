/* Copyright 2020, Philipp Albrecht */

#include <vector>
#include <string>
#include <unordered_map>
#include "./Seed.h"
#include "./Grid.h"

using std::vector;
using std::string;

// ===========================================================================


Seed::Seed() {}

Seed::~Seed() {
    for (string* str : _fieldHistory) { delete str; }
}

// ___________________________________________________________________________


size_t Seed::size() const { return _fieldHistory.size(); }


// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _


const string* Seed::at(const size_t& index) const {
    return _fieldHistory[index];
}


const int Seed::scoreAt(const size_t& index) const {
    return _scoreHistory[index];
}


// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

void Seed::clear() {
    for (string* str : _fieldHistory) {
        delete str;
    }
    _fieldHistory.clear();
    _scoreHistory.clear();
}


// ___________________________________________________________________________


void Seed::leftShift() {
    if (_fieldHistory.size() == 0) { return; }
    delete _fieldHistory[0];
    for (size_t i = 0; i < _fieldHistory.size() - 1; i++) {
        _fieldHistory[i] = _fieldHistory[i + 1];
        _scoreHistory[i] = _scoreHistory[i + 1];
    }
    _fieldHistory.pop_back();
    _scoreHistory.pop_back();
}


// ___________________________________________________________________________

void Seed::push_back(const Grid& grid, const int& score) {
    string* seed = new string;
    for (int i = 0; i < grid.size(); i++) {
        seed -> push_back(INT_TO_CHAR[grid[i]]);
    }
    _fieldHistory.push_back(seed);
    _scoreHistory.push_back(score);
}


// ___________________________________________________________________________


void Seed::pop_back(Grid* grid, int* score) {
    if (_fieldHistory.size() == 0) { return; }

    *score = _scoreHistory.at(_scoreHistory.size() - 1);

    string* seed = _fieldHistory.at(_fieldHistory.size() - 1);
    _fieldHistory.pop_back();
    _scoreHistory.pop_back();
    for (int i = 0; i < grid -> size(); i++) {
        (*grid)[i] = CHAR_TO_INT[(*seed)[i]];
    }
    delete seed;
}
