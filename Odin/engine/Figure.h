//
// Created by Niclas Schwalbe on 06.04.21.
//
#pragma once

enum class Color;

/*
* Figure is a constexpr. This ensures evaluations, as fast as possible.
* It just represents a piece on the board.
* NOTE:
* value() does not return something akin to worth, but the representation value on the board.
*/
class Figure {
 public:
  constexpr Figure(int val, int color) : val_{val}, col_{color} {}

  constexpr Figure(int val, Color color)
      : val_{val}, col_{static_cast<int>(color)} {}

  constexpr Figure(const Figure&& f) : val_{f.val_}, col_{f.col_} {}

  constexpr Figure(const Figure& f) : val_{f.val_}, col_{f.col_} {}

  constexpr void operator=(const Figure&& f) {
    val_ = f.val_;
    col_ = f.col_;
  }

  constexpr void operator=(const Figure& f) {
    val_ = f.val_;
    col_ = f.col_;
  }

  constexpr int value() const { return (col_ * val_); }
  constexpr int color() const { return col_; }

 private:
  int val_;
  int col_;
};

