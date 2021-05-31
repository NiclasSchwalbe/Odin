//
// Created by Niclas Schwalbe on 29.05.21.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

#include "doctest/doctest.h"
#include "Odin.h"
#include "Figure.h"


TEST_CASE("Testing Standardboard Fen - PawnMoves"){ 
	Board b(OdinConstants::standardBoardFen); 
	std::vector<std::tuple<int, int, Figure>> moves{};
    generateAllPawnMoves(std::move(moves), b);
    REQUIRE(moves.size() == 16);
    Board c{makeMove(b,moves[9])};
    Board comparison{"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1"};
    REQUIRE(c == comparison);
}

TEST_CASE("TEST MOVES BLACK") {
  Board b("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1");
  std::vector<std::tuple<int, int, Figure>> moves{};
  generateAllPawnMoves(std::move(moves), b);
  REQUIRE(moves.size() == 16);
  Board c{makeMove(b, moves[9])};
  Board comparison{"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1"};
  REQUIRE(c == comparison);
}
