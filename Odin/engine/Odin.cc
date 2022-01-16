//
// Created by Niclas Schwalbe on 05.04.21.
//

#include <chrono>
#include <cstdlib>
#include <optional>
#include <tuple>
#include <array>
#include "Utility.h"
#include "Odin.h"

#ifdef _MSC_VER 
//does not compile otherwise, template things...
#include "Utility.cc"
#endif


Odin::Odin()
    : start_node_(new Node(Board(OdinConstants::standardBoardFen), std::nullopt,
                           std::nullopt, nullptr)) {
  /*
  computingThread_ = std::thread(&Odin::search, this);
  computingThread_.detach();
  */
}

// prepares for new evaluatiuons
void Odin::setPosition(const std::string &fen,
                       const std::vector<std::string> &moves) {
  start_node_ =
      std::make_shared<Node>(Board(fen), std::nullopt, std::nullopt, nullptr);
  start_node_->board_.setPosition(fen, moves);
  positions_calculated_ = 0;
}

// computes next best move
void Odin::search() {
    
  using namespace std::chrono_literals;
  auto start = std::chrono::system_clock::now();
  auto pos_before = 0;
  while (in_chess_ && positions_calculated_++ < OdinConstants::max_positions_) {
    while (!searching_) {
      std::this_thread::sleep_for(500ms);
    }
    computeNext();
    if (positions_calculated_ % OdinConstants::max_positions_ == 0) {
      auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - start);
      std::cout << 1000000.0f * (positions_calculated_ - pos_before) / (elapsed.count()) << " kN/s" << std::endl;
      pos_before = positions_calculated_;
      start = std::chrono::system_clock::now();
    }
  }
}

double fast_sig(double x) {
  return 0.5* (x / (1 + std::abs(x)) + 1);
}
// calculates intrisic value of a position
double Odin::evaluatePosition(const Board &board) {
  double val{0};

  if (isCheckMate(board)) {
    return board.to_move_ == Color::WHITE ? 1 : 0;
  }

  if (isStaleMate(board)) {
    return 0.5;
  }

  for (int i{0}; i < 64; i++) {
    switch (board(i)) {
      using namespace FIGURES;
      case FIGURES::EMPTY.value():continue;
      case FIGURES::WPAWN.value(): {
        constexpr int piece = WPAWN.value();
        val += (PIECEEVALUATONVALUES::pieceEvaluationValue(piece) + PIECEEVALUATONTABLES::TABLE<piece>[i]);

      }
        break;
      case FIGURES::WKNIGHT.value(): {
        constexpr int piece = WKNIGHT.value();
        val += (PIECEEVALUATONVALUES::pieceEvaluationValue(piece) + PIECEEVALUATONTABLES::TABLE<piece>[i]);
      }
        break;
      case FIGURES::WBISHOP.value(): {
        constexpr int piece = WBISHOP.value();
        val += (PIECEEVALUATONVALUES::pieceEvaluationValue(piece) + PIECEEVALUATONTABLES::TABLE<piece>[i]);
      }
        break;
      case FIGURES::WROOK.value(): {
        constexpr int piece = WROOK.value();
        val += (PIECEEVALUATONVALUES::pieceEvaluationValue(piece) + PIECEEVALUATONTABLES::TABLE<piece>[i]);
      }
        break;
      case FIGURES::WQUEEN.value(): {
        constexpr int piece = WQUEEN.value();
        val += (PIECEEVALUATONVALUES::pieceEvaluationValue(piece) + PIECEEVALUATONTABLES::TABLE<piece>[i]);
      }
        break;
      case FIGURES::BPAWN.value(): {
        constexpr int piece = WPAWN.value();
        val -= (PIECEEVALUATONVALUES::pieceEvaluationValue(piece) + PIECEEVALUATONTABLES::TABLE<piece>[(7 - (i/8))*8 + i%8]);

      }
        break;
      case FIGURES::BKNIGHT.value(): {
        constexpr int piece = WKNIGHT.value();
        val -= (PIECEEVALUATONVALUES::pieceEvaluationValue(piece) + PIECEEVALUATONTABLES::TABLE<piece>[(7 - (i/8))*8 + i%8]);
      }
        break;
      case FIGURES::BBISHOP.value(): {
        constexpr int piece = WBISHOP.value();
        val -= (PIECEEVALUATONVALUES::pieceEvaluationValue(piece) +
                PIECEEVALUATONTABLES::TABLE<piece>[(7 - (i / 8)) * 8 + i % 8]);
      }
        break;
      case FIGURES::BROOK.value(): {
        constexpr int piece = WROOK.value();
        val -= (PIECEEVALUATONVALUES::pieceEvaluationValue(piece) +
                PIECEEVALUATONTABLES::TABLE<piece>[(7 - (i / 8)) * 8 + i % 8]);
      }
        break;
      case FIGURES::BQUEEN.value(): {
        constexpr int piece = WQUEEN.value();
        val -= (PIECEEVALUATONVALUES::pieceEvaluationValue(piece) +
                PIECEEVALUATONTABLES::TABLE<piece>[(7 - (i / 8)) * 8 + i % 8]);
      }
        break;
    }
  }
  return fast_sig(val/100);
}

// computes new field and feeds it up
void Odin::computeNext() { start_node_->evalNextPosition(); }

void Odin::setUpForCalculations() {}

std::tuple<int, int, Figure> Odin::bestMove() const {
  //if there cannot be made any move: return illegal tupel  
  if (start_node_->moves_.size() == 0) {
    return std::make_tuple(-1, -1, FIGURES::EMPTY);
  }
  //else get into the move "container" and get the evaluation of the resulting board
  auto best_value{start_node_->moves_[0].ptr_to_node->value()};
  //let move be the inital move, which is best in the moment
  std::tuple<int, int, Figure> move = start_node_->moves_[0].move;
  //search what is the best move, white or if black do it slightly different (min,max)
  switch (start_node_->board_.to_move_) {
    case Color::WHITE:
      //foreach possible move, check if the resulting position is better  
      for (const auto &link : start_node_->moves_) {
        if (link.ptr_to_node->value() > best_value) {
          move = link.move;
          best_value = link.ptr_to_node->value();
        }
        continue;
      }
      break;
    case Color::BLACK:
      //analogous to first case  
      for (const auto &link : start_node_->moves_) {
        if (link.ptr_to_node->value() < best_value) {
          move = link.move;
          best_value = link.ptr_to_node->value();
        }
        continue;
      }
  }
  //return the best move
  return move;
}



