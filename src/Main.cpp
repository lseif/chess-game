#include "Tests.h"
#include <iostream>
#include <ostream>
#include <stdexcept>

void showPossibleMoves(std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> v) {
  for(int i = 0; i< NUMBEROFDIRECTIONS; i++) {
    for (Pos pair : v[i]) {
    std::cout<<i <<": " << pair.show() << "\n";
  }
  }
  
}

void play(Board& b) {
  bool allowTakingBack = false;
  std::cout << "before you begin to play, do you want to allow taking back bad moves?\n Press 1 for yes or 0 for no: ";
  std::cin >> allowTakingBack;
  std::cout << "\n";
  std::cout << b.show();
  bool whosTurn = WHITE;
  bool end = false;
  while(!end) {
    int x;
    int y;
    std::pair<int, int> move;
    if(whosTurn==WHITE) {
      std::cout << "whites Turn\n";
    } else {
      std::cout << "blacks Turn\n";
    }
    std::cout << "give position of piece to move \n";
    std::cout << "x:";
    std::cin >> x;
    std::cout << "Y:";
    std::cin >> y;
    Pos piece = Pos(x,y);
    if(!piece.inRange(Pos(0,0), Pos(BOARDSIZE, BOARDSIZE))) {
      std::cout << "thats no valid position. Position has to be in range 0-7. \n";
      continue;
    } else if (b.isEmpty(piece)) {
      std::cout << "theres no piece\n";
      continue;
    } else if (b.pieceAt(piece)->color!=whosTurn) {
      std::cout << "thats your opponents piece\n";
      continue;
    }
    std::cout << "where should the piece move?\n";
    std::cout << "x:";
    std::cin >> x;
    std::cout << "Y:";
    std::cin >> y;
    
    try {
      Move move = Move(*b.pieceAt(piece), Pos(x, y));
      b.ruledMove(move);
      std::cout << b.show();
      if(allowTakingBack) {
        bool takeBack;
        std::cout << "revert this move?\n Press 1 for yes or 0 for no: ";
        std::cin >> takeBack;
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

int main() { //vector to safe positions and move back
  tests();
  Board b = startPosition();
  play(b);
 
  return 0;
}


