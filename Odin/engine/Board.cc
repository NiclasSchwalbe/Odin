// 
// Created by Niclas Schwalbe on 06.04.21.
//

#include "Board.h"
#include "Odin.h"
#include "Utility.h"

Board::Board(const Board& b){
  *this = b;
}

/*
* This method generates a board using a fen.
*/
void Board::setPosition(const std::string &fen,
                        const std::vector<std::string> &moves) {
  int rank = 7;
  int line = 0;
  int field = 0;

  std::vector<std::string> strList = splitString(fen, ' ');

  for (int i = 0; field < 64 && i < strList[0].length(); i++) {
    char c = strList[0].at(i);
    switch (c) {
      case 'p':board_[rank][line] = FIGURES::BPAWN.value();
        break;
      case 'r':board_[rank][line] = FIGURES::BROOK.value();
        break;
      case 'b':board_[rank][line] = FIGURES::BBISHOP.value();
        break;
      case 'q':board_[rank][line] = FIGURES::BQUEEN.value();
        break;
      case 'n':board_[rank][line] = FIGURES::BKNIGHT.value();
        break;
      case 'k':board_[rank][line] = FIGURES::BKING.value();
        break;
      case 'P':board_[rank][line] = FIGURES::WPAWN.value();
        break;
      case 'R':board_[rank][line] = FIGURES::WROOK.value();
        break;
      case 'N':board_[rank][line] = FIGURES::WKNIGHT.value();
        break;
      case 'B':board_[rank][line] = FIGURES::WBISHOP.value();
        break;
      case 'Q':board_[rank][line] = FIGURES::WQUEEN.value();
        break;
      case 'K':board_[rank][line] = FIGURES::WKING.value();
        break;
      case '/':
        rank--;
        line = 0;
        continue;
      default:
        line += c - '1';
        field += c - '1';
    }
    line++;
    field++;

  }
  if (strList.size() >= 2) {
    if (strList[1] == "w") {
      to_move_ = Color::WHITE;
    } else if (strList[1] == "b") {
      to_move_ = Color::BLACK;
    }
  }
  // set boardstate to initial 0
  // Initialize all castle possibilities
  if (strList.size() >= 3) {
    if (strList[2].find('K') != std::string::npos) {
      short_castle_white_ = true;
    }
    if (strList[2].find('Q') != std::string::npos) {
      long_castle_white_ = true;
    }
    if (strList[2].find('k') != std::string::npos) {
      short_castle_black_ = true;
    }
    if (strList[2].find('q') != std::string::npos) {
      long_castle_black_ = true;
    }
  }

  if (strList.size() >=4){
    if(strList[3].find('-') == std::string::npos){
        char line = strList[3][0] - 'a';
        char rank = strList[3][1] - '1';
        en_passant_field_ = line + rank * 8;
    }
  }

  if (strList.size() >= 5){
    if(strList[4] != "-"){
      fifty_move_rule_info_ = std::stoi(strList[4]);
    } else {
      fifty_move_rule_info_ = -1;
    }
  }
}

Board::Board(const std::string &fen) {
  const std::vector<std::string> vector(0);
  setPosition(fen, vector);
  //intrinsic_value_ = Odin::evaluatePosition(*this);
}

bool Board::operator==(const Board &b) const {
  // checks if two Boards have the same position
  for (int i = 0; i < 64; i++) {
    if (b(i) != this->operator()(i)) {
      return false;
    }
  }
  // and if they differ in any other way
  if (b.to_move_ != this->to_move_ ||
      b.en_passant_field_ != this->en_passant_field_) {
    return false;
  }

  if (b.long_castle_black_ != this->long_castle_black_ ||
      b.long_castle_white_ != this->long_castle_white_) {
    return false;
  }

  if (b.short_castle_black_ != this->short_castle_black_ ||
      b.short_castle_white_ != this->short_castle_white_) {
    return false;
  }

  if (b.fifty_move_rule_info_ != this->fifty_move_rule_info_) {
    return false;
  }

  return true;
}

void Board::reeval() { intrinsic_value_ = Odin::evaluatePosition(*this); }

Board::BoardIterator Board::begin() const { return Board::BoardIterator(0, this); }
Board::BoardIterator Board::end() const { return Board::BoardIterator(64, this); }
