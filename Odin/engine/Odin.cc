//
// Created by Niclas Schwalbe on 05.04.21.
//
#include <chrono>
#include <optional>
#include <list>
#include <tuple>
#include <algorithm>

#include "Odin.h"
#include "Utility.h"

Odin::Odin() :
    start_node_(new Node(Board(OdinConstants::standardBoardFen), std::nullopt, std::nullopt, nullptr)) {
  computingThread_ = std::thread(&Odin::search, this);
  computingThread_.detach();
}

void Odin::setPosition(const std::string &fen, const std::vector<std::string> &moves) {
  start_node_ = std::make_shared<Node>(Board(fen), std::nullopt, std::nullopt, nullptr);
  start_node_->board_.setPosition(fen, moves);
}

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

double Odin::evaluatePosition(Board &board) {
  return 0.0;
}

void Odin::computeNext() {
  start_node_->evalNextPosition();
}

void Odin::setUpForCalculations() {

}

Board makeMove(const Board &b, std::tuple<int, int, Figure> t) {
  Board new_b{b};

  int temp = new_b[std::get<0>(t) / 8][std::get<0>(t) % 8];
  new_b[std::get<0>(t) / 8][std::get<0>(t) % 8] = 0;

  if (std::get<2>(t).value() == 0) {
    new_b[std::get<1>(t) / 8][std::get<1>(t) % 8] = temp;
  } else {
    new_b[std::get<1>(t) / 8][std::get<1>(t) % 8] = std::get<2>(t).value();
  }
  new_b.to_move_ = b.to_move_ == Color::WHITE ? Color::BLACK : Color::WHITE;

  return new_b;
}

void generateAllLegalMoves(std::vector<std::tuple<int, int, Figure>> &moves, const Board &board) {

  extractLegalMoves(moves, board, generateAllPawnMovesAsList);
  /*generateAllLegalKnightMoves(moves, board);
  generateAllBishopMoves(moves, board);
  generateAllRookMoves(moves,board);
  generateAllQueenMoves(moves, board);
  generateAllKingMoves(moves, board);*/

}

void generateAllMoves(std::vector<std::tuple<int, int, Figure>> &moves, const Board &board) {

  generateAllPawnMoves(moves, board);
  /*generateAllKnightMoves(moves, board);
  generateAllBishopMoves(moves, board);
  generateAllRookMoves(moves,board);
  generateAllQueenMoves(moves, board);
  generateAllKingMoves(moves, board);*/

}

void extractLegalMoves(std::vector<std::tuple<int, int, Figure>> &moves,
                       const Board &board,
                       std::function<void(std::list<std::tuple<int, int, Figure>> &, const Board &)> generator) {

  std::list<std::tuple<int, int, Figure>> new_moves;
  generator(new_moves, board);
  new_moves.erase(std::remove_if(new_moves.begin(), new_moves.end(), checkIfMoveIsIllegalDueCheck(board)),
                  new_moves.end());

  for (auto t : new_moves) {
    moves.push_back(t);
  }

}


bool checkIfMoveIsIllegalDueCheck(const Board &b, std::tuple<int, int, Figure> move) {
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

  for (auto[from, to, f] : moves) {
    if (to == field_num) {
      return true;
    }
  }

  return false;

}



