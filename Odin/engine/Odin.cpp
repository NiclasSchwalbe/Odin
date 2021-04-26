//
// Created by Niclas Schwalbe on 05.04.21.
//

#include "Odin.h"
#include "Figure.h"
#include <chrono>


Odin::Odin() {
    std::thread(&Odin::search, this);
}

void Odin::set_position(const std::string fen, const std::vector<std::string> moves){
    board.set_position(fen, moves);
}

inline void Odin::searchOn() {
    searching = true;
    setUpForCalculations();
}

inline void Odin::searchOff() {
    searching = false;
}

void Odin::search() {
    using namespace std::chrono_literals;

    while(inChess){
        while(!searching){
            std::this_thread::sleep_for(500ms);
        }
        computeNext();
        positionsCalculated++;
    }

}

void Odin::computeNext() {

}





