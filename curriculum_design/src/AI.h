#ifndef AI_H
#define AI_H

#include "Board.h"

class AI {
public:
    AI();
    void init(int aiColor);

    Point think(Board &board);

private:
    int myColor;
    int humanColor;
    int searchDepth;

    int alphaBeta(Board &board, int depth, int alpha, int beta, bool isAI);

    int evaluate(Board &board);

    bool hasNeighbor(Board &board, int x, int y);
    int getLineScore(int count, int emptyEnds, int turn);
};

#endif