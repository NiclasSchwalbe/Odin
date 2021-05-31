//
// Created by Niclas Schwalbe on 06.04.21.
//
#pragma once

#include <string>
#include <vector>
#include <array>
#include "Utility.h"

class Board {
 public:

 public:
  struct BoardIterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int;
    using reference = const int &;

    BoardIterator(pointer ptr, const Board* b) :
    m_ptr(ptr), board_{b} {}

    reference operator*() const { return (*board_)(m_ptr); }
    //pointer operator->() { return  (*board_)(m_ptr); }
    BoardIterator &operator++() {
      m_ptr++;
      return *this;
    }
    BoardIterator operator++(int) {
      BoardIterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const BoardIterator &a, const BoardIterator &b) { return a.m_ptr == b.m_ptr; };
    friend bool operator!=(const BoardIterator &a, const BoardIterator &b) { return a.m_ptr != b.m_ptr; };

   private:
    pointer m_ptr;
    const Board* board_;
  };

  bool long_castle_white_{false};
  bool long_castle_black_{false};
  bool short_castle_white_{false};
  bool short_castle_black_{false};
  int en_passant_field_{-1};
  int fifty_move_rule_info_{0};

  Color to_move_{Color::WHITE};

  double intrinsic_value_;

  std::array<std::array<int, 8>, 8> board_{};
  void setPosition(const std::string &fen, const std::vector<std::string> &moves);
  explicit Board(const std::string &);
  Board(const Board &b) {
    *this = b;
  }

  const std::array<int, 8>& operator[] (int i) const { return board_[i]; }
  std::array<int, 8>& operator[] (int i) { return board_[i]; }
  int& operator()(int i) { return board_[i / 8][i % 8]; }
  const int& operator()(int i) const { return board_[i / 8][i % 8]; }
  bool operator== (const Board & b) const{ 
      for (int i = 0; i < 64; i++) {
        if (b(i) != this->operator()(i)) {
          return false;
        } 
      } 
      if (b.to_move_ != this->to_move_ ||
          b.en_passant_field_ != this->en_passant_field_) {
        return false;
      } 
          
      if (b.long_castle_black_ != this->long_castle_black_ ||
          b.long_castle_white_ != this->long_castle_white_) {
        return false;
      }

      if (b.short_castle_black_ != this->short_castle_black_ ||
          b.short_castle_white_ != this->short_castle_white_) {
        return false;
      }

      if (b.fifty_move_rule_info_ != this->fifty_move_rule_info_) {
        return false;
      }
     
      return true;  
  }

  BoardIterator begin() const;
  BoardIterator end() const;

 private:

};
