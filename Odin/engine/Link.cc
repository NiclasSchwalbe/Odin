//
// Created by Niclas Schwalbe on 18.05.21.
//

#include "Link.h"

Link::Link(std::shared_ptr<Node> pointer, std::pair<int, int> mv):
    ptr{pointer},
    move{mv}
{}
