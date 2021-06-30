#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

#include "doctest/doctest.h"
#include "Odin.h"
#include "Figure.h"

TEST_CASE("TEST WHITE BISHOP MOVES I") {
  Board b{"8/8/8/3P1p2/4B3/3P1P2/8/8 w - - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  generateAllBishopMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 1, "There should be 1 moves available");
}

TEST_CASE("TEST WHITE BISHOP MOVES II") {
  Board b{"8/8/8/3B4/8/8/8/8 w - - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  generateAllBishopMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 13, "There should be 13 moves available");
}
