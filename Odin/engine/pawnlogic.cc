//
// Created by Niclas Schwalbe on 30.05.21.
//
#include "Odin.h"

inline void generatePawnPromotion(std::vector<std::tuple<int, int, Figure>> &seq,
                                  const int field,
                                  const int new_field) {
  seq.push_back(std::make_tuple(field, new_field, BKNIGHT));
  seq.push_back(std::make_tuple(field, new_field, BBISHOP));
  seq.push_back(std::make_tuple(field, new_field, BROOK));
  seq.push_back(std::make_tuple(field, new_field, BQUEEN));
}

void PAWNMOVES::generateAllPawnMovesWithWhite(std::vector<std::tuple<int, int, Figure>> &pawn_moves,
                                   const Board &board,
                                   int field_num) {
  int rank = field_num / 8;
  int line = field_num % 8;

  if (hasNoFigure(board, rank + 1, line)) {
    int new_field{field_num + 8};
    if (rank == 6) {
      generatePawnPromotion(pawn_moves, field_num, new_field);
    } else {
      pawn_moves.push_back(std::make_tuple(field_num, new_field, EMPTY));
    }
  }

  if (rank == 1 && hasNoFigure(board, rank + 2, line) && hasNoFigure(board, rank + 1, line)) {
    pawn_moves.push_back(std::make_tuple(field_num, field_num + 16, EMPTY));
  }

  int left = line - 1;
  int right = line + 1;

  if (0 <= left && left < 8 && hasBlackFigure(board, rank + 1, left)) {
    int new_field{field_num + 7};
    if (rank == 6) {
      generatePawnPromotion(pawn_moves, field_num, new_field);
    } else {
      pawn_moves.push_back(std::make_tuple(field_num, new_field, EMPTY));
    }
  }
  if (0 <= right && right < 8 && hasBlackFigure(board, rank + 1, right)) {
    int new_field{field_num + 9};
    if (rank == 6) {
      generatePawnPromotion(pawn_moves, field_num, new_field);
    } else {
      pawn_moves.push_back(std::make_tuple(field_num, new_field, EMPTY));
    }
  }
}

void PAWNMOVES::generateAllPawnMovesWithBlack(std::vector<std::tuple<int, int, Figure>> &pawn_moves,
                                   const Board &board,
                                   int field_num) {
  int rank = field_num / 8;
  int line = field_num % 8;

  if (hasNoFigure(board, rank - 1, line)) {
    int new_field{field_num - 8};
    if (rank == 1) {
      generatePawnPromotion(pawn_moves, field_num, new_field);
    } else {
      pawn_moves.push_back(std::make_tuple(field_num, new_field, EMPTY));
    }
  }

  if (rank == 6 && hasNoFigure(board, rank - 2, line) && hasNoFigure(board, rank - 1, line)) {
    pawn_moves.push_back(std::make_tuple(field_num, field_num - 16, EMPTY));
  }

  int left = line - 1;
  int right = line + 1;

  if (0 <= left && left < 8 && hasWhiteFigure(board, rank - 1, left)) {
    int new_field{field_num - 9};
    if (rank == 1) {
      generatePawnPromotion(pawn_moves, field_num, new_field);
    } else {
      pawn_moves.push_back(std::make_tuple(field_num, new_field, EMPTY));
    }
  }
  if (0 <= right && right < 8 && hasWhiteFigure(board, rank - 1, right)) {
    int new_field{field_num - 7};
    if (rank == 1) {
      generatePawnPromotion(pawn_moves, field_num, new_field);
    } else {
      pawn_moves.push_back(std::make_tuple(field_num, new_field, EMPTY));
    }
  }

}


void PAWNMOVES::generateAllPawnMoves(std::vector<std::tuple<int, int, Figure>> &moves, const Board &board) {

  auto pawn = board.to_move_ == Color::WHITE ? WPAWN : BPAWN;

  for(int fieldnum = 0; fieldnum < 64; fieldnum++){
    if(board(fieldnum) == pawn.value()){
      switch (board.to_move_) {
        case Color::BLACK: generateAllPawnMovesWithBlack(moves, board, fieldnum);
          break;
        case Color::WHITE: generateAllPawnMovesWithWhite(moves, board, fieldnum);
          break;
      }
    }
  }

}



