//
// Created by Niclas Schwalbe on 05.04.21.
//
#include <chrono>
#include <optional>
#include "Odin.h"



Odin::Odin():
start_node_(new Node(Board(OdinConstants::standardBoardFen), std::nullopt, std::nullopt, nullptr)) {
    computingThread_ = std::thread(&Odin::search, this);
    computingThread_.detach();
}



void Odin::setPosition(const std::string& fen, const std::vector<std::string>& moves){
    start_node_ = std::make_shared<Node>(Board(fen), std::nullopt, std::nullopt, nullptr);
    start_node_->board_.setPosition(fen, moves);
}

void Odin::search() {
    using namespace std::chrono_literals;

    while(in_chess_){
        while(!searching_){
            std::this_thread::sleep_for(500ms);
        }
        computeNext();
        positions_calculated_++;
    }

}

double Odin::evaluatePosition(Board &board) {
    return 0.0;
}

void Odin::computeNext() {
    //start_node_->evalNextPosition();
}

void Odin::setUpForCalculations() {
}




