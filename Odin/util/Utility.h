//
// Created by Niclas Schwalbe on 06.04.21.
//


#pragma once
#include <vector>
#include <string>

constexpr std::int8_t WHITE = 1;
constexpr std::int8_t BLACK = 0;
static const std::string standardBoardFen{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};

std::vector<std::string> splitString(std::string s, char limiter);

