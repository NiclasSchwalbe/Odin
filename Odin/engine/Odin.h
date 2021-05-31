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
    static double evaluatePosition(Board &board);


private:
    std::thread computingThread_{};
    bool searching_{false};
    bool in_chess_{true};

    void setUpForCalculations();
    void computeNext();


};

Board makeMove(const Board &b, std::tuple<int, int, Figure>);

bool isInCheck(const Board &board);

void generateAllMoves(std::vector<std::tuple<int, int, Figure>>& moves, const Board& board);
void generateAllLegalMoves(std::vector<std::tuple<int, int, Figure>> &moves, const Board& board);
void extractLegalMoves(std::vector<std::tuple<int, int, Figure>>& moves, const Board & board,
                       std::function<void(std::list<std::tuple<int, int, Figure>>&, const Board &)> generator);

/*
 * AsList Suffix is necessary, otherwise it will not be understood by std::function.... weird template stuff
 */
void generateAllPawnMovesAsList(std::list<std::tuple<int, int, Figure>>& pawn_moves, const Board & board);
void generateAllPawnMoves(std::vector<std::tuple<int, int, Figure>>& , const Board& board);
void generateAllKnightMoves(std::vector<std::tuple<int, int, Figure>>& , const Board& board);
void generateAllBishopMoves(std::vector<std::tuple<int, int, Figure>>& , const Board& board);
void generateAllRookMoves(std::vector<std::tuple<int, int, Figure>>& , const Board& board);
void generateAllQueenMoves(std::vector<std::tuple<int, int, Figure>>&, const Board& board);
void generateAllKingMoves(std::vector<std::tuple<int, int, Figure>>&, const Board& board);

void generateAllPawnMovesWithWhite(std::list<std::tuple<int, int, Figure>> &pawn_moves, const Board & board);
void generateAllPawnMovesWithBlack(std::list<std::tuple<int, int, Figure>> &pawn_moves, const Board & board);

inline bool hasNoFigure(const Board& board, const int rank, const int line) {
  if (rank < 0 || rank >= 8 || line < 0 || line >= 8) {
    return false;
  }  
  return board[rank][line] == 0;
}

inline bool hasBlackFigure(const Board& board, const int rank, const int line) {
  if (rank < 0 || rank >= 8 || line < 0 || line >= 8) {
    return false;
  }
  return board[rank][line] < 0;
}

inline bool hasWhiteFigure(const Board& board, const int rank, const int line) {
  if (rank < 0 || rank >= 8 || line < 0 || line >= 8) {
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

inline void generatePawnPromotion(std::list<std::tuple<int, int, Figure>> &seq, int field, int new_field) {
  seq.push_back(std::make_tuple(field, new_field, BKNIGHT));
  seq.push_back(std::make_tuple(field, new_field, BBISHOP));
  seq.push_back(std::make_tuple(field, new_field, BROOK));
  seq.push_back(std::make_tuple(field, new_field, BQUEEN));
}

