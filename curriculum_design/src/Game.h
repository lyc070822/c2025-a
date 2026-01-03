#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "AI.h"
#include "Constants.h"

class Game {
public:
    Game();
    void run();

private:
    Board board;
    AI ai;

    bool isGameOver;
    int winner;
    int turn;
    Point lastMove;

    void update();
    void handleInput();
    void reset();


    void draw();
    void drawBoard();
    void drawPieces();
};

#endif
