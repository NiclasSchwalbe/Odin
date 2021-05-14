//
// Created by Niclas Schwalbe on 06.04.21.
//

#pragma once

class Figure {
    public:
        Figure(int val, int color);
        int value() const;
        int color() const;
    private:
        int const val;
        int const col;
};

