//
// Created by Niclas Schwalbe on 11.05.21.
//

#include <cmath>
#include "Node.h"

Node::Node(Board& board, std::optional<double> alpha, std::optional<double> beta, std::shared_ptr<Node> parent)
	: board_(board),
	beta_(beta),
	alpha_(alpha),
	parent_(parent),
	value_(std::nullopt),
	color_(board.to_move_),
	moves_(),
	intrinsic_value_(board.intrinsic_value_)
{}



Node::Node(Board&& board, std::optional<double> alpha, std::optional<double> beta, std::shared_ptr<Node> parent)
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
  std::shared_ptr<Node> parent{parent_};
	if (!value_.has_value()) {
		value_ = val;
		parent->updateValueAsChild(val);
		return;
	}
	switch (color_) {
	//Black is minimizing, white is maximizing
	case Color::BLACK:
		if (val > value_) {
			value_ = val;
			parent->updateValueAsChild(val);
		}
		return;
	case Color::WHITE:
		if (val < value_) {
			value_ = val;
			parent->updateValueAsChild(val);
		}
		return;
	}
}

/*
* Finds next position recusively and 
*/
void Node::evalNextPosition() {
	if (moves_.size() == 0) {
		expand();
        std::shared_ptr<Node> parent{parent_};
		parent->updateValueAsChild(intrinsic_value_);
		return;
	}
	visits_++;

	double mscore = -10;
	Link max = moves_[0];
	for (auto move : moves_) {
		if (move.ptr->visits_ == 0) {
			max = move;
			break;
		}
		/*
		* Calculate childs value, actually this should always be value_
		* If score is bigger, update score
		*/
		double child_value;
		if (move.ptr->value_.has_value()) {
			child_value = move.ptr->value_.value();
		}
		else {
			child_value = move.ptr->intrinsic_value_;
		}
		double score = (child_value + OdinConstants::cpuct * sqrt(log2(visits_) / move.ptr->visits_));
		if (score > mscore) {
			mscore = score;
			max = move;
		}
	}

	//Now max has highest score and will therefore be explored
	max.ptr->evalNextPosition();

}

void Node::expand() {
	std::vector<std::string> moves;

}


