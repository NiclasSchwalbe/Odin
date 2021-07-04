#include <vector>
#include <tuple>
#include "Odin.h"

//adds Knight move if moveable
inline void addIfMoveable(std::vector<std::tuple<int, int, Figure>>& moves, int fromi,
    int fromj, int toi, int toj, const Board& b) {

    int opposite = b.to_move_ == Color::WHITE ? -1 : 1; 
    if (inBounds(toi, toj)) {
    return;
    }
    if (opposite * b[toi][toj] >= 0) {
      int old_field = fromi * 8 + fromj;
      int new_field = toi * 8 + toj;
      moves.push_back(std::make_tuple(old_field, new_field, EMPTY)); 
    }
    return;
}

void generateAllKnightMoves(std::vector<std::tuple<int, int, Figure>>& moves,
                            const Board& board) {
  auto piece = board.to_move_ == Color::WHITE ? WKNIGHT : BKNIGHT;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j] == piece.value()) {
        addIfMoveable(moves, i, j, i - 2, j + 1, board);
        addIfMoveable(moves, i, j, i - 2, j - 1, board);
        addIfMoveable(moves, i, j, i + 2, j + 1, board);
        addIfMoveable(moves, i, j, i + 2, j - 1, board);
        addIfMoveable(moves, i, j, i - 1, j + 2, board);
        addIfMoveable(moves, i, j, i - 1, j - 2, board);
        addIfMoveable(moves, i, j, i + 1, j + 2, board);
        addIfMoveable(moves, i, j, i + 1, j - 2, board);
      }  

    }
  }
}

