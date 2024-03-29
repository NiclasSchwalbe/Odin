#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Board.h"
#include "Odin.h"
#include "doctest/doctest.h"
#include "Utility.h"

TEST_CASE("Testing  Initalization - Board"){
  Board b("8/8/8/8/8/8/8/8");
}

TEST_CASE("Testing EMPTY BOARD - Board") {
  Board b("8/8/8/8/8/8/8/8");
  for (auto k : b) {
    REQUIRE(k == 0);
  }
}

TEST_CASE("Testing KINGS ONLY - Board") {
  Board b("8/3k4/8/8/8/8/3K4/8 w - - 0 1");
  REQUIRE(b.to_move_ == Color::WHITE);
  for (int i = 0; i < 64; i++) {
    CAPTURE(i);
    if (i == 11) {
      REQUIRE(b(i) == FIGURES::WKING.value());
    } else if (i == 51) {
      REQUIRE(b(i) == FIGURES::BKING.value());
    } else {
      REQUIRE(b(i) == 0);

    }
  }
}

TEST_CASE("Testing Castling and more... - Board") {
  Board b("rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 1");
  REQUIRE(b.to_move_ == Color::WHITE);
  REQUIRE(b.en_passant_field_ == 43);
  REQUIRE(b.long_castle_black_ == true);
  REQUIRE(b.long_castle_white_ == true);
  REQUIRE(b.short_castle_black_== true);
  REQUIRE(b.short_castle_white_== true);
}

TEST_CASE("Testing Castling and En Passant... 2 - Board") {
  Board b("rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQq d6 0 1");
  REQUIRE(b.to_move_ == Color::WHITE);
  REQUIRE(b.en_passant_field_ == 43);
  REQUIRE(b.long_castle_black_ == true);
  REQUIRE(b.long_castle_white_ == true);
  REQUIRE(b.short_castle_black_== false);
  REQUIRE(b.short_castle_white_== true);
}

TEST_CASE("Testing Castling and more... 3 - Board") {
  Board b("rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR w Qq d6 0 1");
  REQUIRE(b.to_move_ == Color::WHITE);
  REQUIRE(b.en_passant_field_ == 43);
  REQUIRE(b.long_castle_black_ == true);
  REQUIRE(b.long_castle_white_ == true);
  REQUIRE(b.short_castle_black_== false);
  REQUIRE(b.short_castle_white_== false);
}

TEST_CASE("Testing standardposition - Board") {
  Board b(OdinConstants::standardBoardFen);
  REQUIRE(b.to_move_ == Color::WHITE);
  REQUIRE(b.en_passant_field_ == -1);
  REQUIRE(b.long_castle_black_ == true);
  REQUIRE(b.long_castle_white_ == true);
  REQUIRE(b.short_castle_black_== true);
  REQUIRE(b.short_castle_white_== true);

  for(auto i : b[1]){
    REQUIRE(i == 1);
  }

  for(auto i : b[6]){
    REQUIRE(i == -1);
  }

  REQUIRE(b[7][0] == FIGURES::BROOK.value());
  REQUIRE(b[7][7] == FIGURES::BROOK.value());
  REQUIRE(b[7][1] == FIGURES::BKNIGHT.value());
  REQUIRE(b[7][6] == FIGURES::BKNIGHT.value());
  REQUIRE(b[7][2] == FIGURES::BBISHOP.value());
  REQUIRE(b[7][5] == FIGURES::BBISHOP.value());
  REQUIRE(b[7][3] == FIGURES::BQUEEN.value());
  REQUIRE(b[7][4] == FIGURES::BKING.value());

  REQUIRE(b[0][0] == FIGURES::WROOK.value());
  REQUIRE(b[0][7] == FIGURES::WROOK.value());
  REQUIRE(b[0][1] == FIGURES::WKNIGHT.value());
  REQUIRE(b[0][6] == FIGURES::WKNIGHT.value());
  REQUIRE(b[0][2] == FIGURES::WBISHOP.value());
  REQUIRE(b[0][5] == FIGURES::WBISHOP.value());
  REQUIRE(b[0][3] == FIGURES::WQUEEN.value());
  REQUIRE(b[0][4] == FIGURES::WKING.value());
}
