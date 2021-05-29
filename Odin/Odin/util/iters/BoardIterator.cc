#include "../../engine/Board.h"

int BoardIterator::operator*() const { 
	return (board_)->operator[](field_/ 8)[field_ % 8]; 
}
bool BoardIterator::operator==(const BoardIterator& other) const {
	return (board_ == other.board_) && (field_ == other.field_);
}
bool BoardIterator::operator!=(const BoardIterator& other) const { 
	return !(*this == other); 
}