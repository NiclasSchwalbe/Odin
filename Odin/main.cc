//
//  main.cpp
//  Odin
//
//  Created by Niclas Schwalbe on 04.04.21.
//

#include "engine/Odin.h"
#include "uci/uci.hpp"
#include "Utility.h"

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
    uci.receive_position.connect([&](const std::string &fen, const std::vector <std::string> &moves) {
        odin.setPosition(fen, moves);
    });

    uci.receive_go.connect([&](const std::map <uci::command, std::string> &parameters) {
        odin.searchOn();
    });

    uci.launch();


}
 */

int main(){
  Board b("8/3k4/8/8/8/8/3K4/8 w - - 0 1");
  printBoard(b);
}
