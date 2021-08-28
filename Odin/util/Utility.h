//
// Created by Niclas Schwalbe on 06.04.21.

#pragma once

#include <vector>
#include <string>
#include <array>
#include "../engine/Figure.h"

class Board;
enum class Color { BLACK = -1, WHITE = 1 };

namespace FIGURES {
constexpr Figure EMPTY(0, Color::WHITE);
constexpr Figure BPAWN(1, Color::BLACK);
constexpr Figure BKNIGHT(2, Color::BLACK);
constexpr Figure BBISHOP(3, Color::BLACK);
constexpr Figure BROOK(4, Color::BLACK);
constexpr Figure BQUEEN(5, Color::BLACK);
constexpr Figure BKING(6, Color::BLACK);
constexpr Figure WPAWN(1, Color::WHITE);
constexpr Figure WKNIGHT(2, Color::WHITE);
constexpr Figure WBISHOP(3, Color::WHITE);
constexpr Figure WROOK(4, Color::WHITE);
constexpr Figure WQUEEN(5, Color::WHITE);
constexpr Figure WKING(6, Color::WHITE);
}

/*
 * int mg_value[6] = { 82, 337, 365, 477, 1025,  0};
 * taken from https://www.chessprogramming.org/PeSTO%27s_Evaluation_Function
 */
namespace PIECEEVALUATONVALUES {

constexpr double pieceEvaluationValue(int val){
  if  (val < 0){
    val = -val;
  }
  switch (val) {
    using namespace FIGURES;
    case WPAWN.value():
        return 82;
    case WKNIGHT.value():
        return 337;
    case WBISHOP.value():
      return 356;
    case WROOK.value():
      return 477;
    case WQUEEN.value():
      return 1025;
    default: return 0;
  }

}

}
//* taken from https://www.chessprogramming.org/PeSTO%27s_Evaluation_Function
namespace PIECEEVALUATONTABLES {
template<int VALUE=0> extern std::array<double, 64> TABLE;
}



std::vector<std::string> splitString(std::string s, char limiter);
void printBoard(const Board &);

inline bool inBounds(int x, int y) {
  return x < 8 && x >= 0 && y < 8 && y >= 0;
}

