#include "Board.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

Board::Board(std::vector<std::shared_ptr<Piece>>&& pieces)
{
    for (std::shared_ptr<Piece>& piece : pieces) {
        placeNewPiece(*piece);
    }
}

Board::Board(std::vector<std::shared_ptr<Piece>>& pieces)
{
    for (std::shared_ptr<Piece>& piece : pieces) {
        placeNewPiece(*piece);
    }
}

std::shared_ptr<Piece>& Board::pieceAt(const Pos& position)
{
    return board[position.x][position.y];
}

std::string showPiecesOfColor(bool color, std::vector<std::shared_ptr<Piece>> pieces) {
  std::string result = "";
  for(std::shared_ptr<Piece> piece : pieces) {
    if(piece->color==color) {
      result.append(piece->show() + " ");
    }
  }
  result.append("\n");
  return result;
}

std::string Board::show()
{
    std::string result = "";

    result.append("X\n");
    for (int i = BOARDSIZE - 1; i >= 0; i--) {
        result.append(std::to_string(i) + " ");
        for (int j = 0; j < BOARDSIZE; j++) {
            if (board[i][j] != nullptr) {
                result.append(board[i][j]->show() + " ");
            } else {
                result.append("0 ");
            }
        }
        result.append("\n");
    }
    result.append("  0 1 2 3 4 5 6 7 Y\n\n");
    result.append("taken white Pieces:\n");
    result.append(showPiecesOfColor(WHITE, takenPieces));
    result.append("taken black Pieces:\n");
    result.append(showPiecesOfColor(BLACK, takenPieces));
    return result;
}



void Board::unruledMove(const Move& move)
{
    pastPositions.push_back(board);
    pastMoves.push_back(move);
    pastPositions.push_back(board);
    if (isKing(*move.getPiece())) {
        auto it = std::find(kingPositions[move.getPiece()->color].begin(),
            kingPositions[move.getPiece()->color].end(),
            move.getPiece()->position);
        if (it != kingPositions[move.getPiece()->color].end()) {
            kingPositions[move.getPiece()->color].erase(it);
        }

        kingPositions[move.getPiece()->color].push_back(
            move.getPosition()); // update king position
    }
    pieceAt(move.getPiece()->position) = nullptr;
    pieceAt(move.getPosition()) = move.getPiece()->clone();
    pieceAt(move.getPosition())->position = move.getPosition();
}

void Board::placePiece(Piece& piece)
{
    Move move = Move(piece, piece.position);
    unruledMove(move);
}

void Board::placeNewPiece(Piece& piece)
{
    pastPositions.push_back(board);
    pastMoves.push_back(Move(piece, piece.position));
    if (isKing(piece)) {
        auto it = std::find(kingPositions[piece.color].begin(),
            kingPositions[piece.color].end(), piece.position);
        if (it != kingPositions[piece.color].end()) {
            kingPositions[piece.color].erase(it);
        }

        kingPositions[piece.color].push_back(piece.position); // update king
                                                              // position
    }
    pieceAt(piece.position) = piece.clone();
}

void Board::promote(Pawn& pawn)
{

    std::array<std::shared_ptr<Piece>, 4> options;
    options[0] = Knight(pawn.color, Pos(0, 0)).clone();
    options[1] = Bishop(pawn.color, Pos(0, 0)).clone();
    options[2] = Rook(pawn.color, Pos(0, 0)).clone();
    options[3] = Queen(pawn.color, Pos(0, 0)).clone();
    std::string newPiece;
    std::cout << "choose a piece\n";
    std::cout << "Knight: press " << options[0]->show() << std::endl;
    std::cout << "Rook: press " << options[1]->show() << std::endl;
    std::cout << "Bishop: press " << options[2]->show() << std::endl;
    std::cout << "Queen: press " << options[3]->show() << std::endl;
    std::cin >> newPiece;

    bool matched = false;

    for (int i = 0; i < 4; i++) {
        if (options[i]->SYMBOL == newPiece) {
            Move move = Move(*options[i], pawn.position);
            unruledMove(move);
            matched = true;
        }
    }
    if (matched == false) { // promote to queen as default
        Move move = Move(*options[3], pawn.position);
        unruledMove(move);
    }
}

