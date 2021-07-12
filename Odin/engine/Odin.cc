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

Board makeMove(const Board &old_b, std::tuple<int, int, Figure> t) {
  // copy Board
  Board new_b{old_b};
  const auto from_field{std::get<0>(t)};
  const auto to_field{std::get<1>(t)};
  const auto promotion{std::get<2>(t)};

  // value of the piece to be moved.
  int temp = new_b(from_field);
  new_b(from_field) = EMPTY.value();

  // is the move an en passant?
  auto pawn = old_b.to_move_ == Color::WHITE ? WPAWN : BPAWN;
  if (old_b(from_field) == pawn.value() &&
      old_b.en_passant_field_ == to_field) {
    if (old_b.to_move_ == Color::WHITE) {
      new_b(to_field - 8) = EMPTY.value();
    } else {
      new_b(to_field + 8) = EMPTY.value();
    }
  }

  // is it pawn move with 2 steps, if yes set en_passant
  if (old_b(from_field) == pawn.value() && abs(from_field - to_field) == 16) {
    new_b.en_passant_field_ =
        new_b.to_move_ == Color::WHITE ? from_field + 8 : from_field - 8;
  } else {
    new_b.en_passant_field_ = -1;
  }

  // if move is castle, then set rook and remove castling rights
  auto king = old_b.to_move_ == Color::WHITE ? WKING : BKING;
  if (old_b(from_field) == king.value() && abs(from_field - to_field) == 2) {
    if (to_field % 8 < 5) {
      new_b((from_field / 8) * 8) = EMPTY.value();
      new_b((from_field / 8) * 8 + 3) = king.color() * WROOK.value();
    } else {
      new_b((from_field / 8) * 8 + 7) = EMPTY.value();
      new_b((from_field / 8) * 8 + 5) = king.color() * WROOK.value();
    }
    if (old_b.to_move_ == Color::WHITE) {
      new_b.long_castle_white_ = false;
      new_b.short_castle_white_ = false;
    } else {
      new_b.long_castle_black_ = false;
      new_b.short_castle_black_ = false;
    }
  }

  // Set new position, promote pawn if necessary
  if (promotion.value() == 0) {
    new_b(to_field) = temp;
  } else {
    new_b(to_field) = promotion.value();
  }

  // change color
  new_b.to_move_ = old_b.to_move_ == Color::WHITE ? Color::BLACK : Color::WHITE;

  return new_b;
}

void generateAllLegalMoves(std::vector<std::tuple<int, int, Figure>> &moves,
                           const Board &board) {
  extractLegalMoves(moves, board, generateAllMoves);
}

void generateAllMoves(std::vector<std::tuple<int, int, Figure>> &moves,
                      const Board &board) {
  generateAllPawnMoves(moves, board);
  generateAllKnightMoves(moves, board);
  generateAllBishopMoves(moves, board);
  generateAllRookMoves(moves, board);
  generateAllQueenMoves(moves, board);
  generateAllKingMoves(moves, board);
}

void extractLegalMoves(
    std::vector<std::tuple<int, int, Figure>> &moves, const Board &board,
    std::function<void(std::vector<std::tuple<int, int, Figure>> &,
                       const Board &)>
        generator) {
  std::vector<std::tuple<int, int, Figure>> new_moves;
  generator(new_moves, board);

  for (auto &t : new_moves) {
    if (!checkIfMoveIsIllegalDueCheck(board, t)) {
      moves.push_back(t);
    }
  }
}

bool checkIfMoveIsIllegalDueCheck(const Board &b,
                                  std::tuple<int, int, Figure> move) {
  Board new_board = makeMove(b, move);
  return isCheck(new_board, b.to_move_);
}

bool isCheck(const Board &b, Color color_to_be_checked) {
  std::vector<std::tuple<int, int, Figure>> moves;
  if (b.to_move_ == color_to_be_checked) {
    Board passTurn{b};
    passTurn.to_move_ =
        b.to_move_ == Color::WHITE ? Color::BLACK : Color::WHITE;
    return isCheck(passTurn, color_to_be_checked);
  } else {
    generateAllMoves(moves, b);

    int field_num{0};

    auto figure = b.to_move_ == Color::WHITE ? BKING : WKING;

    for (auto p : b) {
      if (p == figure.value()) {
        break;
      }
      field_num++;
    }

    for (auto [from, to, f] : moves) {
      if (to == field_num) {
        return true;
      }
    }

    return false;
  }
}

bool isCheckMate(const Board &board) {
  if (!isCheck(board, board.to_move_)) {
    return false;
  }
  std::vector<std::tuple<int, int, Figure>> vec{};
  generateAllLegalMoves(vec, board);
  return vec.size() == 0;
}

bool isStaleMate(const Board &board) {
  if (isCheck(board, board.to_move_)) {
    return false;
  }
  std::vector<std::tuple<int, int, Figure>> vec{};
  generateAllLegalMoves(vec, board);
  return vec.size() == 0;
}
