//
// Created by Niclas Schwalbe on 05.04.21.
//

#pragma once
#include <list>
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <functional>
#include "Board.h"
#include "Node.h"
#include "Utility.h"

namespace OdinConstants {
    static const std::string standardBoardFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    static const double cpuct = 2.0f;
}

class Node;

class Odin {
public:
    Odin();

    long positions_calculated_{0};
    std::shared_ptr<Node> start_node_;

    inline void searchOn() {
        searching_ = true;
        setUpForCalculations();
    }


    inline void searchOff() {
        searching_ = false;
    }

    void search();
    void setPosition(const std::string& fen, const std::vector<std::string>& moves);
    inline void setPosition(const Board& board) { 
        start_node_ =
          std::make_shared<Node>(board,std::nullopt, std::nullopt, nullptr);
      positions_calculated_ = 0;
    }
    static double evaluatePosition(const Board &board);

    std::tuple<int, int, Figure> bestMove() const;


private:
    std::thread computingThread_{};
    bool searching_{false};
    bool in_chess_{true};

    void setUpForCalculations();
    void computeNext();


};

/* //////////////////////////////////////////////////
 * Move Generation
 *///////////////////////////////////////////////////

Board makeMove(const Board &b, std::tuple<int, int, Figure>);
/*
 * Checks if king could be "captured" in the next move and would therefore be in
 * check.
 */
bool isCheck(const Board &board, Color to_be_checked);

void generateAllMoves(std::vector<std::tuple<int, int, Figure>>& moves, const Board& board);
void generateAllLegalMoves(std::vector<std::tuple<int, int, Figure>> &moves, const Board& board);
/*
 * filters all Moves which would be illegal, because color would check itself or
 * not escape a check
 */
void extractLegalMoves(std::vector<std::tuple<int, int, Figure>>& moves, const Board & board,
                       std::function<void(std::vector<std::tuple<int, int, Figure>>&, const Board &)> generator);

namespace PAWNMOVES {
void generateAllPawnMovesWithWhite(std::vector<std::tuple<int, int, Figure>> &pawn_moves, const Board &board, int field_num);
void generateAllPawnMovesWithBlack(std::vector<std::tuple<int, int, Figure>> &pawn_moves, const Board &board, int field_num);
void generateAllPawnMoves(std::vector<std::tuple<int, int, Figure>>& , const Board& board);
}
namespace KNIGHTMOVES {
void addIfMoveable(std::vector<std::tuple<int, int, Figure>>& moves, const int fromi, const int fromj, const int toi, const int toj, const Board& b);
void generateAllKnightMoves(std::vector<std::tuple<int, int, Figure>> &, const Board &board);
}
namespace LONGRANGEPIECEMOVES {
template <int dX, int dY> void generateMoves(std::vector<std::tuple<int, int, Figure>>& moves, const Board& board, const int y, const int x);
void generateAllBishopMoves(std::vector<std::tuple<int, int, Figure>>& , const Board& board);
void generateAllRookMoves(std::vector<std::tuple<int, int, Figure>>& , const Board& board);
void generateAllQueenMoves(std::vector<std::tuple<int, int, Figure>>&, const Board& board);
}

namespace KINGMOVES {
/*
* Generates a king step in any direction. Where dX, dY is the directrion.
 * For some weird reason, I do not fully understand: generateOneSteps needs to be header defined.
*/
template<int dX, int dY>
void generateOneSteps(const int i, const int j,
                                 std::vector<std::tuple<int, int, Figure>> &moves,
                                 const Board &board) {

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
void generateAllCastling(int i, int j, std::vector<std::tuple<int, int, Figure>> &moves, const Board &board);
void generateAllKingMoves(std::vector<std::tuple<int, int, Figure>>&, const Board& board);
}

inline bool hasNoFigure(const Board& board, const int rank, const int line) {
  if (!inBounds(rank, line)) {
    return false;
  }  
  return board[rank][line] == 0;
}

inline bool hasBlackFigure(const Board& board, const int rank, const int line) {
  if (!inBounds(rank, line)) {
    return false;
  }
  return board[rank][line] < 0;
}

inline bool hasWhiteFigure(const Board& board, const int rank, const int line) {
  if (!inBounds(rank, line)) {
     return false;
  }
  return board[rank][line] > 0;
}

/*
 * This method checks if the given move, does not make the king takeable, ensures the King is still protected.
 */
bool checkIfMoveIsIllegalDueCheck(const Board &b, std::tuple<int, int, Figure> move);

/*
 * This currys checkIfMoveIsIllegalDueCheck(const Board &b, std::tuple<int, int, Figure> move);
 */
inline std::function<bool(std::tuple<int, int, Figure>)> checkIfMoveIsIllegalDueCheck(const Board& b){
  return [b](std::tuple<int, int, Figure> move) -> bool {
    return checkIfMoveIsIllegalDueCheck(b, move);
  };
}

bool isCheckMate(const Board& b);
bool isStaleMate(const Board& b);
