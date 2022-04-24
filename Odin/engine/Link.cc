//
// Created by Niclas Schwalbe on 18.05.21.
//

#include "Link.h"

Link::Link(std::shared_ptr<Node> pointer, std::tuple<int, int,Figure> mv):
    ptr_to_node{pointer},
    move{mv}
{}
