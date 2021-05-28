#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../engine/Board.h"
#include "doctest/doctest.h"

TEST_CASE("Testing EMPTY BOARD") {
  Board b("8/8/8/8/8/8/8/8");
  for (auto k : b) {
    REQUIRE(k == 0);
  }
}