//w
// Created by Niclas Schwalbe on 06.04.21.
//

#include "Board.h"
#include "../util/Utility.h"

void Board::set_position(const std::string fen, const std::vector<std::string> moves) {
    int rank = 7;
    int line = 0;
    int field = 0;

    std::vector<std::string> strList = splitString(fen, ' ');

    for (int i = 0; field < 64 && i < strList[0].length(); i++)
    {
        switch (strList[0].at(i)) {
            case 'p':
                board[rank][line] = BPAWN.value();
                break;
            case 'r':
                board[rank][line] = BROOK.value();
                break;
            case 'b':
                board[rank][line] = BBISHOP.value();
                break;
            case 'q':
                board[rank][line] = BQUEEN.value();
                break;
            case 'k':
                board[rank][line] = BKING.value();
                break;
            case 'P':
                board[rank][line] = WPAWN.value();
                break;
            case 'R' :
                board[rank][line] = WPAWN.value();
                break;
            case 'N' :
                board[rank][line] = WKNIGHT.value();
                break;
            case 'B' :
                board[rank][line] = WBISHOP.value();
                break;
            case 'Q' :
                board[rank][line] = WQUEEN.value();
                break;
            case 'K' :
                board[rank][line] = WKING.value();
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
                toMove = WHITE;
            } else if (strList[1] == "b") {
                toMove = BLACK;
            }
        }

        // set boardstate to initial 0
        // Initialize all castle possibilities
        if (strList.size()>=3)
        {
            if (strList[2].find('K') != string::npos) state =
                                                              TBoardState_SET_CASTLE_WHITE_KS(state,WHITE_CASTLE_KINGSIDE);
            if (strList[2].find('Q') != string::npos) state =
                                                              TBoardState_SET_CASTLE_WHITE_QS(state,WHITE_CASTLE_QUEENSIDE);
            if (strList[2].find('k') != string::npos) state =
                                                              TBoardState_SET_CASTLE_BLACK_KS(state,BLACK_CASTLE_KINGSIDE);
            if (strList[2].find('q') != string::npos) state =
                                                              TBoardState_SET_CASTLE_BLACK_QS(state,BLACK_CASTLE_QUEENSIDE);
        }
    }


    return;
}