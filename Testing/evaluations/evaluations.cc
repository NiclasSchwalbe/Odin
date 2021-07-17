//
// Created by Niclas Schwalbe on 17.07.21.
//


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

#include "doctest/doctest.h"
#include "Odin.h"
#include "Figure.h"
#include "Utility.h"

TEST_CASE("EVAL CHECKMATE") {
Board initial_board{"4k3/Q7/5K2/8/8/8/8/8 w - - 0 1"};
initial_board.en_passant_field_ = -1;
std::vector<std::tuple<int, int, Figure>> moves{};
Board comparison{"4k3/4Q3/5K2/8/8/8/8/8 b - - 0 1"};
Odin odin{};
odin.searchOn();
odin.search();
Board actual = makeMove(initial_board, odin.bestMove());
CHECK(actual == comparison);
}