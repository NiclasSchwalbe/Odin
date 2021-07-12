//
// Created by Niclas Schwalbe on 06.04.21.
//
#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>

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

    BoardIterator(pointer ptr, const Board *b) : m_ptr(ptr), board_{b} {}

    reference operator*() const { return (*board_)(m_ptr); }
    
    
    BoardIterator &operator++() {
      m_ptr++;
      return *this;
    }
    BoardIterator operator++(int) {
      BoardIterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const BoardIterator &a, const BoardIterator &b) {
      return a.m_ptr == b.m_ptr;
    };
    friend bool operator!=(const BoardIterator &a, const BoardIterator &b) {
      return a.m_ptr != b.m_ptr;
    };

   private:
    pointer m_ptr;
    const Board *board_;
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
  void setPosition(const std::string &fen,
                   const std::vector<std::string> &moves);
  void reeval();
  explicit Board(const std::string &);
  Board(const Board &b);

  const std::array<int, 8> &operator[](int i) const { return board_[i]; }
  std::array<int, 8> &operator[](int i) { return board_[i]; }
  int &operator()(int i) { return board_[i / 8][i % 8]; }
  const int &operator()(int i) const { return board_[i / 8][i % 8]; }

  
  bool operator==(const Board &b) const;

  //allows to print a Board
  friend std::ostream &operator<<(std::ostream &os, Board const& b) {
    std::string output{}; 
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (b.board_[7 - i][j] >= 0) {
          output += ' '; 
        }    
        output += (std::to_string(b.board_[7 - i][j])) + '|';
      }
      output += "\n";
    }
    return (os << output) << std::endl;
  }

  BoardIterator begin() const;
  BoardIterator end() const;

 private:
};
