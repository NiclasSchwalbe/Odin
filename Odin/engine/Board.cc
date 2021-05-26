//w
// Created by Niclas Schwalbe on 06.04.21.
//

#include "Board.h"
#include "Odin.h"
#include "BoardIterator.h"

void Board::setPosition(const std::string& fen, const std::vector<std::string>& moves) {

    int rank = 7;
    int line = 0;
    int field = 0;

    std::vector<std::string> strList = splitString(fen, ' ');

    for (int i = 0; field < 64 && i < strList[0].length(); i++) 
    {
        switch (strList[0].at(i)) {
            case 'p':
                board_[rank][line] = BPAWN.value();
                break;
            case 'r':
                board_[rank][line] = BROOK.value();
                break;
            case 'b':
                board_[rank][line] = BBISHOP.value();
                break;
            case 'q':
                board_[rank][line] = BQUEEN.value();
                break;
            case 'n':
                board_[rank][line] = BKNIGHT.value();
                break;
            case 'k':
                board_[rank][line] = BKING.value();
                break;
            case 'P':
                board_[rank][line] = WPAWN.value();
                break;
            case 'R' :
                board_[rank][line] = WROOK.value();
                break;
            case 'N' :
                board_[rank][line] = WKNIGHT.value();
                break;
            case 'B' :
                board_[rank][line] = WBISHOP.value();
                break;
            case 'Q' :
                board_[rank][line] = WQUEEN.value();
                break;
            case 'K' :
                board_[rank][line] = WKING.value();
                break;
            case '/':
                rank--;
                line = 0;
                break;
            default:
                line += line-'1';
                field += line-'1';

                line++;
                field++;

        }

        if (strList.size()>=2)
        {
            if (strList[1] == "w"){
                to_move_ = Color::WHITE;
            } else if (strList[1] == "b") {
                to_move_ = Color::BLACK;
            }
        }
        //set boardstate to initial 0
        // Initialize all castle possibilities
        if (strList.size()>=3)
        {
            if (strList[2].find('K') != std::string::npos) {
                short_castle_white_ = true;
            }
            if (strList[2].find('Q') != std::string::npos) {
                short_castle_black_ = true;
            }
            if (strList[2].find('k') != std::string::npos) {
                long_castle_white_ = true;
            }
            if (strList[2].find('q') != std::string::npos) {
                long_castle_black_ = true;
            }
        }

    }

}


Board::Board(const std::string& fen) {
    const std::vector<std::string> vector(0);
    setPosition(fen, vector);
    intrinsic_value_ = Odin::evaluatePosition(*this);
}

BoardIterator Board::begin() const{
    return BoardIterator(0, this);
}
BoardIterator Board::end() const{
    return BoardIterator(63, this);
}

