//
// Created by Niclas Schwalbe on 06.04.21.
//

#include "Utility.h"
#include "Figure.h"

const Figure BPAWN(1, BLACK);
const Figure BKNIGHT(2, BLACK);
const Figure BBISHOP(3, BLACK);
const Figure BROOK(4, BLACK);
const Figure BQUEEN(5, BLACK);
const Figure BKING(6, BLACK);
const Figure WPAWN(1, WHITE);
const Figure WKNIGHT(2, WHITE);
const Figure WBISHOP(3, WHITE);
const Figure WROOK(4, WHITE);
const Figure WQUEEN(5, WHITE);
const Figure WKING(6, WHITE);

std::vector<std::string> splitString(std::string s, char limiter) {
    std::vector<std::string> tokens;
    std::string token;


    for (const auto c: s) {
        if (c == limiter)
            token += c;
        else {
            if (token.length() != 0) {
                tokens.push_back(token);
                token.clear();
            }
        }
    }

    if (token.length() != 0) {
        tokens.push_back(token);
    }

    return tokens;
}

