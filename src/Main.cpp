#include "Tests.h"
#include <iostream>
#include <stdexcept>

void showPossibleMoves(std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> v) {
  for(int i = 0; i< NUMBEROFDIRECTIONS; i++) {
    for (Pos pair : v[i]) {
    std::cout<<i <<": " << pair.show() << "\n";
  }
  }
  
}

void play(Board& b) {
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
    if(piece.x<0||piece.y>7) {
      std::cout << "thats no valid position. Position has to be in range 0-7. \n";
      continue;
    } else if (b.isEmpty(piece)) {
      //std::cout << "theres no piece\n";
      //continue;
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
      whosTurn = !whosTurn;
    } catch(const std::runtime_error& exception) {
      std::cout << exception.what();
      std::cout << "do something else \n";
    } 
    
    std::cout << b.show();
    //std::cout << "you want to end? press 1 else press 0\n";
    //std::cin >> end;
    
  }
}

int main() { //vector to safe positions and move back
  tests();
  //error (0,1) (0,3)
  Board b = kingCheckPosition();
  play(b);
  /*std::cout << b.show();
  showPossibleMoves(b.pieceAt(Pos(0,7))->possibleMoves());

  std::cout << b.show() << "\n";
  b.showPossibleMoves(*b.pieceAt(Pos(0, 1)));
  Move move = Move(*b.pieceAt(Pos(0, 1)), Pos(2,2));
  b.ruledMove(move);
  std::cout << b.show() << "\n";
  */
  return 0;
}


