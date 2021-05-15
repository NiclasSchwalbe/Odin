//
// Created by Niclas Schwalbe on 06.04.21.
//

#include "Figure.h"

Figure::Figure(int val, int color) {
    this->val = val;
    this->col = color;
}

int Figure::value() const{
    return (this->col * this->val);
}

int Figure::color() const{
    return this->col;
}

