//
// Created by Niclas Schwalbe on 06.04.21.
//


#pragma once
#include <vector>
#include <string>
#include "../engine/Figure.h"

enum class Color { BLACK = -1, WHITE = 1};

const Figure EMPTY(0, Color::WHITE);
const Figure BPAWN(1, Color::BLACK);
const Figure BKNIGHT(2, Color::BLACK);
const Figure BBISHOP(3, Color::BLACK);
const Figure BROOK(4, Color::BLACK);
const Figure BQUEEN(5, Color::BLACK);
const Figure BKING(6, Color::BLACK);
const Figure WPAWN(1, Color::WHITE);
const Figure WKNIGHT(2, Color::WHITE);
const Figure WBISHOP(3, Color::WHITE);
const Figure WROOK(4, Color::WHITE);
const Figure WQUEEN(5, Color::WHITE);
const Figure WKING(6, Color::WHITE);

std::vector<std::string> splitString(std::string s, char limiter);

