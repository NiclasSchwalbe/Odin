//
// Created by Niclas Schwalbe on 05.04.21.
//

#pragma once

#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>
#include "Board.h"
#include "Figure.h"
#include "Utility.h"

class Odin {
public:
    long positionsCalculated = 0;

    Board board{standardBoardFen};
    Odin();
    void set_position(const std::string& fen, const std::vector<std::string>& moves);
    void searchOn();
    void searchOff();
    void search();
    static void evaluatePosition(Board &board);

private:
    std::thread computingThread{};
    bool searching = false;
    bool inChess = true;

    void setUpForCalculations();
    void computeNext();
};