// moves piece at @move.piece->position to @position if chess rules allow it
// throws @notallowedMoveException
void Board::ruledMove(const Move& move)
{
    if (!move.getPiece()) {
        throw NotAllowedMoveException(std::string("there is no piece\n").c_str());
    }
    const bool enemyColor = !move.getPiece()->color;
    const bool promotion = isPromotion(move);
    bool shortCastle;
    bool longCastle;
    // check if piece can physically move to @position
    std::shared_ptr<Piece> pieceToBeTaken = nullptr;
    bool allowed = false;
    for (int i = 0; i < BOARDSIZE; i++) {
        std::vector<Pos> vec = possibleMovesWithNoPieceInWay(*move.getPiece())[i];
        auto iterator = std::find(vec.begin(), vec.end(), move.getPosition());
        if (iterator != vec.end()) {
            allowed = true;
            break;
        }
    }

    if (allowed) { // move @piece to check if king of @pieces color is in check
        pieceToBeTaken = (pieceAt(move.getPosition())); // keep option to revert move
        if (pieceToBeTaken) {
            takenPieces.push_back(pieceToBeTaken);
        }
        unruledMove(move);
        if (promotion) {
            promote(dynamic_cast<Pawn&>(*pieceAt(move.getPosition())));
        }

    } else if (isShortCastle(move)) {
        castle(SHORT, move);
    } else if (isLongCastle(move)) {
        castle(LONG, move);

    } else if (isEnpassantLeft(move)) {
        enpassantLeft(*move.getPiece());
    } else if (isEnpassantRight(move)) {
        enpassantRight(*move.getPiece());
    } else {
        throw NotAllowedMoveException(std::string("piece ")
                .append(move.getPiece()->show())
                .append(move.getPiece()->position.show())
                .append(" cant move to ")
                .append(move.getPosition().show())
                .append("\n")
                .c_str());
    }

    for (int k = 0; k < kingPositions[pieceAt(move.getPosition())->color].size();
        k++) {
        if (!kingPositions[move.getPiece()->color].empty()) {
            std::optional<Pos> pieceAttackingKing = isCovered(
                kingPositions[move.getPiece()->color][k], !move.getPiece()->color);
            if (pieceAttackingKing.has_value()) {
                Move revert = Move(*pieceAt(move.getPosition()), move.getPiece()->position);
                unruledMove(revert);
                if (pieceToBeTaken) {
                    takenPieces.pop_back();
                    placePiece(*pieceToBeTaken);
                }
                if (promotion) { // revert promotion
                    std::shared_ptr<Piece> pawn = std::shared_ptr<Piece>(
                        Pawn(move.getPiece()->color, move.getPiece()->position).clone());
                    placePiece(*pawn);
                }
                throw NotAllowedMoveException(
                    ("your king would be in check from piece at " + pieceAttackingKing.value().show() + "\n")
                        .c_str());
            }
        }
    }
}

void Board::revertLastMove()
{
    if (!pastPositions.empty()) {
        board = pastPositions.back();
    }
    pastPositions.pop_back();
    pastMoves.pop_back();
}

// the moves @piece can do wihtout jumping over other pieces or taking its own
// pieces
std::array<std::vector<Pos>, NUMBEROFDIRECTIONS>
Board::possibleMovesWithNoPieceInWay(const Piece& piece)
{
    std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> result;
    std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> possibleMoves = piece.possibleMoves();
    for (int i = 0; i < NUMBEROFDIRECTIONS; i++) {
        for (int j = 0; j < possibleMoves[i].size(); j++) {
            Pos move = possibleMoves[i][j];

            bool noPiece = pieceAt(move) == nullptr;

            bool friendlyPiece = noPiece ? false : pieceAt(move)->color == piece.color;

            if (noPiece) {
                if (isPawn(piece)) {
                    if (i == DOWN || i == UP) { // pawns can only move up and down if thers no piece
                        result[i].push_back(move);
                    }
                } else {
                    result[i].push_back(move);
                }

            } else if (friendlyPiece) {
                break;
            } else {
                if (isPawn(piece)) {
                    if (i != DOWN && i != UP) { // pawns can only take diagonally
                        result[i].push_back(move);
                        break;
                    }
                } else {
                    result[i].push_back(move);
                    break;
                }
            }
        }
    }
    return result;
}
void Board::showPossibleMoves(const Piece& piece)
{
    std::array<std::vector<Pos>, NUMBEROFDIRECTIONS> v = possibleMovesWithNoPieceInWay(piece);
    for (int i = 0; i < NUMBEROFDIRECTIONS; i++) {
        for (Pos pair : v[i]) {
            std::cout << pair.show() << "\n";
        }
    }
}

