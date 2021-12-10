#include "bishop.h"
#include "board.h"
#include "move.h"

Bishop::Bishop(Piece::PieceColour colour): Piece{colour}{}

Bishop::Bishop(const Bishop &other) : Piece{other.colour} {}

Piece::PieceType Bishop::getType() {
    return PieceType::Bishop;
}

Piece::PieceColour Bishop::getColour() {
    return colour;
}

bool Bishop::isValidMove(int startRow, char startCol, int endRow, char endCol, Board const & board){
    if(board.getPieceAt(endCol, endRow)->getColour() == colour){
        return false;
    }
    if(endCol - startCol == endRow - startRow || endCol - startCol == startRow - endRow){ // Checks if there is a piece between startRow, startCol and endRow, endCol (diagonally)
        int rowDir = (endRow - startRow > 0) ? 1 : -1;
        char colDir = (endCol - startCol > 0) ? 1 : -1;
        char j = startCol + colDir;
        for(int i = startRow + rowDir; i != endRow; i += rowDir){
            if(board.getPieceAt(j, i)->getType() != Empty){
                return false;
            }
            j += colDir;
        }
        return true;
    }
    return false;
}

std::unique_ptr<Piece> Bishop::make_copy() const {
    auto newPtr = std::make_unique<Bishop>(*this);
    return newPtr;
}

std::vector<Move> Bishop::valid_direction_moves(char file, int rank) const {
    std::vector<Move> directional_moves;
    for (int right = -1; right <= 1; right += 2) {
        for (int up = -1; up <= 1; up += 2) {
            for (int i = 1; inBounds(file + right * i, rank + up * i) ; ++i) {
                directional_moves.emplace_back(file, rank, file + right * i, rank + up * i);
            }
        }
    }
    // // NE direction
    // for (int i = 1; inBounds(file + i, rank + i) ; ++i) {
    //     directional_moves.emplace_back(file, rank, file + i, rank + i);
    // }
    // // SE direction
    // for (int j = 1; inBounds(file + i, rank + i) ; ++j) {
    //     directional_moves.emplace_back(file, rank, file + j, rank - j);
    // }
    // // SW direction
    // for (int k = 1; inBounds(file + i, rank + i) ; ++k) {
    //     directional_moves.emplace_back(file, rank, file - k, rank - k);
    // }
    // // NW direction
    // for (int l = 1; inBounds(file + i, rank + i) ; ++l) {
    //     directional_moves.emplace_back(file, rank, file - l, rank + l);
    // }
    return directional_moves;
}