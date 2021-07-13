
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

#include "doctest/doctest.h"
#include "Odin.h"
#include "Figure.h"

TEST_CASE("TEST WHITE KNIGHT MOVES 1 - Knightmove") {
  Board b{"8/8/3P1p2/2P3n1/4N3/2P3p1/3r1P2/8 w - - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  KNIGHTMOVES::generateAllKnightMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 4, "There should be 4 moves available");
}

TEST_CASE("TEST BLACK KNIGHT MOVES 1 - Knightmove") {
  Board b{"8/8/3P1p2/2P3N1/4n3/2P3p1/3r1P2/8 b - - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  KNIGHTMOVES::generateAllKnightMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 5, "There should be 5 moves available");
}

TEST_CASE("TEST WHITE KNIGHT BORDERS 1 - Knightmove") {
  Board b{"8/8/3P1p2/2P3N1/4n3/2P3p1/3r1P2/8 w - - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  KNIGHTMOVES::generateAllKnightMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 6, "There should be 6 moves available");
}

TEST_CASE("TEST WHITE KNIGHT BORDERS 1 - Knightmove") {
  Board b{"8/1N6/3P1p2/2P5/4n3/2P3p1/3r1P2/8 w - - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  KNIGHTMOVES::generateAllKnightMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 2, "There should be 2 moves available");
}

TEST_CASE("TEST BLACK KNIGHT BORDERS 1 - Knightmove") {
  Board b{"8/8/3P1p2/2P5/8/2P3p1/3r1P2/n7 b - - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  KNIGHTMOVES::generateAllKnightMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 2, "There should be 2 moves available");
}

TEST_CASE("TEST BLACK KNIGHT BORDERS 1 - Knightmove") {
  Board b{"8/1n6/3P1p2/2P5/8/2P3p1/3r1P2/8 b - - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  KNIGHTMOVES::generateAllKnightMoves(moves, b);
  CHECK_MESSAGE(moves.size() == 4, "There should be 4 moves available");
}

