#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include "Figure.h"
#include "Odin.h"
#include "doctest/doctest.h"

TEST_CASE("TEST Queen MOVES - No Move") {
  Board b{"rnbqkbn1/ppppppp1/8/3r3p/7P/P7/1PPPPPP1/RNBQKBNR w KQq - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  LONGRANGEPIECEMOVES::generateAllQueenMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 0, "There should be 0 moves available");
}


TEST_CASE("TEST Queen MOVES II") {
  Board b{"rnbqkbn1/ppppppp1/8/3q3p/7P/P7/1PPPPPP1/RNBQKBNR b KQq - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  LONGRANGEPIECEMOVES::generateAllQueenMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 18, "There should be 18 moves available");
}
