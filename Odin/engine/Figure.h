//
// Created by Niclas Schwalbe on 06.04.21.
//
#pragma once

enum class Color;

class Figure {
    public:
        Figure(int val, int color) {
            val_ = val;
            col_ = color;
        }

        Figure(int val, Color color) {
            val_ = val;
            col_ = static_cast<int>(color);
        }
        inline int value() const{
            return (col_ * val_);
        }
        inline int color() const{
            return col_;
        }
    private:
        int val_;
        int col_;
};

