//
// Created by Niclas Schwalbe on 05.04.21.
//

#pragma once
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>
#include "../util/Utility.h"

#include "Board.h"
#include "Figure.h"

static const std::string standardBoardFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

class Odin {
public:
    long positionsCalculated = 0;
    Odin();
    Board board = Board(standardBoardFen);
    void set_position(const std::string& fen, const std::vector<std::string>& moves);


    void searchOn();

    void searchOff();
    void search();


    static double evaluatePosition(Board &board);


private:
    std::thread computingThread{};
    bool searching = false;
    bool inChess = true;

    void setUpForCalculations();
    void computeNext();

};

