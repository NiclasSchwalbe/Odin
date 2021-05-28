//
// Created by Niclas Schwalbe on 06.04.21.
//
#pragma once


#include <string>
#include <vector>
#include <array>
#include "../util/Utility.h"
#include "../iters/BoardIterator.h"

class Board {
public:

    /*
    bool long_castle_white_{false};
    bool long_castle_black_{false};
    bool short_castle_white_{false};
    bool short_castle_black_{false};
    Color to_move_{Color::WHITE};
    */
    //double intrinsic_value_;

    std::array<std::array<int, 8>, 8> board_{};
    //void setPosition(const std::string& fen, const std::vector<std::string>& moves);
    explicit Board(const std::string&);
    Board(const Board &b) {
        *this = b;
    }

    std::array<int, 8> operator[](int i) const { return board_[i]; }

    BoardIterator begin() const;
    BoardIterator end() const;

private:


};
