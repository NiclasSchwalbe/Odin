#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

#include "doctest/doctest.h"
#include "Odin.h"
#include "Figure.h"

TEST_CASE("TEST Castle -- WHITE") {
  Board b{"r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  KINGMOVES::generateAllKingMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 4, "There should be 4 moves available");
}

TEST_CASE("TEST Castle -- BLACK") {
  Board b{"r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R b KQk - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  KINGMOVES::generateAllKingMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 3, "There should be 3 moves available. Black must not castle long.");
}


TEST_CASE("TEST Impossible Castle -- WHITE") {
  Board b{"4k2r/pp1pppPp/8/8/8/8/PPPPPPPP/R2bK1bR w KQkq - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  KINGMOVES::generateAllKingMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 2, "There should be 2 moves available");
}

TEST_CASE("TEST Impossible Castle -- BLACK") {
  Board b{"4k2r/pp1pppPp/8/8/8/8/PPPPPPPP/R2bK1bR b KQkq - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  KINGMOVES::generateAllKingMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 2, "There should be 2 moves available");
}

TEST_CASE("TEST Usal Moves -- WHITE") {
  Board b{"8/1k6/8/8/8/8/6K1/8 w - - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  KINGMOVES::generateAllKingMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 8, "There should be 8 moves available");
}

TEST_CASE("TEST Usal Moves -- Black") {
  Board b{"8/1k6/8/8/8/8/6K1/8 b - - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  KINGMOVES::generateAllKingMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 8, "There should be 8 moves available");
}

