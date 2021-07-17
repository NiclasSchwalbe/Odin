#include <vector>
#include <tuple>
#include "Odin.h"
#include "Utility.h"

//adds Knight move if moveable
inline void KNIGHTMOVES::addIfMoveable(std::vector<std::tuple<int, int, Figure>>& moves, const int fromi,
                          const int fromj, const int toi, const int toj, const Board& b) {

  int opposite = b.to_move_ == Color::WHITE ? -1 : 1;
  if (!inBounds(toi, toj)) {
    return;
  }
  if (opposite * b[toi][toj] >= 0) {
    int old_field = fromi * 8 + fromj;
    int new_field = toi * 8 + toj;
    moves.push_back(std::make_tuple(old_field, new_field, FIGURES::EMPTY));
  }
  return;
}


void KNIGHTMOVES::generateAllKnightMoves(std::vector<std::tuple<int, int, Figure>>& moves,
                            const Board& board) {
  auto piece = board.to_move_ == Color::WHITE ? FIGURES::WKNIGHT : FIGURES::BKNIGHT;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j] == piece.value()) {
        KNIGHTMOVES::addIfMoveable(moves, i, j, i - 2, j + 1, board);
        KNIGHTMOVES::addIfMoveable(moves, i, j, i - 2, j - 1, board);
        KNIGHTMOVES::addIfMoveable(moves, i, j, i + 2, j + 1, board);
        KNIGHTMOVES::addIfMoveable(moves, i, j, i + 2, j - 1, board);
        KNIGHTMOVES::addIfMoveable(moves, i, j, i - 1, j + 2, board);
        KNIGHTMOVES::addIfMoveable(moves, i, j, i - 1, j - 2, board);
        KNIGHTMOVES::addIfMoveable(moves, i, j, i + 1, j + 2, board);
        KNIGHTMOVES::addIfMoveable(moves, i, j, i + 1, j - 2, board);
      }  

    }
  }
}

