//
// Created by Niclas Schwalbe on 06.04.21.
//
#include "../util/Utility.h"
#ifndef ODIN_BOARD_H
#define ODIN_BOARD_H


class Board {
public:
    bool long_castle_white = false;
    bool long_castle_black = false;
    bool short_castle_white = false;
    bool short_castle_black = false;
    char toMove = WHITE;
    char board[8][8] = {0};
    void set_position(const std::string fen, const std::vector<std::string> moves);
};


#endif //ODIN_BOARD_H