bool Board::isPromotion(const Move& move)
{
    if (isPawn(*move.getPiece())) {
        if (move.getPiece()->color == WHITE && move.getPosition().x == BOARDSIZE - 1) {
            return true;
        } else if (move.getPiece()->color == BLACK && move.getPosition().x == 0) {
            return true;
        }
    }
    return false;
}

// returns position of piece of @color that covers @position
// if no piece of @color covers @position return nullopt
std::optional<Pos> Board::isCovered(const Pos& position, const bool& color)
{
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            if (board[i][j] != nullptr && board[i][j]->color == color && isMovePossible(possibleMovesWithNoPieceInWay(*board[i][j]), position)) {
                return Pos(i, j);
            }
        }
    }
    return std::nullopt;
}

bool Board::isLongCastle(const Move& move)
{
    if (isKing(*move.getPiece()) && move.getPiece()->position.y == move.getPosition().y + 2) {
        return true;
    } else {
        return false;
    }
}

bool Board::isShortCastle(const Move& move)
{
    if (isKing(*move.getPiece()) && move.getPiece()->position.y == move.getPosition().y - 2) {
        return true;
    } else {
        return false;
    }
}

void Board::castle(const bool& direction, const Move& move)
{
    bool castle = false;
    if (direction == SHORT) {
        if (!pieceAt(Pos(move.getPiece()->position.x, BOARDSIZE - 1))->isMoved && !move.getPiece()->isMoved) {
            for (int i = move.getPiece()->position.y + 1; i < BOARDSIZE - 1; i++) {
                if (isEmpty(Pos(move.getPiece()->position.x, i))) {
                    if (i - 1 < move.getPiece()->position.y + 2) { //-1 to check if king is in check. Castling is
                                                                   // not allowed if King is in Check
                        if (isCovered(Pos(move.getPiece()->position.x, i - 1),
                                !move.getPiece()->color)) {
                            throw NotAllowedMoveException(
                                ("cant castle." + Pos(move.getPiece()->position.x, i - 1).show() + " is covered \n")
                                    .c_str());
                        }
                    }
                    castle = true;

                } else {
                    throw NotAllowedMoveException(
                        ("cant castle." + Pos(move.getPiece()->position.x, i).show() + " isn't empty \n")
                            .c_str());
                }
            }
        } else {
            throw NotAllowedMoveException(
                ("cant castle. you already moved one of the two pieces\n"));
        }
        if (castle) {
            Move rookMove = Move(
                *pieceAt(Pos(move.getPiece()->position.x, BOARDSIZE - 1)),
                Pos(move.getPiece()->position.x, move.getPiece()->position.y + 1));
            unruledMove(rookMove);
            Move kingMove = move;
            unruledMove(kingMove);
        }
    } else {
        if (!pieceAt(Pos(move.getPiece()->position.x, 0))->isMoved && !pieceAt(move.getPiece()->position)->isMoved) {
            for (int i = move.getPiece()->position.y - 1; i > 0; i--) {
                if (isEmpty(Pos(move.getPiece()->position.x, i))) {
                    if (i > move.getPiece()->position.y - 2) {
                        if (isCovered(Pos(move.getPiece()->position.x, i),
                                !pieceAt(move.getPiece()->position)->color)) {
                            throw NotAllowedMoveException(
                                ("cant castle." + Pos(move.getPiece()->position.x, i).show() + " is covered \n")
                                    .c_str());
                        }
                    }
                    castle = true;
                } else {
                    throw NotAllowedMoveException(
                        ("cant castle." + Pos(move.getPiece()->position.x, i).show() + " isn't empty \n")
                            .c_str());
                }
            }
        } else {
            throw NotAllowedMoveException(
                ("cant castle. you already moved one of the two pieces\n"));
        }
        if (castle) {
            Move rookMove = Move(
                *pieceAt(Pos(move.getPiece()->position.x, 0)),
                Pos(move.getPiece()->position.x, move.getPiece()->position.y - 1));
            unruledMove(rookMove);
            Move kingMove = move;
            unruledMove(kingMove);
        }
    }
}

