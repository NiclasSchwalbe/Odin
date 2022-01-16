//
// Created by Niclas Schwalbe on 18.05.21.
//


#pragma once

#include <memory>
#include <utility>
#include "Node.h"
#include "Figure.h"

class Node;

class Link {
public:
    std::shared_ptr<Node> ptr_to_node;
    std::tuple<int,int,Figure> move;
    Link(std::shared_ptr<Node> ptr,  std::tuple<int,int,Figure> move);
};


