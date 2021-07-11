#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

#include "doctest/doctest.h"
#include "Odin.h"
#include "Figure.h"

TEST_CASE("Test MAKE MOVE - EP") {
  Board initial_board{"8/8/8/3pP3/8/8/8/8 w - - 0 1"};
  initial_board.en_passant_field_ = 43;
  std::vector<std::tuple<int, int, Figure>> moves{};
  Board comparison{"8/8/3P4/8/8/8/8/8 b - - 0 1"};
  Board actual{makeMove(initial_board, std::make_tuple(36, 43, EMPTY))};
  CHECK(actual == comparison);
}

TEST_CASE("Test MAKE MOVE - Castle") {
  Board initial_board{"8/8/8/8/8/8/PPPP4/R3K3 w Q - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  Board comparison{"8/8/8/8/8/8/PPPP4/2KR4 b - - 0 1"};
  Board actual{makeMove(initial_board, std::make_tuple(4, 2, EMPTY))};
  CHECK(actual == comparison);
}

TEST_CASE("Test MAKE MOVE - Castle Black") {
  Board initial_board{"4k2r/8/8/8/8/8/PPPP4/2KR4 b - - 0 1"};
  std::vector<std::tuple<int, int, Figure>> moves{};
  Board comparison{"5rk1/8/8/8/8/8/PPPP4/2KR4 w - - 0 1"};
  Board actual{makeMove(initial_board, std::make_tuple(60, 62, EMPTY))};
  std::cout << actual;
  std::cout << comparison;
  CHECK(actual == comparison);
}