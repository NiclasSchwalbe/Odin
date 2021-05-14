//
// Created by Niclas Schwalbe on 11.05.21.
//


#include <memory>
#include <vector>
#include "Board.h"
#include "Odin.h"

#pragma once

class Node {
public:
    std::shared_ptr<Node b> parent;
    std::vector<std::shared_ptr<Node b>> nodes;
    Board board;
    double value;
    double alpha;
    double beta;

    Node(Board &board, double alpha, double beta, std::shared_ptr<Node> parent);
    void addNode(Node d);

};


