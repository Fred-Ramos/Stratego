 #ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

#include <Qlist>

class Board{ //Container for the pieces
public:
    //constructor
    Board();

    //setters
    void addPiece(Piece* piece);

    //getters
    QList<Piece*> getPieces();

    //public methods
    void placePieces(int x, int y);
private:
    QList<Piece*> pieces;
};

#endif // BOARD_H
