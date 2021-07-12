#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include "Figure.h"
#include "Odin.h"
#include "doctest/doctest.h"

/*
TEST_CASE("Test Real Problem - Odin 0.0 - Problem 1") {
  Board initial_board{
      "rnbqkbnr/1ppppppp/8/8/p7/PPP5/3PPPPP/RNBQKBNR w KQkq - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  generateAllLegalMoves(moves, initial_board);
  CHECK(moves.size() != 0);
}


TEST_CASE("Test Real Problem - Odin 0.0 - Problem 1 Partproblem 1") {
  Board initial_board{"rnbqkbnr/1ppppppp/8/8/p7/PPPP4/4PPPP/RNBQKBNR b KQkq - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  generateAllMoves(moves, initial_board);
  REQUIRE(moves.size() == 22);
  CHECK(std::get<1>(moves[21]) == 32);
}


TEST_CASE("Test Real Problem - Odin 0.0 - Problem 1 Partproblem 1.1") {
  Board initial_board{
      "8/8/8/8/p7/PPPP4/4P1PP/RNBQKBNR b KQ - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  generateAllMoves(moves, initial_board);
  REQUIRE(moves.size() == 1);
  CHECK(std::get<1>(moves[0]) == 17);
}

TEST_CASE("Test Real Problem - Odin 0.0 - Problem 1 Partproblem 2") {
  Board initial_board{
      "8/8/8/8/p7/PPPP4/4PPPP/RNBQKBNR b KQ - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  generateAllMoves(moves, initial_board);
  REQUIRE(moves.size() == 1);
  Board comparison{"8/8/8/8/8/PpPP4/4PPPP/RNBQKBNR w KQ - 0 1"};
  Board c1 = makeMove(initial_board, moves[0]);
  CHECK(comparison == c1);
}

TEST_CASE("Test Real Problem - Odin 0.0 - Problem 2") {
  Board initial_board{
      "3k4/8/8/8/8/r7/1B6/7K w - - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  generateAllLegalMoves(moves, initial_board);
  Odin odin{};
  odin.setPosition(initial_board);
  odin.searchOn();
  odin.search();
  std::tuple<int, int, Figure> move = odin.bestMove();
  CHECK(std::get<1>(move) == 8);
  
}
*/


TEST_CASE("Test Real Problem - Odin 0.0 - Problem 3") {
  //find checkmate in 1  
  Board initial_board{"3k4/1Q6/4K3/8/8/8/8/8 w - - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  generateAllLegalMoves(moves, initial_board);
  Odin odin{};
  odin.setPosition(initial_board);
  odin.searchOn();
  odin.search();
  std::tuple<int, int, Figure> move = odin.bestMove();
  CHECK(std::get<0>(move) == 48);
  CHECK(std::get<1>(move) == 56);
}



TEST_CASE("Test Real Problem - Odin 0.0 - Problem 3 - Partproblem 1") {
  //find checkmate in 1  
  Board initial_board{"1Q1k4/8/4K3/8/8/8/8/8 b - - 0 1"};
  CHECK(isCheckMate(initial_board));
}