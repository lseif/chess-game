#include "Tests.h"
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <sstream>

void showPossibleMoves(std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> v) {
  for(int i = 0; i< NUMBEROFDIRECTIONS; i++) {
    for (Pos pair : v[i]) {
    std::cout<<i <<": " << pair.show() << "\n";
  }
  }
  
}

std::string getline() {
  std::string str;
  std::getline(std::cin, str);
  return str;
}

bool inputBool() {
  while (true) {
    bool x = false;
    std::cout << "press 1 for yes or 0 for no:\n";
    std::istringstream iss(getline());
    iss >> x >> std::ws;
    if(iss.fail() || !iss.eof()) {
      std::cout << "thats no valid input \n";
      continue;
    } else {
      return x;
    }
  }
}

Pos inputPosition() {
  while (true) {
    int x;
    int y;
    std::cout << "give position of piece to move \n";
    std::cout << "x:";
    std::istringstream iss(getline());
    iss >> x >> std::ws;
    if(iss.fail() || !iss.eof()) {
      std::cout << "thats no valid input \n";
      continue;
    }
    iss.clear();
    std::cout << "y:";
    iss.str(getline());
    iss >> y >> std::ws;
    if(iss.fail() || !iss.eof()) {
      std::cout << "thats no valid input \n";
      continue;
    }
    Pos position = Pos(x, y);
    if(position.inRange(Pos(0,0), Pos(BOARDSIZE, BOARDSIZE))) {
      return position;
    } else {
      std::cout << "thats no valid position. Position has to be in range 0-7. \n";
      continue;;
    }
  }
}

void play(Board& b) {
  std::cout << "before you begin to play, do you want to allow taking back bad moves?\n";
  bool allowTakingBack = inputBool();
  std::cout << "\n";
  std::cout << b.show();
  bool whosTurn = WHITE;
  bool end = false;
  while(!end) {
    if(whosTurn==WHITE) {
      std::cout << "whites Turn\n";
    } else {
      std::cout << "blacks Turn\n";
    }
    Pos piece = inputPosition();
    if (b.isEmpty(piece)) {
      std::cout << "theres no piece at " << piece.show() << " \n";
      continue;
    } else if (b.pieceAt(piece)->color!=whosTurn) {
      std::cout << "thats your opponents piece\n";
      continue;
    }

    Pos position = inputPosition();
    try {
      Move move = Move(*b.pieceAt(piece), position);
      b.ruledMove(move);
      std::cout << b.show();
      if(allowTakingBack) {
        bool takeBack;
        std::cout << "revert this move?\n";
        takeBack = inputBool();
        if (takeBack) {
          b.revertLastMove();
          std::cout<< b.show();
        } else {
          whosTurn = !whosTurn;
        }
      } else {
        whosTurn= !whosTurn;
      }
      
    } catch(const std::runtime_error& exception) {
      std::cout << exception.what();
      std::cout << "do something else \n";
    } 
    
    
  }
}

int main() {
  tests();
  Board b = startPosition();
  play(b);
 
  return 0;
}


