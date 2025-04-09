#include <array>
#include <memory>
#include <optional>
#include <string>
#include <Move.h>
#include <vector>


const int BOARDSIZE = 8;
const bool WHITE = false;
const bool BLACK = true;
const bool LONG = true;
const bool SHORT = false;
class Board {
  public:
    Board(std::vector<std::shared_ptr<Piece>>&& pieces);
    Board(std::vector<std::shared_ptr<Piece>>& pieces);

    std::array<std::array<std::shared_ptr<Piece>, BOARDSIZE>, BOARDSIZE> board; //(0,0)=> a1, (0,1)=> a2, (7,7)=> h8

    std::vector<std::array<std::array<std::shared_ptr<Piece>, BOARDSIZE>, BOARDSIZE>> pastPositions;
    std::vector<Move> pastMoves;
    std::vector<std::shared_ptr<Piece>> takenPieces;

    //move @piece to any @position
    void unruledMove(const Move& move);
    //move @piece based on chess rules to @position
    void ruledMove(const Move& move);
    //place @piece on its position on the board
    void placePiece(Piece& piece);
    //place @piece and set isMoved to true
    void placeNewPiece(Piece& piece);    
    std::string show();
    void showPossibleMoves(const Piece& piece);
    std::shared_ptr<Piece>& pieceAt(const Pos& position);
    bool isEmpty(const Pos& position);
    const bool operator==(const Board& other) const;
    void revertLastMove();
  private: 
    std::optional<Pos> isCovered(const Pos& position, const bool& color);
    bool isEnpassantLeft(const Move& move);
    bool isEnpassantRight(const Move& move);
    std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMovesWithNoPieceInWay(const Piece& piece);
    std::array<std::vector<Pos>, 2> kingPositions;    
    bool isPromotion(const Move& move);
    bool isShortCastle(const Move& move);
    bool isLongCastle(const Move& move);
    void promote(Pawn& pawn);
    void shortCastle(Piece& king);
    void longCastle(Piece& king);     
    void castle(const bool& direction, const Move& move);
    void enpassantLeft(Piece& piece);
    void enpassantRight(Piece& piece);
};



bool isMovePossible(const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS>& possibleMoves, const Pos& move);

bool isKing(const Piece& piece);

bool isPawn(const Piece& piece);

bool isPiece(const Piece& piece);