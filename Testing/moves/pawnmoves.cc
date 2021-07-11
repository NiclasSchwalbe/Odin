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


TEST_CASE("Testing Standardboard Fen - PawnMoves") {
    Board b(OdinConstants::standardBoardFen);
    std::vector<std::tuple<int, int, Figure>> moves{};
    generateAllPawnMoves(moves, b);
    REQUIRE(moves.size() == 16);
    Board c{ makeMove(b,moves[9]) };
    Board comparison{ "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1" };
    comparison.en_passant_field_ = 20;

    REQUIRE(c == comparison);
}

TEST_CASE("TEST MOVES BLACK - PawnMoves") {
    Board b("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1");
    std::vector<std::tuple<int, int, Figure>> moves{};
    generateAllPawnMoves(moves, b);
    REQUIRE(moves.size() == 16);
    Board c{ makeMove(b, moves[9]) };
    Board comparison{ "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1" };
    comparison.en_passant_field_ = 44;
    REQUIRE(c == comparison);
}

TEST_CASE("TEST Capture White - PawnMoves") {
    Board b("rnbqkbnr/ppp1p1pp/8/3p1p2/4P3/P7/1PPP1PPP/RNBQKBNR w KQkq - 0 1");
    MESSAGE("First board initialized"); 
    std::vector<std::tuple<int, int, Figure>> moves{};
    generateAllPawnMoves(moves, b);
    CHECK_MESSAGE(moves.size() == 16, "Sizes do not match");
    Board c{ makeMove(b, moves[15]) };
    Board comparison{ "rnbqkbnr/ppp1p1pp/8/3p1P2/8/P7/1PPP1PPP/RNBQKBNR b KQkq - 0 1" };
    MESSAGE("Second board initialized"); 
    CHECK_MESSAGE(c == comparison, "Comparison did not fit");

    Board c2 = makeMove(b, moves[14]);
    Board comparison2{ "rnbqkbnr/ppp1p1pp/8/3P1p2/8/P7/1PPP1PPP/RNBQKBNR b KQkq - 0 1" };
    MESSAGE("Third board initialized"); 
    CHECK_MESSAGE(c2 == comparison2, "Comparison did not fit");
}


TEST_CASE("TEST Capture Black - PawnMoves") {
  Board b("rnbqkbnr/ppp1pppp/8/3p4/2N1R2P/8/PPPPPPP1/RNBQKB2 b Qkq - 0 1");
  std::vector<std::tuple<int, int, Figure>> moves{};
  generateAllPawnMoves(moves, b);
  REQUIRE(moves.size() == 17);
  MESSAGE("Size correct");
  Board c{makeMove(b, moves[2])};
  Board c2{makeMove(b, moves[1])};
  Board comparison{
      "rnbqkbnr/ppp1pppp/8/8/2p1R2P/8/PPPPPPP1/RNBQKB2 w Qkq - 0 1"};
  Board comparison2{
      "rnbqkbnr/ppp1pppp/8/8/2N1p2P/8/PPPPPPP1/RNBQKB2 w Qkq - 0 1"};
  REQUIRE(c == comparison);
  REQUIRE(c2 == comparison2);
}


