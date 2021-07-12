//
// Created by Niclas Schwalbe on 11.05.21.
//


#pragma once

#include <memory>
#include <vector>
#include <optional>

#include "Board.h"
#include "Odin.h"
#include "Link.h"


class Link;

class Node {
public:
    Node* parent_;
    std::vector<Link> moves_;
    Board board_;
    double intrinsic_value_;
    std::optional<double> value_;
    std::optional<double> alpha_;
    std::optional<double> beta_;
    long visits_{0};
    Color color_;
    bool end_node_{false};

    Node(const Board &board, std::optional<double> alpha, std::optional<double> beta, Node* parent);
    Node(const Board &&board, std::optional<double> alpha, std::optional<double> beta, Node* parent);
    void addNode(Node d);
    void updateValueAsChild(double value);
    void evalNextPosition();
    void expand();

    double value() const {
      if (value_.has_value()) {
        return value_.value();
      }
      return intrinsic_value_;
    }

};


