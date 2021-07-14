#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include "Figure.h"
#include "Odin.h"
#include "doctest/doctest.h"


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
  CHECK(std::get<1>(move) == 16);
  
}

TEST_CASE("Test Real Problem - Odin 0.0 - Problem 3 - Partproblem 1") {
  //find checkmate in 1  
  Board initial_board{"1Q1k4/8/4K3/8/8/8/8/8 b - - 0 1"};
  CHECK(isCheckMate(initial_board));
}


TEST_CASE("Test Real Problem - Odin 0.0 - Problem 4 - Partproblem 1") {
  Board initial_board{"rnbqkQnr/1p2p1pp/3p4/2p5/p7/2N1P3/PPPP1PPP/R1B1KBNR b KQkq - 0 1"};
  CHECK(!isCheckMate(initial_board));
}


TEST_CASE("Test Real Problem - Odin 0.0 - Problem 5 - Partproblem 1") {
  Board initial_board{
      "rnbqkbnr/1pppppp1/7p/p7/8/2PQ4/PP1PPPPP/RNB1KBNR b KQkq - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves;
  KNIGHTMOVES::generateAllKnightMoves(moves, initial_board);
  CHECK(moves.size() == 3);
}

TEST_CASE("Test Real Problem - Odin 0.0 - Problem 6 - Partproblem 1") {
  Board initial_board{
      "rnbqkbnr/1pppppp1/7p/p7/8/2PQ4/PP1PPPPP/RNB1KBNR w KQkq - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves;
  PAWNMOVES::generateAllPawnMoves(moves, initial_board);
  CHECK(moves.size() == 13);
}

TEST_CASE("Test Real Problem - Odin 0.0 - Problem 6 - Partproblem 2") {
  Board initial_board{
      "rnbqkbnr/1pppppp1/8/p6p/8/2PQ4/PP1PPPPP/RNB1KBNR w KQkq - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves;
  PAWNMOVES::generateAllPawnMoves(moves, initial_board);
  CHECK(moves.size() == 13);
}

TEST_CASE("Test Real Problem - Odin 0.0 - Problem 6 - Partproblem 3") {
  Board initial_board{
      "rnbqkbnr/1pppppp1/8/p6p/8/2PQ4/PP1PPPPP/RNB1KBNR b KQkq - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves;
  PAWNMOVES::generateAllPawnMoves(moves, initial_board);
  CHECK(moves.size() == 14);
}

TEST_CASE("Test Real Problem - Odin 0.0 - Problem 6 - Partproblem 4") {
  Board initial_board{
      "rnbqkbnr/1pppppp1/8/p6p/8/2PQ4/PP1PPPPP/RNB1KBNR w KQkq - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves;
  generateAllLegalMoves(moves, initial_board);
  CHECK(moves.size() == 33);
}