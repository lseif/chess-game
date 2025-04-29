#include "Exceptions.h"
#include <array>
#include <memory>
#include <string>
#include <vector>

const int NUMBEROFDIRECTIONS = 8;
const int UP = 0;
const Pos UPDIR = Pos(1, 0);
const int UP_RIGHT = 1;
const int RIGHT = 2;
const Pos RIGHTDIR = Pos(0, 1);
const int DOWN_RIGHT = 3;
const int DOWN = 4;
const Pos DOWNDIR = Pos(-1, 0);
const int DOWN_LEFT = 5;
const int LEFT = 6;
const Pos LEFTDIR = Pos(0, -1);
const int UP_LEFT = 7;

class Piece {
  public:
  bool color;
  Pos position;
  bool isMoved;
  const std::string SYMBOL;
  virtual const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMoves() const = 0;
  const std::string show() const;
  Piece(const bool& Color, const Pos& position);
  Piece(const bool& Color, const Pos& position, const bool& isMoved);
  //Piece(const Piece& piece);
  virtual ~Piece() {};
  virtual std::shared_ptr<Piece> clone() const = 0;
  const bool operator==(const Piece& other) const;

  protected:
  explicit Piece(const bool& Color, const Pos& position, const std::string& symbol);
  //Piece(const Piece& piece);
};

class Rook : public Piece {
  public:
  Rook(const bool& Color, const Pos& position);
  virtual const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMoves() const;
  virtual std::shared_ptr<Piece> clone() const;
};

class Knight : public Piece {
  public:
  Knight(const bool& Color, const Pos& position);
  virtual const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMoves() const;
  virtual std::shared_ptr<Piece> clone() const;
};

class Bishop : public Piece {
  public:
  Bishop(const bool& Color, const Pos& position);
  virtual const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMoves() const;
  virtual std::shared_ptr<Piece> clone() const;
};

class King : public Piece {
  public:
  King(const bool& Color, const Pos& position);
  virtual const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMoves() const;
  virtual std::shared_ptr<Piece> clone() const;
};

class Queen : public Piece {
  public:
  Queen(const bool& Color, const Pos& position);
  virtual const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMoves() const;
  virtual std::shared_ptr<Piece> clone() const;
};

class Pawn : public Piece {
  public:
  bool hasMoved;
  Pawn(const bool& Color, const Pos& position);
  virtual const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMoves() const;
  virtual std::shared_ptr<Piece> clone() const;
};

std::string printGreen(const std::string& string);

std::string printRed(const std::string& string);
