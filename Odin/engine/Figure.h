//
// Created by Niclas Schwalbe on 06.04.21.
//

#ifndef ODIN_FIGURE_H
#define ODIN_FIGURE_H

class Figure {
    public:
        Figure(int val, int color);
        int value() const;
        int color() const;
    private:
        int const val;
        int const col;
};

#endif //ODIN_FIGURE_H