const bool Board::operator==(const Board& other) const
{
    for (int row = 0; row < BOARDSIZE; row++) {
        for (int column = 0; column < BOARDSIZE; column++) {
            std::shared_ptr<Piece> thisPiece = board[row][column];
            std::shared_ptr<Piece> otherPiece = other.board[row][column];
            if (thisPiece != otherPiece) { // check if pointers are euqual (both nullpointer)
                if (thisPiece == nullptr || otherPiece == nullptr) { // check if one of them is nullpointer
                    return false;
                } else {
                    if (!(*board[row][column] == *other.board[row][column])) { // check if Pieces are equal
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool Board::isEmpty(const Pos& position)
{
    if (pieceAt(position) == nullptr) {
        return true;
    } else {
        return false;
    }
}

bool isMovePossible(
    const std::array<std::vector<Pos>, NUMBEROFDIRECTIONS>& possibleMoves,
    const Pos& move)
{
    bool isPossible = false;
    for (int i = 0; i < NUMBEROFDIRECTIONS; i++) {
        if (possibleMoves[i].empty()) {
            continue;
        }
        for (int j = 0; j < possibleMoves[i].size(); j++) {
            if (possibleMoves[i][j] == move) {
                return true;
            }
        }
    }
    return isPossible;
}

bool isKing(const Piece& piece)
{
    if (piece.SYMBOL == "O") {
        return true;
    } else {
        return false;
    }
}

bool isPawn(const Piece& piece)
{
    if (piece.SYMBOL == "P") {
        return true;
    } else {
        return false;
    }
}

const bool isPieceInFront(const Piece& piece, const Piece& other)
{
    Pos distance = piece.position - other.position;
    if (piece.color == WHITE) {
        if (distance.x < 0) {
            return true;
        } else {
            return false;
        }
    } else {
        if (distance.x > 0) {
            return true;
        } else {
            return false;
        }
    }
}

bool Board::isEnpassantLeft(const Move& move)
{
    if (!isPawn(*move.getPiece())) {
        return false;
    }
    if (pastMoves.empty()) {
        return false;
    } else {
        Move lastMove = pastMoves.back();
        if (isPawn(*lastMove.getPiece()) && lastMove.getPiece()->color != move.getPiece()->color && abs(lastMove.vec().x) > 1) {
            if (move.getPiece()->color == WHITE && lastMove.getPiece()->position == move.getPiece()->position + Pos(2, -1) && move.getPosition() == move.getPiece()->position + Pos(1, -1)) {
                return true;
            } else if (move.getPiece()->color == BLACK && lastMove.getPiece()->position == move.getPiece()->position + Pos(-2, -1) && move.getPosition() == move.getPiece()->position + Pos(-1, -1)) {
                return true;
            }
        }
    }
    return false;
}

bool Board::isEnpassantRight(const Move& move)
{
    if (!isPawn(*move.getPiece())) {
        return false;
    }
    if (pastMoves.empty()) {
        return false;
    } else {
        Move lastMove = pastMoves.back();
        if (isPawn(*lastMove.getPiece()) && lastMove.getPiece()->color != move.getPiece()->color && abs(lastMove.vec().x) > 1) {
            if (move.getPiece()->color == WHITE && lastMove.getPiece()->position == move.getPiece()->position + Pos(2, 1) && move.getPosition() == move.getPiece()->position + Pos(1, 1)) {
                return true;
            } else if (move.getPiece()->color == BLACK && lastMove.getPiece()->position == move.getPiece()->position + Pos(-2, 1) && move.getPosition() == move.getPiece()->position + Pos(-1, 1)) {
                return true;
            }
        }
    }
    return false;
}

void Board::enpassantLeft(Piece& pawn)
{
    if (pawn.color == WHITE) {
        pieceAt(pawn.position + Pos(0, -1)) = nullptr;
        unruledMove(Move(pawn, pawn.position + Pos(1, -1)));
    } else {
        pieceAt(pawn.position + Pos(0, -1)) = nullptr;
        unruledMove(Move(pawn, pawn.position + Pos(-1, -1)));
    }
}

void Board::enpassantRight(Piece& pawn)
{
    if (pawn.color == WHITE) {
        pieceAt(pawn.position + Pos(0, 1)) = nullptr;
        unruledMove(Move(pawn, pawn.position + Pos(1, 1)));
    } else {
        pieceAt(pawn.position + Pos(0, 1)) = nullptr;
        unruledMove(Move(pawn, pawn.position + Pos(-1, 1)));
    }
}
