//
// Created by Niclas Schwalbe on 06.04.21.
//
#pragma once


#include <string>
#include <vector>
#include <array>
#include "../util/Utility.h"

class Board {
public:

    bool long_castle_white_{false};
    bool long_castle_black_{false};
    bool short_castle_white_{false};
    bool short_castle_black_{false};
    color to_move_{WHITE};
    double intrinsic_value_;

    std::array<std::array<int, 8>, 8> board_{};
    void setPosition(const std::string& fen, const std::vector<std::string>& moves);
    explicit Board(const std::string&);

private:


};
