
#include "Odin.h"

/*
* Generates a king step in any direction. Where dX, dY is the directrion.
*/
template <int dX, int dY>
void generateOneSteps(const int i, const int j,
                      std::vector<std::tuple<int, int, Figure>>& moves,
                      const Board& board) {
 
  int toi = i + dX;
  int toj = j + dY;
  if (!inBounds(toi, toj)) {
    return;
  }
  if (board[toi][toj] == EMPTY.value()) {
    moves.push_back(std::make_tuple((8 * i + j), (8 * toi + toj), EMPTY));
  } else if (board[toi][toj] * (static_cast<int>(board.to_move_)) <=
             EMPTY.value()) {
    moves.push_back(std::make_tuple((8 * i + j), (8 * toi + toj), EMPTY));
  }
}
/*
* Generates all castling moves. If the king is in check after the castling, the move will be generated and can be filtered out later.
* However, if the king would be in check while crossing, the move would not be added.
*/
void generateAllCastling(int i, int j,
                         std::vector<std::tuple<int, int, Figure>>& moves,
                         const Board& board) {
  //check if King is at original position.  
  if (!((board.to_move_ == Color::BLACK && i == 7 && j == 4) ||
        (board.to_move_ == Color::WHITE && i == 0 && j == 4))) {
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
        moves.push_back(std::make_tuple(4, 5, EMPTY));
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
        moves.push_back(std::make_tuple(60, 59, EMPTY));
      }
      if (board.short_castle_black_ &&
          !checkIfMoveIsIllegalDueCheck(board, std::make_tuple(60, 61, EMPTY)) &&
          board[7][5] == EMPTY.value() && 
          board[7][6] == EMPTY.value() &&
          board[7][7] == BROOK.value()) {
        moves.push_back(std::make_tuple(60, 61, EMPTY));
      }
  }
}

void generateAllKingMoves(std::vector<std::tuple<int, int, Figure>>& moves,
                          const Board& board) {
  auto piece = board.to_move_ == Color::WHITE ? WKING : BKING;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j] == piece.value()) {
        generateOneSteps<1, 0>(i, j, moves, board);
        generateOneSteps<1, 1>(i, j, moves, board);
        generateOneSteps<1, -1>(i, j, moves, board);
        generateOneSteps<-1, 0>(i, j, moves, board);
        generateOneSteps<-1, -1>(i, j, moves, board);
        generateOneSteps<-1, 0>(i, j, moves, board);
        generateOneSteps<0, -1>(i, j, moves, board);
        generateOneSteps<0, 1>(i, j, moves, board);
        generateAllCastling(i, j, moves, board);
        break;
      }
    }
  }
}