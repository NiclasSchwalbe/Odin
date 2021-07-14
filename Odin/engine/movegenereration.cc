//
// Created by Niclas Schwalbe on 13.07.21.
//

#include "Odin.h"

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
  bool colb = Color::WHITE == board.to_move_;
  auto pawn = colb ? WPAWN : BPAWN;
  auto knight = colb ? WKNIGHT : BKNIGHT;
  auto bishop = colb ? WBISHOP : BBISHOP;
  auto rook = colb ? WROOK : BROOK;
  auto queen = colb ? WQUEEN : BQUEEN;
  auto king = colb ? WKING : BKING;

  for (int fieldnum = 0; fieldnum < 64; fieldnum++) {
    auto val = board(fieldnum);
    int y = fieldnum / 8;
    int x = fieldnum % 8;

    if (val == pawn.value()) {

      switch (board.to_move_) {
        case Color::WHITE: PAWNMOVES::generateAllPawnMovesWithWhite(moves, board, fieldnum);
                           break;
        case Color::BLACK: PAWNMOVES::generateAllPawnMovesWithBlack(moves, board, fieldnum);
      }

    } else if (val == knight.value()) {

      KNIGHTMOVES::addIfMoveable(moves, y, x, y - 2, x + 1, board);
      KNIGHTMOVES::addIfMoveable(moves, y, x, y - 2, x - 1, board);
      KNIGHTMOVES::addIfMoveable(moves, y, x, y + 2, x + 1, board);
      KNIGHTMOVES::addIfMoveable(moves, y, x, y + 2, x - 1, board);
      KNIGHTMOVES::addIfMoveable(moves, y, x, y - 1, x + 2, board);
      KNIGHTMOVES::addIfMoveable(moves, y, x, y - 1, x - 2, board);
      KNIGHTMOVES::addIfMoveable(moves, y, x, y + 1, x + 2, board);
      KNIGHTMOVES::addIfMoveable(moves, y, x, y + 1, x - 2, board);

    } else if (val == bishop.value()) {

      LONGRANGEPIECEMOVES::generateMoves<1, 1>(moves, board, y, x);
      LONGRANGEPIECEMOVES::generateMoves<1, -1>(moves, board, y, x);
      LONGRANGEPIECEMOVES::generateMoves<-1, -1>(moves, board, y, x);
      LONGRANGEPIECEMOVES::generateMoves<-1, 1>(moves, board, y, x);

    } else if (val == rook.value()) {

      LONGRANGEPIECEMOVES::generateMoves<1, 0>(moves, board, y, x);
      LONGRANGEPIECEMOVES::generateMoves<0, -1>(moves, board, y, x);
      LONGRANGEPIECEMOVES::generateMoves<-1, 0>(moves, board, y, x);
      LONGRANGEPIECEMOVES::generateMoves<0, 1>(moves, board, y, x);

    } else if (val == queen.value()) {

      LONGRANGEPIECEMOVES::generateMoves<1, 1>(moves, board, y, x);
      LONGRANGEPIECEMOVES::generateMoves<1, 0>(moves, board, y, x);
      LONGRANGEPIECEMOVES::generateMoves<1, -1>(moves, board, y, x);
      LONGRANGEPIECEMOVES::generateMoves<-1, -1>(moves, board, y, x);
      LONGRANGEPIECEMOVES::generateMoves<-1, 0>(moves, board, y, x);
      LONGRANGEPIECEMOVES::generateMoves<-1, 1>(moves, board, y, x);
      LONGRANGEPIECEMOVES::generateMoves<0, -1>(moves, board, y, x);
      LONGRANGEPIECEMOVES::generateMoves<0, 1>(moves, board, y, x);

    } else if (val == king.value()) {


      KINGMOVES::generateOneSteps<1, 0>(x, y, moves, board);
      KINGMOVES::generateOneSteps<1, 1>(x, y, moves, board);
      KINGMOVES::generateOneSteps<1, -1>(x, y, moves, board);
      KINGMOVES::generateOneSteps<-1, 0>(x, y, moves, board);
      KINGMOVES::generateOneSteps<-1, -1>(x, y, moves, board);
      KINGMOVES::generateOneSteps<-1, 1>(x, y, moves, board);
      KINGMOVES::generateOneSteps<0, -1>(x, y, moves, board);
      KINGMOVES::generateOneSteps<0, 1>(x, y, moves, board);
      KINGMOVES::generateAllCastling(x, y, moves, board);

    }
  }
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



