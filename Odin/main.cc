//
//  main.cpp
//  Odin
//
//  Created by Niclas Schwalbe on 04.04.21.
//

#include "Utility.h"
#include "engine/Odin.h"
#include "uci/uci.hpp"

/*
int main(int argc, const char *argv[]) {
    Odin odin;
    uci uci;
    uci.receive_uci.connect([&]() {
        uci::send_id("Odin", "Niclas Schwalbe");
        uci::send_option_uci_limit_strength(false);
        uci::send_uci_ok();
    });
    uci.receive_is_ready.connect([&]() {
        uci::send_ready_ok();
    });
    uci.receive_position.connect([&](const std::string &fen, const std::vector
<std::string> &moves) { odin.setPosition(fen, moves);
    });

    uci.receive_go.connect([&](const std::map <uci::command, std::string>
&parameters) { odin.searchOn();
    });

    uci.launch();


}
 */
#include <iostream>
#include <string>
#include "Odin.h"
#include <thread>
#include <chrono>


int main(){ 
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    Odin odin{};
    Board board{OdinConstants::standardBoardFen};
    odin.searchOn();
    for (int i = 0; i < 100; i++) {
      std::cout << board;
      odin.search();
      std::tuple<int, int, Figure> move = odin.bestMove();
      board = makeMove(board, move);
      odin.setPosition(board);
      //sleep_for(seconds(2));
    }
}
