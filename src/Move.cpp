#include <Move.h>
#include <memory>

//Move::Move(Piece& piece, Pos& position) : piece(piece.clone()), position(position){}
Move::Move(Piece& piece, Pos&& position) : piece(piece.clone()), position(position){}
Move::Move(Piece& piece, const Pos& position) : piece(piece.clone()), position(position){}
const std::shared_ptr<Piece> Move::getPiece() const {
  return piece;
}

std::shared_ptr<Piece> Move::getPiece() {
  return piece;
}

Pos Move::getPosition() {
  return position;
}

const Pos Move::getPosition() const {
  return position;
}

const Pos Move::vec() const {
  return getPosition()-getPiece()->position;
}