bool hasMoveToField(const Board &board, int to_field) {
  auto opposite = board.to_move_ == Color::WHITE ? -1 : 1;
  int x = to_field % 8;
  int y = to_field / 8;
  Figure pawn{opposite, WPAWN.value()};
  Figure knight{opposite, WKNIGHT.value()};
  Figure bishop{opposite, WBISHOP.value()};
  Figure rook{opposite, WROOK.value()};
  Figure queen{opposite, WQUEEN.value()};
  Figure king{opposite, WKING.value()};

  std::vector<std::tuple<int, int, Figure>> knightmoves;
  KNIGHTMOVES::addIfMoveable(knightmoves, y, x, y - 2, x + 1, board);
  KNIGHTMOVES::addIfMoveable(knightmoves, y, x, y - 2, x - 1, board);
  KNIGHTMOVES::addIfMoveable(knightmoves, y, x, y + 2, x + 1, board);
  KNIGHTMOVES::addIfMoveable(knightmoves, y, x, y + 2, x - 1, board);
  KNIGHTMOVES::addIfMoveable(knightmoves, y, x, y - 1, x + 2, board);
  KNIGHTMOVES::addIfMoveable(knightmoves, y, x, y - 1, x - 2, board);
  KNIGHTMOVES::addIfMoveable(knightmoves, y, x, y + 1, x + 2, board);
  KNIGHTMOVES::addIfMoveable(knightmoves, y, x, y + 1, x - 2, board);

  for(auto& [from, to, E] : knightmoves){
    if(to == knight.value()){
      return true;
    }
  }

  std::vector<std::tuple<int, int, Figure>> bishopmoves;
  LONGRANGEPIECEMOVES::generateMoves<1, 1>(bishopmoves, board, y, x);
  LONGRANGEPIECEMOVES::generateMoves<1, -1>(bishopmoves, board, y, x);
  LONGRANGEPIECEMOVES::generateMoves<-1, -1>(bishopmoves, board, y, x);
  LONGRANGEPIECEMOVES::generateMoves<-1, 1>(bishopmoves, board, y, x);

  for(auto& [from, to, E] : bishopmoves){
    if(to == bishop.value() || to == queen.value()){
      return true;
    }
  }

  std::vector<std::tuple<int, int, Figure>> rookmoves;
  LONGRANGEPIECEMOVES::generateMoves<1, 0>(rookmoves, board, y, x);
  LONGRANGEPIECEMOVES::generateMoves<0, -1>(rookmoves, board, y, x);
  LONGRANGEPIECEMOVES::generateMoves<-1, 0>(rookmoves, board, y, x);
  LONGRANGEPIECEMOVES::generateMoves<0, 1>(rookmoves, board, y, x);

  for(auto& [from, to, E] : rookmoves){
    if(to == rook.value() || to == queen.value()){
      return true;
    }
  }

  std::vector<std::tuple<int, int, Figure>> kingmoves;
  KINGMOVES::generateOneSteps<1, 0>(x, y, kingmoves, board);
  KINGMOVES::generateOneSteps<1, 1>(x, y, kingmoves, board);
  KINGMOVES::generateOneSteps<1, -1>(x, y, kingmoves, board);
  KINGMOVES::generateOneSteps<-1, 0>(x, y, kingmoves, board);
  KINGMOVES::generateOneSteps<-1, -1>(x, y, kingmoves, board);
  KINGMOVES::generateOneSteps<-1, 1>(x, y, kingmoves, board);
  KINGMOVES::generateOneSteps<0, -1>(x, y, kingmoves, board);
  KINGMOVES::generateOneSteps<0, 1>(x, y, kingmoves, board);

  for(auto& [from, to, E] : kingmoves){
    if(to == king.value()){
      return true;
    }
  }

  switch (board.to_move_) {
    case Color::WHITE: return board[y+1][x-1] == pawn.value() || board[y+1][x+1] == pawn.value();
    case Color::BLACK: return board[y-1][x-1] == pawn.value() || board[y-1][x+1] == pawn.value();
  }


}

bool isCheck(const Board &b, Color color_to_be_checked) {
  std::vector<std::tuple<int, int, Figure>> moves;
  if (b.to_move_ == color_to_be_checked) {
    Board passTurn{b};
    passTurn.to_move_ =
        b.to_move_ == Color::WHITE ? Color::BLACK : Color::WHITE;
    return isCheck(passTurn, color_to_be_checked);
  } else {
    //TODO:: Make smarter
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
}

bool isCheckMate(const Board &board) {
  if (!isCheck(board, board.to_move_)) {
    return false;
  }

  //smarter way
  if (board.is_end_position.has_value()) {
    return board.is_end_position.value();
  }  
  //else Bruteforce
  std::vector<std::tuple<int, int, Figure>> vec{};
  generateAllLegalMoves(vec, board);
  return vec.size() == 0;
}

bool isStaleMate(const Board &board) {
  if (isCheck(board, board.to_move_)) {
    return false;
  }
  //smarter way
  if (board.is_end_position.has_value()) {
    return board.is_end_position.value();
  }  
  //else Brutforce
  std::vector<std::tuple<int, int, Figure>> vec{};
  generateAllLegalMoves(vec, board);
  return vec.size() == 0;
}
