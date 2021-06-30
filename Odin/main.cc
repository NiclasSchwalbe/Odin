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

int main(){ 
    Board b{"8/8/8/3B4/8/8/8/8 w - - 0 1"}; 
    std::vector<std::tuple<int, int, Figure>> moves{};
    generateAllBishopMoves(moves, b);
    std::cout << (moves.size()) << std::endl;
}
