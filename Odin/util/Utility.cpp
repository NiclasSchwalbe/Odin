//
// Created by Niclas Schwalbe on 06.04.21.
//

#include "Utility.h"



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

