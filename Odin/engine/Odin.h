//
// Created by Niclas Schwalbe on 05.04.21.
//

#include <string>
#include <vector>
#include<thread>

#include "Board.h"


#ifndef ODIN_ODIN_H
#define ODIN_ODIN_H

class Odin {
public:
    long positionsCalculated = 0;

    Board board = Board();

    Odin();

    void set_position(const std::string fen, const std::vector<std::string> moves);
    void searchOn();
    void searchOff();
    void search();

private:
    std::thread computingThread{};
    bool searching = false;
    bool inChess = true;

    void setUpForCalculations();
    void computeNext();


};

#endif //ODIN_ODIN_H
