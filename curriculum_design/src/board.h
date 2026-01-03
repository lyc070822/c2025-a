#ifndef BOARD_H
#define BOARD_H

#include "Constants.h"

class Board {
public:
    int map[BOARD_SIZE][BOARD_SIZE];
    int pieceCount;

    Board();

    void init();

    bool isValid(int x, int y);

    void putPiece(int x, int y, int color);
    void removePiece(int x, int y);

    int getPiece(int x, int y);

    bool checkWin(int color);
    bool isFull();
};

#endif