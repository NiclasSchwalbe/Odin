#include "Odin.h"

template <int dX, int dY>
void generateMoves(std::vector<std::tuple<int, int, Figure>>& moves,
                   const Board& board, int x, int y) {
  int tox = x;
  int toy = y;
  for (int i = 0; i < 8 && inBounds(tox + dX, toy + dY); i++) {
    tox += dX;
    toy += dY;
    if (board[tox][toy] == EMPTY.value()) {
      moves.push_back(std::make_tuple((8 * y + x), (8 * toy + tox), EMPTY));
      continue;
    } else if (board[tox][toy] * (static_cast<int>(board.to_move_)) <=
               EMPTY.value()) {
      moves.push_back(std::make_tuple((8 * y + x), (8 * toy + tox), EMPTY));
      break;
    }
    break;
  }
}

void generateAllBishopMoves(std::vector<std::tuple<int, int, Figure>>& moves,
                            const Board& board) {
  auto piece = board.to_move_ == Color::WHITE ? WBISHOP : BBISHOP;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j] == piece.value()) {
        generateMoves<1, 1>(moves, board, i, j);
        generateMoves<1, -1>(moves, board, i, j);
        generateMoves<-1, -1>(moves, board, i, j);
        generateMoves<-1, 1>(moves, board, i, j);
      }
    }
  }
}

void generateAllRookMoves(std::vector<std::tuple<int, int, Figure>>& moves,
                          const Board& board) {
  auto piece = board.to_move_ == Color::WHITE ? WROOK : BROOK;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j] == piece.value()) {
        generateMoves<1, 0>(moves, board, i, j);
        generateMoves<0, -1>(moves, board, i, j);
        generateMoves<-1, 0>(moves, board, i, j);
        generateMoves<0, 1>(moves, board, i, j);
      }
    }
  }
}
