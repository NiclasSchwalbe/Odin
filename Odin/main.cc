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
#include <iostream>
#include <string>
int main(){
  Board b("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1");
  std::vector<std::tuple<int, int, Figure>> moves{};
  generateAllPawnMoves(std::move(moves), b);
  Board c{makeMove(b, moves[9])};
  Board comparison{"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1"};
  std::cout << (c == comparison) << std::endl;
}
