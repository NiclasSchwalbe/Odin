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
      moves_()
{
}

Node::Node(const Board&& board, std::optional<double> alpha,
           std::optional<double> beta, Node* parent)
    : board_(board),
      beta_(beta),
      alpha_(alpha),
      parent_(parent),
      value_(std::nullopt),
      color_(board.to_move_)
{
}

/*
 * Recursively feeds new values up the tree.
 * It is using a min-max principle.
 */
void Node::updateValueAsChild(double val) {
  //if Node has no preset value, set it and update Parent  
  if (!value_.has_value()) {
    value_ = val;
    if (parent_ != nullptr) {
      parent_->updateValueAsChild(val);
    }
    return;
  }
  //if Node already has value, set it if its better for the color and update parent afterward
  bool new_value_set = false;
  switch (color_) {
    // Black is minimizing, white is maximizing
    case Color::BLACK:
      if (val < value_) {
        value_ = val;
        new_value_set = true;
      }
      break;
    case Color::WHITE:
      if (val > value_) {
        value_ = val;
        new_value_set = true;
      }
      break;
  }
  if (parent_ != nullptr && new_value_set) {
    parent_->updateValueAsChild(val);
  }
}

/*
 * Finds next position recusively and
 */
void Node::evalNextPosition() {

  visits_++;

  if (moves_.size() == 0 && !end_node_) {
    expand();
    if (parent_ != nullptr) {
      parent_->updateValueAsChild(intrinsic_value_);
    }
    return;
  }

  if (end_node_) {
    if (parent_ != nullptr) {
      parent_->updateValueAsChild(intrinsic_value_);
    }
    return;
  }  

  double mscore = moves_[0].ptr_to_node->value();
  Link opt = moves_[0];

  switch (board_.to_move_) {
    case Color::WHITE:
      for (auto move : moves_) {
        if (move.ptr_to_node->visits_ == 0) {
          opt = move;
          break;
        }
        /*
         * Calculate childs value, actually this should always be value_
         * If score is bigger, update score
         */
        double child_value{move.ptr_to_node->value()};
        double score =
            (child_value +
             OdinConstants::cpuct * sqrt(log2(visits_) / move.ptr_to_node->visits_));

        if (score > mscore) {
          mscore = score;
          opt = move;
        }
      }
      break;
    case Color::BLACK:
      for (auto move : moves_) {
        if (move.ptr_to_node->visits_ == 0) {
          opt = move;
          break;
        }
        /*
         * Calculate childs value, actually this should always be value_
         * If score if smaller, update score
         */
        double child_value{move.ptr_to_node->value()};
        double score =
            (child_value -
             OdinConstants::cpuct * sqrt(log2(visits_) / move.ptr_to_node->visits_));
        if (score < mscore) {
          mscore = score;
          opt = move;
        }
      }
  }



  // Now opt has best score and will therefore be explored
  opt.ptr_to_node->evalNextPosition();
}

void Node::expand() {
  std::vector<std::tuple<int, int, Figure>> moves;
  generateAllLegalMoves(moves, board_);
  //if there are no legal moves, it must be an endposition
  if (moves.size() == 0) {
    end_node_ = true;
    board_.is_end_position_ = true;
    return;
  }
  //there are legal moves, thus it is an endposition
  board_.is_end_position_ = false;
  //eval the board
  board_.reeval();
  intrinsic_value_ = board_.intrinsic_value_;
  //add all resulting boards as leaves into the board 
  for (auto& move : moves) {
    moves_.push_back(
        Link{std::make_shared<Node>(makeMove(board_, move), std::nullopt,
                                    std::nullopt, this), move});
  }
}
