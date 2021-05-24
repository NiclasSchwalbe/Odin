//
// Created by Niclas Schwalbe on 11.05.21.
//

#include <cmath>
#include "Node.h"

Node::Node(Board &board, std::optional<double> alpha, std::optional<double> beta, std::shared_ptr<Node> parent)
        : board_(board),
          beta_(beta),
          alpha_(alpha),
          parent_(parent),
          value_(std::nullopt),
          color_(board.to_move_),
          moves_(),
          intrinsic_value_(board.intrinsic_value_)
          {}



Node::Node(Board &&board, std::optional<double> alpha, std::optional<double> beta, std::shared_ptr<Node> parent)
        : board_(board),
          beta_(beta),
          alpha_(alpha),
          parent_(parent),
          value_(std::nullopt),
          color_(board.to_move_),
          intrinsic_value_(board.intrinsic_value_){}

/*
void Node::updateValueAsChild(double val) {
    std::shared_ptr<Node> parent(parent_);
    if (!value_.has_value()) {
        value_ = val;
        parent->updateValueAsChild(val);
        return;
    }
    switch (color_) {
        case BLACK:
            if (val > value_) {
                value_ = val;
                parent->updateValueAsChild(val);
            }
            return;
        case WHITE:
            if (val < value_) {
                value_ = val;
                parent->updateValueAsChild(val);
            }
            return;
    }
}


void Node::evalNextPosition() {
    if(moves_.size() == 0){
        expand();
        std::shared_ptr<Node> parent (parent_);
        parent->updateValueAsChild(intrinsic_value_);
        return;
    }
    visits_++;

    double score = -10;
    std::shared_ptr<Node> max = nullptr;
    for(auto move : moves_){
        if(move.ptr->visits_ == 0){
            move.ptr->evalNextPosition();
            return;
        }
       
    }



}
*/


