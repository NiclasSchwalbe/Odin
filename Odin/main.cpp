//
//  main.cpp
//  Odin
//
//  Created by Niclas Schwalbe on 04.04.21.
//

#include <iostream>
#include "engine/Odin.h"
#include "uci/uci.hpp"

int main(int argc, const char *argv[]) {
    Odin odin = Odin();
    uci uci;
    uci.receive_uci.connect([&]() {
        uci.send_id("Odin", "Niclas Schwalbe");
        uci.send_option_uci_limit_strength(false);
        uci.send_uci_ok();
    });
    uci.receive_is_ready.connect([&]() {
        uci.send_ready_ok();
    });
    uci.receive_position.connect([&](const std::string &fen, const std::vector <std::string> &moves) {
        odin.set_position(fen, moves);
    });
    uci.receive_go.connect([&](const std::map <uci::command, std::string> &parameters) {
        odin.searchOn();
    });
    uci.launch();


}
