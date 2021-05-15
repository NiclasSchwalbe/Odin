//
// Created by Niclas Schwalbe on 11.05.21.
//

#include "Node.h"

Node::Node(Board &board, double alpha, double beta, std::shared_ptr<Node> parent)
    :board(board),
     beta(beta),
     alpha(alpha),
     parent(parent),
     value(0.0)
{}