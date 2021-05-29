#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "Board.h"
#include "doctest/doctest.h"

TEST_CASE("Testing  Initalization"){
  Board b("8/8/8/8/8/8/8/8");
}

TEST_CASE("Testing EMPTY BOARD") {
  Board b("8/8/8/8/8/8/8/8");
  for (auto k : b) {
    REQUIRE(k == 0);
  }
}

TEST_CASE("Testing KINGS ONLY") {
  Board b("8/3k4/8/8/8/8/3K4/8 w - - 0 1");
  REQUIRE(b.to_move_ == Color::WHITE);
  for (int i = 0; i < 64; i++) {
    CAPTURE(i);
    if (i == 11) {
      REQUIRE(b(i) == WKING.value());
    } else if (i == 51) {
      REQUIRE(b(i) == BKING.value());
    } else {
      REQUIRE(b(i) == 0);

    }
  }
}

TEST_CASE("Testing Castling and more...") {
  Board b("rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 1");
  REQUIRE(b.to_move_ == Color::WHITE);
  REQUIRE(b.en_passant_field_ == 43);
  REQUIRE(b.long_castle_black_ == true);
  REQUIRE(b.long_castle_white_ == true);
  REQUIRE(b.short_castle_black_== true);
  REQUIRE(b.short_castle_white_== true);
}

