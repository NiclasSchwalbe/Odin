//
// Created by Niclas Schwalbe on 06.04.21.
//
#pragma once

#include <array>
#include <string>
#include "../util/Utility.h"

class Board {
public:
    bool long_castle_white = false;
    bool long_castle_black = false;
    bool short_castle_white = false;
    bool short_castle_black = false;
    char toMove = WHITE;
    double intrinsicValue;
    std::array<std::array<int, 8>, 8> board;
    void set_position(const std::string& fen, const std::vector<std::string>& moves);

    Board(const std::string& fen);

private:


};
