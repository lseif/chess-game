#include <string>
#include <vector>
#include "Board.h"

bool inBoardRange(const Pos& pos) {
  return pos.inRange(Pos(0, 0), Pos(BOARDSIZE, BOARDSIZE));
}

Piece::Piece(const bool& color, const Pos& position) : color(color), position(position), isMoved(false) {}

Piece::Piece(const bool& color, const Pos& position, const bool& isMoved) : color(color), position(position), isMoved(isMoved) {}

Piece::Piece(const bool& color, const Pos& position, const std::string& symbol) : color(color), position(position), isMoved(false), SYMBOL(symbol) {}

//Piece::Piece(const Piece& piece) : color(piece.color), position(piece.position), isMoved(piece.isMoved), SYMBOL(piece.SYMBOL) {}


std::shared_ptr<Piece> Rook::clone() const {
  return std::shared_ptr<Piece>(new Rook(*this));
}

std::shared_ptr<Piece> Knight::clone() const {
  return std::shared_ptr<Piece>(new Knight(*this));
}

std::shared_ptr<Piece> Bishop::clone() const {
  return std::shared_ptr<Piece>(new Bishop(*this));
}

std::shared_ptr<Piece> Queen::clone() const {
  return std::shared_ptr<Piece>(new Queen(*this));
}

std::shared_ptr<Piece> King::clone() const {
  return std::shared_ptr<Piece>(new King(*this));
}

std::shared_ptr<Piece> Pawn::clone() const {
  return std::shared_ptr<Piece>(new Pawn(*this));
}


const std::string Piece::show() const {
  if (color==WHITE) {
    return printRed(SYMBOL);
  } else {
    return printGreen(SYMBOL);
  }
}

const bool Piece::operator==(const Piece& other) const {
  if (color==other.color&&position==other.position&&isMoved==other.isMoved&&SYMBOL==other.SYMBOL) {
    return true;
  } else {
    return false;
  }
}



Rook::Rook(const bool& c, const Pos& p) : Piece(c, p, std::string("R")) {}

Knight::Knight(const bool& c, const Pos& p) : Piece(c, p, std::string("K")) {}

Bishop::Bishop(const bool& c, const Pos& p) : Piece(c, p, std::string("B")) {}

Queen::Queen(const bool& c, const Pos& p) : Piece(c, p, std::string("Q")) {}

King::King(const bool& c, const Pos& p) : Piece(c, p, std::string("O")) {}

Pawn::Pawn(const bool& c, const Pos& p) : Piece(c, p, std::string("P")) {}



const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMovesRow(const Pos& position) {
  std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> result;
  for (int i = 1; i<BOARDSIZE; i++) {
    Pos possibleUpMove = position + UPDIR.scale(i); //UPDIR is const
    Pos possibleDownMove = position + DOWNDIR.scale(i);
    Pos possibleRightMove = position + RIGHTDIR.scale(i);
    Pos possibleLeftMove = position + LEFTDIR.scale(i);
    if(inBoardRange(possibleUpMove)){
      result[UP].push_back(possibleUpMove);
    }
    if(inBoardRange(possibleDownMove)) {
      result[DOWN].push_back(possibleDownMove);
    }
    if(inBoardRange(possibleRightMove)) {
      result[RIGHT].push_back(possibleRightMove);
    }
    if(inBoardRange(possibleLeftMove)) {
      result[LEFT].push_back(possibleLeftMove);
    }
  }
  
  return result;
}

const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMovesDiagonal(const Pos& position) {
  std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> result;
  for (int i = 1; i<BOARDSIZE; i++) {
    Pos possibleUpRightMove = position + (UPDIR+RIGHTDIR).scale(i); //UPDIR is const
    Pos possibleDownLeftMove = position + (DOWNDIR+LEFTDIR).scale(i);
    Pos possibleDownRightMove = position + (DOWNDIR+RIGHTDIR).scale(i);
    Pos possibleUpLeftMove = position + (UPDIR+LEFTDIR).scale(i);
    if(inBoardRange(possibleUpRightMove)){
      result[UP_RIGHT].push_back(possibleUpRightMove);
    }
    if(inBoardRange(possibleDownLeftMove)) {
      result[DOWN_LEFT].push_back(possibleDownLeftMove);
    }
    if(inBoardRange(possibleDownRightMove)) {
      result[DOWN_RIGHT].push_back(possibleDownRightMove);
    }
    if(inBoardRange(possibleUpLeftMove)) {
      result[UP_LEFT].push_back(possibleUpLeftMove);
    }
  }
  return result;
}

