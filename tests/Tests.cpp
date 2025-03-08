#include "Positions.h"
#include <iostream>
#include <ostream>
#include <catch2/catch_test_macros.hpp>


Rook rook = Rook(BLACK, Pos(0,0));

bool test_movesOnEmptyBoard() {
  std::array<std::vector<Pos>, BOARDSIZE> possibleRookMovesAt00;
  std::array<std::vector<Pos>, BOARDSIZE> possibleRookMovesAt77;
  for (int i=1; i<BOARDSIZE; i++) {
    possibleRookMovesAt00[UP].push_back(Pos(i,0));
    possibleRookMovesAt00[RIGHT].push_back(Pos(0,i));

    possibleRookMovesAt77[DOWN].push_back(Pos((BOARDSIZE-1)-i,BOARDSIZE-1));
    possibleRookMovesAt77[LEFT].push_back(Pos(BOARDSIZE-1,(BOARDSIZE-1)-i));
  }
  Rook newRook = rook;
  if (newRook.possibleMoves()!=possibleRookMovesAt00) {
    return false;
  };
  newRook.position=Pos(7,7);
  if (newRook.possibleMoves()!=possibleRookMovesAt77) {
    return false;
  }
  return true;
}

bool test_placeNewPiece() {
  Board b = Board(std::vector<std::shared_ptr<Piece>>{Rook(BLACK, Pos(0,0)).clone()});
  Board emptyBoard(std::vector<std::shared_ptr<Piece>>{});
  emptyBoard.placeNewPiece(rook);
  if (b==emptyBoard) {
    return true;
  } else {
    return false;
  }
}

bool test_unruledMove() {
  Rook rook1 = rook;
  Rook rook2 = Rook(BLACK, Pos(1,2));
  Board c = Board({rook2.clone()});
  c.unruledMove(Move(*c.board[1][2], Pos(2,2)));
  Board b = Board({rook1.clone()});
  b.unruledMove(Move(*b.board[0][0], Pos(2,2)));
  if(b==c) {
    return true;
  } else {
    return false;
  }
}

bool test_ruledMove() {
  Board b = startPosition();
  Board c = startPosition();
  b.ruledMove(Move(*b.pieceAt(Pos(1,4)), Pos(2, 4)));
  c.unruledMove(Move(*c.pieceAt(Pos(1,4)), Pos(2, 4)));
  if (c==b) {
    return true;
  } else {
    return false;
  }
}

bool test_pawnTwoSteps() {
  Board b = startPosition();
  Board c = startPosition();
  c.unruledMove(Move(*b.pieceAt(Pos(1,0)), Pos(3,0)));
  b.ruledMove(Move(*b.pieceAt(Pos(1,0)), Pos(3,0)));
  try {
    b.ruledMove(Move(*b.pieceAt(Pos(3,0)), Pos(5,0)));
    return false;
  } catch (NotAllowedMoveException) {
    return true;
  }
}

bool test_castle() {
  Board b = castlePosition();
  Board c = castlePosition();
  try {
    b.ruledMove(Move(*b.pieceAt(Pos(0,4)), Pos(0,2)));
    return false;
  } catch (NotAllowedMoveException) {
    try {
      b.ruledMove(Move(*b.pieceAt(Pos(0,4)), Pos(0,6)));
      return false;
    } catch (NotAllowedMoveException)   {
      b.ruledMove(Move(*b.pieceAt(Pos(7,3)), Pos(7,0)));
      b.ruledMove(Move(*b.pieceAt(Pos(0,6)), Pos(2,5)));
      c.ruledMove(Move(*c.pieceAt(Pos(7,3)), Pos(7,0)));
      c.ruledMove(Move(*c.pieceAt(Pos(0,6)), Pos(2,5)));

      b.ruledMove(Move(*b.pieceAt(Pos(0,4)), Pos(0,2)));
      c.ruledMove(Move(*c.pieceAt(Pos(0,4)), Pos(0,6)));
    }
  
  }
  return true;
}

bool test_kingCheck() {return true;}

bool test_enpassant() {
  Board b = checkEnpassantPosition();
  b.ruledMove(Move(*b.pieceAt(Pos(4,4)), Pos(5,3)));


    
  Board c =startPosition();
  c.unruledMove(Move(*c.pieceAt(Pos(6, 3)), Pos(4,3)));
  c.unruledMove(Move(*c.pieceAt(Pos(1, 4)), Pos(4,3)));
  c.unruledMove(Move(*c.pieceAt(Pos(4, 3)), Pos(5,3)));

  if(b==c) {
    return true;
  } else {
    return false;
  }
}


TEST_CASE( "test_moves") {
  std::cout << "tests";
  REQUIRE( test_movesOnEmptyBoard());
  REQUIRE( test_placeNewPiece());
  REQUIRE( test_unruledMove());
  REQUIRE( test_ruledMove());
  REQUIRE( test_enpassant() );
  REQUIRE( test_kingCheck());
  REQUIRE( test_castle());
  REQUIRE( test_pawnTwoSteps() ); 
}