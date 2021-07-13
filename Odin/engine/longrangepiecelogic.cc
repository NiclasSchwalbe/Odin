#include "Odin.h"

/*
* Generates long range piece moves. Where dX, dY is the direction the piece is going to.
* A rook and a rook need 4 directions
* A queen needs 6 directions
*/
template <int dX, int dY>
void LONGRANGEPIECEMOVES::generateMoves(std::vector<std::tuple<int, int, Figure>>& moves,
                   const Board& board, const int y, const int x) {
  int tox = x;
  int toy = y;
  for (int i = 0; i < 8 && inBounds(tox + dX, toy + dY); i++) {
    tox += dX;
    toy += dY;
    if (board[toy][tox] == EMPTY.value()) {
      moves.push_back(std::make_tuple((8 * y + x), (8 * toy + tox), EMPTY));
      continue;
    } else if (board[toy][tox] * (static_cast<int>(board.to_move_)) <=
        EMPTY.value()) {
      moves.push_back(std::make_tuple((8 * y + x), (8 * toy + tox), EMPTY));
      break;
    }
    break;
  }
}



void LONGRANGEPIECEMOVES::generateAllBishopMoves(std::vector<std::tuple<int, int, Figure>>& moves,
                            const Board& board) {
  auto piece = board.to_move_ == Color::WHITE ? WBISHOP : BBISHOP;
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (board[y][x] == piece.value()) {
        LONGRANGEPIECEMOVES::generateMoves<1, 1>(moves, board, y, x);
        LONGRANGEPIECEMOVES::generateMoves<1, -1>(moves, board, y, x);
        LONGRANGEPIECEMOVES::generateMoves<-1, -1>(moves, board, y, x);
        LONGRANGEPIECEMOVES::generateMoves<-1, 1>(moves, board, y, x);
      }
    }
  }
}

void LONGRANGEPIECEMOVES::generateAllRookMoves(std::vector<std::tuple<int, int, Figure>>& moves,
                          const Board& board) {
  auto piece = board.to_move_ == Color::WHITE ? WROOK : BROOK;
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (board[y][x] == piece.value()) {
        LONGRANGEPIECEMOVES::generateMoves<1, 0>(moves, board, y, x);
        LONGRANGEPIECEMOVES::generateMoves<0, -1>(moves, board, y, x);
        LONGRANGEPIECEMOVES::generateMoves<-1, 0>(moves, board, y, x);
        LONGRANGEPIECEMOVES::generateMoves<0, 1>(moves, board, y, x);
      }
    }
  }
}

void LONGRANGEPIECEMOVES::generateAllQueenMoves(std::vector<std::tuple<int, int, Figure>>& moves,
                          const Board& board) {
  auto piece = board.to_move_ == Color::WHITE ? WQUEEN : BQUEEN;
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (board[y][x] == piece.value()) {
        LONGRANGEPIECEMOVES::generateMoves<1, 1>(moves, board, y, x);
        LONGRANGEPIECEMOVES::generateMoves<1, -1>(moves, board, y, x);
        LONGRANGEPIECEMOVES::generateMoves<-1, -1>(moves, board, y, x);
        LONGRANGEPIECEMOVES::generateMoves<-1, 1>(moves, board, y, x);
        LONGRANGEPIECEMOVES::generateMoves<1, 0>(moves, board, y, x);
        LONGRANGEPIECEMOVES::generateMoves<0, -1>(moves, board, y, x);
        LONGRANGEPIECEMOVES::generateMoves<-1, 0>(moves, board, y, x);
        LONGRANGEPIECEMOVES::generateMoves<0, 1>(moves, board, y, x);
      }
    }
  }
}
