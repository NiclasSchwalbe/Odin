//
// Created by Niclas Schwalbe on 06.04.21.
//
#include <iostream>
#include "Utility.h"
#include "Board.h"

std::vector<std::string> splitString(std::string s, char limiter) {
    std::vector<std::string> tokens;
    std::string token;


    for (const auto c: s) {
        if (c != limiter)
            token += c;
        else {
            if (token.length() != 0) {
                tokens.push_back(token);
                token.clear();
            }
        }
    }

    if (token.length() != 0) {
        tokens.push_back(token);
    }

    return tokens;
}

void printBoard(const Board& board){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      std::cout << board[7 - i][j] << ' ';
    }
    std::cout << std::endl;
  }
}