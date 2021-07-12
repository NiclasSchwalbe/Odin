//
// Created by Niclas Schwalbe on 11.05.21.
//

#include "Node.h"

#include <cmath>

Node::Node(const Board& board, std::optional<double> alpha,
           std::optional<double> beta, Node* parent)
    : board_(board),
      beta_(beta),
      alpha_(alpha),
      parent_(parent),
      value_(std::nullopt),
      color_(board.to_move_),
      moves_(),
      intrinsic_value_(board.intrinsic_value_) {}

Node::Node(const Board&& board, std::optional<double> alpha,
           std::optional<double> beta, Node* parent)
    : board_(board),
      beta_(beta),
      alpha_(alpha),
      parent_(parent),
      value_(std::nullopt),
      color_(board.to_move_),
      intrinsic_value_(board.intrinsic_value_) {}

/*
 * Recursively feeds new values up the tree.
 * It is using a min-max principle.
 */
void Node::updateValueAsChild(double val) {
  if (!value_.has_value()) {
    value_ = val;
    if (parent_ != nullptr) {
      parent_->updateValueAsChild(val);
    }
    return;
  }
  switch (color_) {
    // Black is minimizing, white is maximizing
    case Color::BLACK:
      if (val < value_) {
        value_ = val;
      }
      break;
    case Color::WHITE:
      if (val > value_) {
        value_ = val;
      }
      break;
  }
  if (parent_ != nullptr) {
    parent_->updateValueAsChild(val);
  }
}

/*
 * Finds next position recusively and
 */
void Node::evalNextPosition() {
  if (moves_.size() == 0) {
    expand();
    if (parent_ != nullptr) {
      parent_->updateValueAsChild(intrinsic_value_);
    }
    return;
  }
  visits_++;

  double mscore = moves_[0].ptr->value();
  Link opt = moves_[0];

  switch (board_.to_move_) {
    case Color::WHITE:
      for (auto move : moves_) {
        if (move.ptr->visits_ == 0) {
          opt = move;
          break;
        }
        /*
         * Calculate childs value, actually this should always be value_
         * If score is bigger, update score
         */
        double child_value{move.ptr->value()};
        double score =
            (child_value +
             OdinConstants::cpuct * sqrt(log2(visits_) / move.ptr->visits_));
        if (score > mscore) {
          mscore = score;
          opt = move;
        }
      }
      break;
    case Color::BLACK:
      for (auto move : moves_) {
        if (move.ptr->visits_ == 0) {
          opt = move;
          break;
        }
        /*
         * Calculate childs value, actually this should always be value_
         * If score if smaller, update score
         */
        double child_value{move.ptr->value()};
        double score =
            (child_value -
             OdinConstants::cpuct * sqrt(log2(visits_) / move.ptr->visits_));
        if (score < mscore) {
          mscore = score;
          opt = move;
        }
      }
  }



  // Now opt has best score and will therefore be explored
  opt.ptr->evalNextPosition();
}

void Node::expand() {
  std::vector<std::tuple<int, int, Figure>> moves;
  generateAllLegalMoves(moves, board_);
  for (auto& move : moves) {
    moves_.push_back(
        Link{std::make_shared<Node>(makeMove(board_, move), std::nullopt,
                                    std::nullopt, this),
             move});
  }
}
