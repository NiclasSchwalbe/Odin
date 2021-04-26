//
// Created by Niclas Schwalbe on 06.04.21.
//

#include "Figure.h"

Figure::Figure(int val, int color) {
    this->val = val;
    this->col = color;
}

Figure::value(){
    return (this->color * this->val);
}

Figure::color(){
    return this->col();
}

