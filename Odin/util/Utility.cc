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

namespace PIECEEVALUATONTABLES {
template<> constexpr std::array<double, 64> TABLE<FIGURES::WPAWN.value()>{{0, 0, 0, 0, 0, 0, 0, 0,
                                                                           98, 134, 61, 95, 68, 126, 34, -11,
                                                                           -6, 7, 26, 31, 65, 56, 25, -20,
                                                                           -14, 13, 6, 21, 23, 12, 17, -23,
                                                                           -27, -2, -5, 12, 17, 6, 10, -25,
                                                                           -26, -4, -4, -10, 3, 3, 33, -12,
                                                                           -35, -1, -20, -23, -15, 24, 38, -22,
                                                                           0, 0, 0, 0, 0, 0, 0, 0
                                                                          }};

template<> constexpr std::array<double, 64> TABLE<FIGURES::WKNIGHT.value()>{{
                                                                                -167, -89, -34, -49, 61, -97, -15, -107,
                                                                                -73, -41, 72, 36, 23, 62, 7, -17,
                                                                                -47, 60, 37, 65, 84, 129, 73, 44,
                                                                                -9, 17, 19, 53, 37, 69, 18, 22,
                                                                                -13, 4, 16, 13, 28, 19, 21, -8,
                                                                                -23, -9, 12, 10, 19, 17, 25, -16,
                                                                                -29, -53, -12, -3, -1, 18, -14, -19,
                                                                                -105, -21, -58, -33, -17, -28, -19, -23,
                                                                            }};

template<> constexpr std::array<double, 64> TABLE<FIGURES::WBISHOP.value()>{{
                                                                                -167, -89, -34, -49, 61, -97, -15, -107,
                                                                                -73, -41, 72, 36, 23, 62, 7, -17,
                                                                                -47, 60, 37, 65, 84, 129, 73, 44,
                                                                                -9, 17, 19, 53, 37, 69, 18, 22,
                                                                                -13, 4, 16, 13, 28, 19, 21, -8,
                                                                                -23, -9, 12, 10, 19, 17, 25, -16,
                                                                                -29, -53, -12, -3, -1, 18, -14, -19,
                                                                                -105, -21, -58, -33, -17, -28, -19, -23,
                                                                            }};

template<> constexpr std::array<double, 64> TABLE<FIGURES::WROOK.value()>{{
                                                                              32, 42, 32, 51, 63, 9, 31, 43,
                                                                              27, 32, 58, 62, 80, 67, 26, 44,
                                                                              -5, 19, 26, 36, 17, 45, 61, 16,
                                                                              -24, -11, 7, 26, 24, 35, -8, -20,
                                                                              -36, -26, -12, -1, 9, -7, 6, -23,
                                                                              -45, -25, -16, -17, 3, 0, -5, -33,
                                                                              -44, -16, -20, -9, -1, 11, -6, -71,
                                                                              -19, -13, 1, 17, 16, 7, -37, -26,
                                                                          }};
template<> constexpr std::array<double, 64> TABLE<FIGURES::WQUEEN.value()>{{
                                                                               -9, 22, 22, 27, 27, 19, 10, 20,
                                                                               -17, 20, 32, 41, 58, 25, 30, 0,
                                                                               -20, 6, 9, 49, 47, 35, 19, 9,
                                                                               3, 22, 24, 45, 57, 40, 57, 36,
                                                                               -18, 28, 19, 47, 31, 34, 39, 23,
                                                                               -16, -27, 15, 6, 9, 17, 10, 5,
                                                                               -22, -23, -30, -16, -16, -23, -36, -32,
                                                                               -33, -28, -22, -43, -5, -32, -20, -41,
                                                                           }
};


template<> constexpr std::array<double, 64> TABLE<FIGURES::WKING.value()>{{
                                                                              -65, 23, 16, -15, -56, -34, 2, 13,
                                                                              29, -1, -20, -7, -8, -4, -38, -29,
                                                                              -9, 24, 2, -16, -20, 6, 22, -22,
                                                                              -17, -20, -12, -27, -30, -25, -14, -36,
                                                                              -49, -1, -27, -39, -46, -44, -33, -51,
                                                                              -14, -14, -22, -46, -44, -30, -15, -27,
                                                                              1, 7, -8, -64, -43, -16, 9, 8,
                                                                              -15, 36, 12, -54, 8, -28, 24, 14,
                                                                          }
};

}