//
// Created by Niclas Schwalbe on 05.04.21.
//
#include <chrono>
#include <optional>
#include <list>
#include <tuple>
#include <algorithm>


#include "Odin.h"
#include "Utility.h"


Odin::Odin():
start_node_(new Node(Board(OdinConstants::standardBoardFen), std::nullopt, std::nullopt, nullptr)) {
    computingThread_ = std::thread(&Odin::search, this);
    computingThread_.detach();
}



void Odin::setPosition(const std::string& fen, const std::vector<std::string>& moves){
    start_node_ = std::make_shared<Node>(Board(fen), std::nullopt, std::nullopt, nullptr);
    start_node_->board_.setPosition(fen, moves);
}

void Odin::search() {
    using namespace std::chrono_literals;

    while(in_chess_){
        while(!searching_){
            std::this_thread::sleep_for(500ms);
        }
        computeNext();
        positions_calculated_++;
    }

}

double Odin::evaluatePosition(Board &board) {
    return 0.0;
}

void Odin::computeNext() {
    start_node_->evalNextPosition();
}

void Odin::setUpForCalculations() {

}

Board Odin::makeMove(const Board &b, std::tuple<int, int, Figure> t) {
   Board new_b{b};

   int temp = new_b.board_[std::get<0>(t)/8][std::get<0>(t)%8];
   new_b.board_[std::get<0>(t)/8][std::get<0>(t)%8] = 0;

   if(std::get<2>(t).value() == 0){
       new_b.board_[std::get<1>(t)/8][std::get<1>(t)%8] = temp;
   } else {
       new_b.board_[std::get<1>(t)/8][std::get<1>(t)%8] = std::get<2>(t).value();
   }

   return new_b;
}

void Odin::generateAllLegalMoves(std::vector<std::tuple<int, int, Figure>>& moves, Board& board) {

    generateAllPawnMoves(moves, board);
    /*generateAllKnightMoves(moves, board);
    generateAllBishopMoves(moves, board);
    generateAllRookMoves(moves,board);
    generateAllQueenMoves(moves, board);
    generateAllKingMoves(moves, board);*/

}

bool Odin::checkIfMoveIsIllegalDueCheck(const Board &b, std::tuple<int, int, Figure> move) {
    Board new_board = makeMove(b, move);
    return isInCheck(new_board, b.to_move_);
}

bool Odin::isInCheck(const Board& b, Color c) {
    return true;
}

void Odin::generateAllPawnMoves(std::vector<std::tuple<int, int, Figure>> &moves, Board& board) {

    std::list<std::tuple<int, int, Figure>> pawn_moves;

    int field{7};

    switch (board.to_move_) {
    case Color::BLACK:
        generateAllPawnMovesWithBlack(pawn_moves, board);
        break;
    case Color::WHITE:
        generateAllPawnMovesWithWhite(pawn_moves, board);
        break;
    }

    pawn_moves.erase(std::remove_if(pawn_moves.begin(), pawn_moves.end(), checkIfMoveIsIllegalDueCheck(board)), pawn_moves.end());

}

void Odin::generateAllPawnMovesWithWhite(std::list<std::tuple<int, int, Figure>> &pawn_moves, Board &board) {
    int field = -1;
    for(int rank{1}; rank < 7; rank++){
        for(int line{0}; line < 8; line++){

            field++;

            if(board.board_[rank][line] != WPAWN.value()){
                continue;
            }

            if(hasAnyFigure(board, rank + 1, line)){
                int new_field {field+8};
                if(rank == 6){
                    generatePawnPromotion(pawn_moves, field, new_field);
                } else {
                    pawn_moves.push_back(std::make_tuple(field, new_field, EMPTY));
                }
            }

            if(rank == 1 && hasAnyFigure(board, rank + 2, line)){
                pawn_moves.push_back(std::make_tuple(field, field+16, EMPTY));
            }

            int left = line - 1;
            int right = line + 1;

            if(0 <= left && left < 8 && hasBlackFigure(board, rank + 1, left)){
                int new_field {field+7};
                if(rank == 6){
                    generatePawnPromotion(pawn_moves, field, new_field);
                } else {
                    pawn_moves.push_back(std::make_tuple(field, new_field, EMPTY));
                }
            }
            if(0 <= right && right < 8 &&hasBlackFigure(board, rank + 1, right)){
                int new_field {field+9};
                if(rank == 6){
                    generatePawnPromotion(pawn_moves, field, new_field);
                } else {
                    pawn_moves.push_back(std::make_tuple(field, new_field, EMPTY));
                }
            }
        }
    }
}

void Odin::generateAllPawnMovesWithBlack(std::list<std::tuple<int, int, Figure>> &pawn_moves, Board &board) {
    int field = -1;
    for(int rank{1}; rank < 7; rank++){
        for(int line{0}; line < 8; line++){

            field++;

            if(board.board_[rank][line] != BPAWN.value()){
                continue;
            }

            if(hasAnyFigure(board, rank - 1, line)){
                int new_field {field-8};
                if(rank == 6){
                    generatePawnPromotion(pawn_moves, field, new_field);
                } else {
                    pawn_moves.push_back(std::make_tuple(field, new_field, EMPTY));
                }
            }

            if(rank == 1 && hasAnyFigure(board, rank - 2, line)){
                pawn_moves.push_back(std::make_tuple(field, field+16, EMPTY));
            }

            int left = line - 1;
            int right = line + 1;

            if(0 <= left && left < 8 && hasWhiteFigure(board, rank + 1, left)){
                int new_field {field-7};
                if(rank == 6){

                } else {
                    pawn_moves.push_back(std::make_tuple(field, new_field, EMPTY));
                }
            }
            if(0 <= right && right < 8 && hasWhiteFigure(board, rank + 1, right)){
                int new_field {field-9};
                if(rank == 6){
                    generatePawnPromotion(pawn_moves, field, new_field);
                } else {
                    pawn_moves.push_back(std::make_tuple(field, new_field, EMPTY));
                }
            }
        }
    }
}



