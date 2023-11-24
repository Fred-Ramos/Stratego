#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

#include <Qlist>

class Board{ //Container for the pieces
public:
    //constructor
    Board();

    //getters/setters
    QList<Piece*> getPieces();

    //public methods
    void placePieces(int x, int y, int cols, int rows);
private:
    QList<Piece*> pieces;
};

#endif // BOARD_H
