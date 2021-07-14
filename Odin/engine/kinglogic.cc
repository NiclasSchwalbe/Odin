#include "Odin.h"


/*
* Generates all castling moves. If the king is in check after the castling, the move will be generated and can be filtered out later.
* However, if the king would be in check while crossing, the move would not be added.
*/
void KINGMOVES::generateAllCastling(int j, int i,
                         std::vector<std::tuple<int, int, Figure>> &moves,
                         const Board &board) {
  //check if King is at original position.
  if (!((board.to_move_ == Color::BLACK && i == 7 && j == 4) || (board.to_move_ == Color::WHITE && i == 0 && j == 4))) {
    return;
  }

  switch (board.to_move_) {
    /*
    * If the side still has castling sides, the space between king and rook is free, the rook still is at original position
    * and the king could not be captured while moving to its desired position.
    */


    //case WHITE
    case Color::WHITE:
      if (board.long_castle_white_ &&
          !checkIfMoveIsIllegalDueCheck(board, std::make_tuple(4, 3, EMPTY)) &&
          board[0][1] == EMPTY.value() &&
          board[0][2] == EMPTY.value() &&
          board[0][3] == EMPTY.value() &&
          board[0][0] == WROOK.value()) {
        moves.push_back(std::make_tuple(4, 2, EMPTY));
      }
      if (board.short_castle_white_ &&
          !checkIfMoveIsIllegalDueCheck(board, std::make_tuple(4, 5, EMPTY)) &&
          board[0][5] == EMPTY.value() &&
          board[0][6] == EMPTY.value() &&
          board[0][7] == WROOK.value()) {
        moves.push_back(std::make_tuple(4, 6, EMPTY));
      }
      break;
      //case BLACK
    default:
      if (board.long_castle_black_ &&
          !checkIfMoveIsIllegalDueCheck(board, std::make_tuple(60, 59, EMPTY)) &&
          board[7][1] == EMPTY.value() &&
          board[7][2] == EMPTY.value() &&
          board[7][3] == EMPTY.value() &&
          board[7][0] == BROOK.value()) {
        moves.push_back(std::make_tuple(60, 58, EMPTY));
      }
      if (board.short_castle_black_ &&
          !checkIfMoveIsIllegalDueCheck(board, std::make_tuple(60, 61, EMPTY)) &&
          board[7][5] == EMPTY.value() &&
          board[7][6] == EMPTY.value() &&
          board[7][7] == BROOK.value()) {
        moves.push_back(std::make_tuple(60, 62, EMPTY));
      }
  }
}


void KINGMOVES::generateAllKingMoves(std::vector<std::tuple<int, int, Figure>> &moves,
                          const Board &board) {
  auto piece = board.to_move_ == Color::WHITE ? WKING : BKING;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j] == piece.value()) {
        KINGMOVES::generateOneSteps<1, 0>(j, i, moves, board);
        KINGMOVES::generateOneSteps<1, 1>(j, i, moves, board);
        KINGMOVES::generateOneSteps<1, -1>(j, i, moves, board);
        KINGMOVES::generateOneSteps<-1, 0>(j, i, moves, board);
        KINGMOVES::generateOneSteps<-1, -1>(j, i, moves, board);
        KINGMOVES::generateOneSteps<-1, 1>(j, i, moves, board);
        KINGMOVES::generateOneSteps<0, -1>(j, i, moves, board);
        KINGMOVES::generateOneSteps<0, 1>(j, i, moves, board);
        KINGMOVES::generateAllCastling(j, i, moves, board);
        return;
      }
    }
  }
}