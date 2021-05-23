//
// Created by Niclas Schwalbe on 06.04.21.
//
#pragma once

class Figure {
    public:
        Figure(int val, int color);
        inline int value() const{
            return (this->col * this->val);
        }
        inline int color() const{
            return this->col;
        }
    private:
        int val;
        int col;
};

