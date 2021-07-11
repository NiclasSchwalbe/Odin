//
// Created by Niclas Schwalbe on 05.04.21.
//
#include "Odin.h"

#include <algorithm>
#include <chrono>
#include <list>
#include <optional>
#include <tuple>
#include <cstdlib>

#include "Utility.h"

Odin::Odin()
    : start_node_(new Node(Board(OdinConstants::standardBoardFen), std::nullopt,
                           std::nullopt, nullptr)) {
  computingThread_ = std::thread(&Odin::search, this);
  computingThread_.detach();
}

// prepares for new evaluatiuons
void Odin::setPosition(const std::string &fen,
                       const std::vector<std::string> &moves) {
  start_node_ =
      std::make_shared<Node>(Board(fen), std::nullopt, std::nullopt, nullptr);
  start_node_->board_.setPosition(fen, moves);
}

// computes next best move
void Odin::search() {
  using namespace std::chrono_literals;

  while (in_chess_) {
    while (!searching_) {
      std::this_thread::sleep_for(500ms);
    }
    computeNext();
    positions_calculated_++;
  }
}

// calculates intrisic value of a position
double Odin::evaluatePosition(Board &board) { return 0.0; }

// computes new field and feeds it up
void Odin::computeNext() { start_node_->evalNextPosition(); }

void Odin::setUpForCalculations() {}

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
  if (old_b(from_field) == pawn.value() && old_b.en_passant_field_ == to_field) {
      if(old_b.to_move_ == Color::WHITE){
        new_b(to_field - 8) = EMPTY.value();
      } else {
        new_b(to_field + 8) = EMPTY.value();
      }
  }

  // is it pawn move with 2 steps, if yes set en_passant
  if (old_b(from_field) == pawn.value() &&
      abs(from_field - to_field) == 16) {
    new_b.en_passant_field_ = new_b.to_move_ == Color::WHITE
                                  ? from_field + 8
                                  : to_field - 8;
  } else {
    new_b.en_passant_field_ = -1;
  }

  //if move is castle, then set rook
  auto king = old_b.to_move_ == Color::WHITE ? WKING : BKING;
  if (old_b(from_field) == king.value() && abs(from_field - to_field) == 2) {
    if(from_field%8 < 5){
      new_b((from_field/8)*8 + 4) = king.color()*WROOK.value();
    } else {
      new_b((from_field/8)*8 + 6) = king.color()*WROOK.value();
    }
  }

  //Set new position, promote pawn if necessary
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
  new_moves.erase(std::remove_if(new_moves.begin(), new_moves.end(),
                                 checkIfMoveIsIllegalDueCheck(board)),
                  new_moves.end());

  for (auto &t : new_moves) {
    if (!checkIfMoveIsIllegalDueCheck(board, t)) {
      moves.push_back(t);
    }
  }
}

bool checkIfMoveIsIllegalDueCheck(const Board &b,
                                  std::tuple<int, int, Figure> move) {
  Board new_board = makeMove(b, move);
  return isInCheck(new_board);
}

bool isInCheck(const Board &b) {
  std::vector<std::tuple<int, int, Figure>> moves;
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
