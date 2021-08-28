//
//  main.cpp
//  Odin
//
//  Created by Niclas Schwalbe on 04.04.21.
//

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
#include <thread>
#include <chrono>
#include "Odin.h"

int main(){


  using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds
  Odin odin{};
  Board board{"7k/R7/5K2/8/8/8/8/8 w - - 0 1"};

  odin.searchOn();
  for (int i = 0; i < 80 && !isCheckMate(board) && !isStaleMate(board); i++) {
    std::cout << board;
    odin.setPosition(board);
    odin.search();
    std::tuple<int, int, Figure> move = odin.bestMove();
    board = makeMove(board, move);
    std::cout << "Move played:" << std::get<0>(move) << "-"
              << std::get<1>(move) << std::endl;
    //sleep_for(seconds(2));
    }


}