const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> Rook:: possibleMoves() const{
  return possibleMovesRow(position);
}

const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> Knight:: possibleMoves() const{
  std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMoves;
  std::array<Pos, NUMBEROFDIRECTIONS> moves;
  moves[UP] = Pos(2, -1);
  moves[UP_RIGHT] = moves[UP].mirrorOnX();
  for(int direction = 2; direction < NUMBEROFDIRECTIONS; direction++) { //calculate vector where Knight can jump
    moves[direction] = moves[direction-2].rotateRight(); 
  }

  for (int direction =0; direction<NUMBEROFDIRECTIONS; direction++) { //calculate moves 
    moves[direction]=moves[direction]+position;
  }
  
  for(int direction = UP; direction<NUMBEROFDIRECTIONS; direction++) { //add Moves that are on the board
    if(inBoardRange(moves[direction])) {
      possibleMoves[direction].push_back(moves[direction]);
    }
  }

  return possibleMoves;
}
 
const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> Bishop:: possibleMoves() const{
  return possibleMovesDiagonal(position);
}

const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> Queen:: possibleMoves() const{
  std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> result = possibleMovesRow(position);
  std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> diagonalMoves = possibleMovesDiagonal(position);
  for(int i=0; i<NUMBEROFDIRECTIONS; i++){
    result[i].insert(result[i].end(), diagonalMoves[i].begin(), diagonalMoves[i].end());
  }
  
  return result;
}

const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> King:: possibleMoves() const{
  std::array<Pos, NUMBEROFDIRECTIONS> moves;
  std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMoves;

  moves[UP] = Pos(1, 0);
  moves[UP_RIGHT] = Pos(1,1);
  for(int direction = 2; direction < NUMBEROFDIRECTIONS; direction++) {
    moves[direction] = moves[direction-2].rotateRight(); 
  }

  for (int direction = 0; direction<NUMBEROFDIRECTIONS; direction++) {
    moves[direction]=moves[direction];
  }
  
  for(int direction = UP; direction<NUMBEROFDIRECTIONS; direction++) {
    if(inBoardRange(moves[direction]+position)) {
      possibleMoves[direction].push_back(moves[direction]+position);
    }
    //castling
    /*if((direction==LEFT||direction==RIGHT)&&!isMoved) {
      possibleMoves[direction].push_back(moves[direction].scale(2)+position);
    }*/
  }

  
  return possibleMoves;
}

const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> Pawn:: possibleMoves() const{
  std::array<Pos, NUMBEROFDIRECTIONS> moves;
  std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMoves;

  moves[UP] = Pos(1, 0);
  moves[UP_RIGHT] = Pos(1,1);
  for(int direction = 2; direction < NUMBEROFDIRECTIONS; direction++) { //calculate vector where Knight can jump
    moves[direction] = moves[direction-2].rotateRight(); 
  }

  for (int direction = 0; direction<NUMBEROFDIRECTIONS; direction++) { //calculate moves 
    moves[direction]=moves[direction]+position;
  }

  for (int direction = 0; direction<NUMBEROFDIRECTIONS; direction++) { //calculate moves 
    if(inBoardRange(moves[direction])) {
      if (color==WHITE) {
        if(direction==UP||direction==UP_RIGHT||direction==UP_LEFT) {
          possibleMoves[direction].push_back(moves[direction]);
        }
        if(position.x==1) {
          possibleMoves[UP].push_back(position+Pos(2,0));//let pawns move two fields if they didnt move yet
        } 
      } else {
        if(direction==DOWN||direction==DOWN_RIGHT||direction==DOWN_LEFT) {
          possibleMoves[direction].push_back(moves[direction]);
        }
        if (position.x==6) {
          possibleMoves[DOWN].push_back(position+Pos(-2,0));//let pawns move two fields if they didnt move yet
        }
      }
    }
  }

  return possibleMoves;
}

std::string printRed(const std::string& string) {
  return "\033[31m" + string + "\033[0m";
}

std::string printGreen(const std::string& string) {
  return "\033[32m" +string + "\033[0m";
}




