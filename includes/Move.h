#include <Pieces.h>
#include <memory>
struct Move {
  public:
    Move(Piece& piece, Pos&& position);
    //Move(Piece& piece, Pos& position);
    Move(Piece& piece, const Pos& position);
    std::shared_ptr<Piece> getPiece();
    const std::shared_ptr<Piece> getPiece() const;
    Pos getPosition();
    const Pos getPosition()const;
    const Pos vec() const;
  private:
    const std::shared_ptr<Piece> piece;
    const Pos position;
};