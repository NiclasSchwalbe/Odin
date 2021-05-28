#pragma once

#include <iterator>

class Board;

class BoardIterator {
private:
    int field_;
    const Board* board_;
    
public:

   BoardIterator(int value, const Board* b) :  field_(value),
                                         board_{b}
   {}
    int operator*() const;
    bool operator==(const BoardIterator& other) const;
    bool operator!=(const BoardIterator& other) const;

    BoardIterator& operator++() {
        ++field_;
        return *this;
    }
};