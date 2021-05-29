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