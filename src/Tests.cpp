#include "Tests.h"
#include <iostream>
#include <ostream>

#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " <<  __LINE__ << std::endl; }

Rook rook = Rook(BLACK, Pos(0,0));

void test_movesOnEmptyBoard() {
  std::array<std::vector<Pos>, BOARDSIZE> possibleRookMovesAt00;
  std::array<std::vector<Pos>, BOARDSIZE> possibleRookMovesAt77;
  for (int i=1; i<BOARDSIZE; i++) {
    possibleRookMovesAt00[UP].push_back(Pos(i,0));
    possibleRookMovesAt00[RIGHT].push_back(Pos(0,i));

    possibleRookMovesAt77[DOWN].push_back(Pos((BOARDSIZE-1)-i,BOARDSIZE-1));
    possibleRookMovesAt77[LEFT].push_back(Pos(BOARDSIZE-1,(BOARDSIZE-1)-i));
  }
  Rook newRook = rook;
  IS_TRUE(newRook.possibleMoves()==possibleRookMovesAt00);
  newRook.position=Pos(7,7);
  IS_TRUE(newRook.possibleMoves()==possibleRookMovesAt77);
}

void test_placeNewPiece() {
  Board b = Board(std::vector<std::shared_ptr<Piece>>{Rook(BLACK, Pos(0,0)).clone()});
  Board emptyBoard(std::vector<std::shared_ptr<Piece>>{});
  emptyBoard.placeNewPiece(rook);
  IS_TRUE(b==emptyBoard);
}

void test_unruledMove() {
  Rook rook1 = rook;
  Rook rook2 = Rook(BLACK, Pos(1,2));
  Board c = Board({rook2.clone()});
  c.unruledMove(Move(*c.board[1][2], Pos(2,2)));
  Board b = Board({rook1.clone()});
  b.unruledMove(Move(*b.board[0][0], Pos(2,2)));
  IS_TRUE(b==c);
}

void test_ruledMove() {
  Board b = startPosition();
  Board c = startPosition();
  b.ruledMove(Move(*b.pieceAt(Pos(1,4)), Pos(2, 4)));
  c.unruledMove(Move(*c.pieceAt(Pos(1,4)), Pos(2, 4)));
  IS_TRUE(c==b);
}

void test_pawnTwoSteps() {
  Board b = startPosition();
  Board c = startPosition();
  c.unruledMove(Move(*b.pieceAt(Pos(1,0)), Pos(3,0)));
  b.ruledMove(Move(*b.pieceAt(Pos(1,0)), Pos(3,0)));
  try {
    b.ruledMove(Move(*b.pieceAt(Pos(3,0)), Pos(5,0)));
    IS_TRUE(false);
  } catch (NotAllowedMoveException) {
    IS_TRUE(b==c);
  }
}

void test_castle() {
  Board b = castlePosition();
  Board c = castlePosition();
  try {
    b.ruledMove(Move(*b.pieceAt(Pos(0,4)), Pos(0,2)));
    IS_TRUE(false);
  } catch (NotAllowedMoveException) {
    try {
      b.ruledMove(Move(*b.pieceAt(Pos(0,4)), Pos(0,6)));
      IS_TRUE(false);
    } catch (NotAllowedMoveException)   {
      b.ruledMove(Move(*b.pieceAt(Pos(7,3)), Pos(7,0)));
      b.ruledMove(Move(*b.pieceAt(Pos(0,6)), Pos(2,5)));
      c.ruledMove(Move(*c.pieceAt(Pos(7,3)), Pos(7,0)));
      c.ruledMove(Move(*c.pieceAt(Pos(0,6)), Pos(2,5)));

      b.ruledMove(Move(*b.pieceAt(Pos(0,4)), Pos(0,2)));
      c.ruledMove(Move(*c.pieceAt(Pos(0,4)), Pos(0,6)));
    }
  
  }
}

void test_kingCheck() {}

void test_enpassant() {
  Board b = checkEnpassantPosition();
  b.ruledMove(Move(*b.pieceAt(Pos(4,4)), Pos(5,3)));


    
  Board c =startPosition();
  c.unruledMove(Move(*c.pieceAt(Pos(6, 3)), Pos(4,3)));
  c.unruledMove(Move(*c.pieceAt(Pos(1, 4)), Pos(4,3)));
  c.unruledMove(Move(*c.pieceAt(Pos(4, 3)), Pos(5,3)));

  IS_TRUE(b==c);
}

void tests() {
  test_movesOnEmptyBoard();
  test_placeNewPiece();
  test_unruledMove();
  test_ruledMove();
  test_pawnTwoSteps();
  test_castle();
  test_enpassant();
}