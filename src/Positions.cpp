#include "Positions.h"
Board castlePosition() {
  std::vector<std::shared_ptr<Piece>> v;
  v.push_back(Knight(WHITE, Pos(0, 6)).clone());
  v.push_back(Rook(WHITE, Pos(0, 0)).clone());
  v.push_back(Rook(WHITE, Pos(0, 7)).clone());
  v.push_back(King(WHITE, Pos(0, 4)).clone());
  v.push_back(King(BLACK, Pos(7, 4)).clone());
  v.push_back(Queen(BLACK, Pos(7, 3)).clone());
  return Board(v);
}

Board kingCheckPosition() {
  std::vector<std::shared_ptr<Piece>> v;
  v.push_back(Pawn(WHITE, Pos(6, 6)).clone());
  v.push_back((Pawn(BLACK, Pos(2, 3))).clone());
  v.push_back(King(BLACK, Pos(7, 2)).clone());
  return Board(v);
}

Board startPosition() {
  std::vector<std::shared_ptr<Piece>> v;
  for(int i = 0; i< BOARDSIZE; i++) {
    v.push_back(Pawn(WHITE, Pos(1, i)).clone());
    v.push_back(Pawn(BLACK, Pos(6, i)).clone());
  }
  v.push_back(Rook(WHITE, Pos(0, 0)).clone());
  v.push_back(Rook(WHITE, Pos(0, 7)).clone());

  v.push_back(Rook(BLACK, Pos(7, 0)).clone());
  v.push_back(Rook(BLACK, Pos(7, 7)).clone());

  v.push_back(Knight(WHITE, Pos(0, 1)).clone());
  v.push_back(Knight(WHITE, Pos(0, 6)).clone());

  v.push_back(Knight(BLACK, Pos(7, 1)).clone());
  v.push_back(Knight(BLACK, Pos(7, 6)).clone());

  v.push_back(Bishop(WHITE, Pos(0, 2)).clone());
  v.push_back(Bishop(WHITE, Pos(0, 5)).clone());

  v.push_back(Bishop(BLACK, Pos(7, 2)).clone());
  v.push_back(Bishop(BLACK, Pos(7, 5)).clone());

  v.push_back(King(BLACK, Pos(7, 4)).clone());
  v.push_back(King(WHITE, Pos(0, 4)).clone());

  v.push_back(Queen(BLACK, Pos(7, 3)).clone());
  v.push_back(Queen(WHITE, Pos(0, 3)).clone());
  
  return Board(v);
}

Board checkEnpassantPosition() {
  Board b = startPosition();
  b.unruledMove(Move(*b.pieceAt(Pos(1,4)), Pos(4,4)));
  b.ruledMove(Move(*b.pieceAt(Pos(6, 3)), Pos(4,3)));

  return b;
}