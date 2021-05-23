//
// Created by Niclas Schwalbe on 05.04.21.
//

#pragma once
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include "Board.h"
#include "Node.h"

namespace OdinConstants {
    static const std::string standardBoardFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    static const double cpuct = 1.0;
}

class Node;

class Odin {
public:
    Odin();

    long positions_calculated_{0};
    std::shared_ptr<Node> start_node_;

    inline void searchOn() {
        searching_ = true;
        setUpForCalculations();
    }

    inline void searchOff() {
        searching_ = false;
    }

    void search();
    void setPosition(const std::string& fen, const std::vector<std::string>& moves);
    static double evaluatePosition(Board &board);

private:
    std::thread computingThread_{};
    bool searching_{false};
    bool in_chess_{true};

    void setUpForCalculations();
    void computeNext();

};

