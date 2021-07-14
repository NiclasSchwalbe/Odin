//
// Created by Niclas Schwalbe on 05.04.21.
//
#include "Odin.h"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <list>
#include <optional>
#include <tuple>

#include "Utility.h"

Odin::Odin()
    : start_node_(new Node(Board(OdinConstants::standardBoardFen), std::nullopt,
                           std::nullopt, nullptr)) {
  /*
  computingThread_ = std::thread(&Odin::search, this);
  computingThread_.detach();
  */
}

// prepares for new evaluatiuons
void Odin::setPosition(const std::string &fen,
                       const std::vector<std::string> &moves) {
  start_node_ =
      std::make_shared<Node>(Board(fen), std::nullopt, std::nullopt, nullptr);
  start_node_->board_.setPosition(fen, moves);
  positions_calculated_ = 0;
}

// computes next best move
void Odin::search() {
  using namespace std::chrono_literals;

  while (in_chess_ && positions_calculated_++ < 10000) {
    while (!searching_) {
      std::this_thread::sleep_for(500ms);
    }
    computeNext();
    std::cout << positions_calculated_ << "\r";
  }
}

// calculates intrisic value of a position
double Odin::evaluatePosition(const Board &board) {
  double val{0};

  if (isCheckMate(board)) {
    return board.to_move_ == Color::WHITE ? -100 : 100;
  }

  if (isStaleMate(board)) {
    return 0;
  }

  for (int i{0}; i < 64; i++) {
    switch (board(i)) {
      case EMPTY.value():
        continue;
      case WPAWN.value():
        val += 1;
        break;
      case WKNIGHT.value():
        val += 3.0;
        break;
      case WBISHOP.value():
        val += 3.15;
        break;
      case WROOK.value():
        val += 5;
        break;
      case WQUEEN.value():
        val += 9;
        break;
      case BPAWN.value():
        val -= 1;
        break;
      case BKNIGHT.value():
        val -= 3.0;
        break;
      case BBISHOP.value():
        val -= 3.15;
        break;
      case BROOK.value():
        val -= 5;
        break;
      case BQUEEN.value():
        val -= 9;
        break;
    }
  }
  return val;
}

// computes new field and feeds it up
void Odin::computeNext() { start_node_->evalNextPosition(); }

void Odin::setUpForCalculations() {}

std::tuple<int, int, Figure> Odin::bestMove() const {
  if (start_node_->moves_.size() == 0) {
    return std::make_tuple(-1, -1, EMPTY);
  }
  auto best_value{start_node_->moves_[0].ptr->value()};
  std::tuple<int, int, Figure> move = start_node_->moves_[0].move;
  switch (start_node_->board_.to_move_) {
    case Color::WHITE:
      for (const auto &link : start_node_->moves_) {
        if (link.ptr->value() > best_value) {
          move = link.move;
          best_value = link.ptr->value();
        }
        continue;
      }
      break;
    case Color::BLACK:
      for (const auto &link : start_node_->moves_) {
        if (link.ptr->value() < best_value) {
          move = link.move;
          best_value = link.ptr->value();
        }
        continue;
      }
  }
  return move;
}



