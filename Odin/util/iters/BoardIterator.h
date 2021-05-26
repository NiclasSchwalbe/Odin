#pragma once

#include <iterator>
#include "../engine/Board.h"

class BoardIterator {
private:
    int field_;
    const Board* board_;
    
public:

   BoardIterator(int value, const Board* b) :  field_(value),
                                         board_{b}
   {}
    int operator*() const { 
        return (*board_)[field_ / 8][field_ % 8]; 
    }
    bool operator==(const BoardIterator& other) const { 
        return (board_ == other.board_) && (field_ == other.field_); 
    }
    bool operator!=(const BoardIterator& other) const { 
        return !(*this == other); 
    }

    BoardIterator& operator++() {
        ++field_;
        return *this;
    }
};