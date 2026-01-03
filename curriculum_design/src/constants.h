#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <raylib.h>

const int BOARD_SIZE = 15;
const int CELL_SIZE = 60;
const int MARGIN = 40;
const int SCREEN_WIDTH = CELL_SIZE * (BOARD_SIZE - 1) + MARGIN * 2;
const int SCREEN_HEIGHT = SCREEN_WIDTH + 60;

enum PieceType {
    PIECE_EMPTY = 0,
    PIECE_BLACK = 1,
    PIECE_WHITE = 2
};

struct Point {
    int x;
    int y;
    int score;
};

const Color BOARD_COLOR = {235, 200, 150, 255};
const Color GRID_COLOR = {0, 0, 0, 255};
const Color BLACK_PIECE_COLOR = {10, 10, 10, 255};
const Color WHITE_PIECE_COLOR = {245, 245, 245, 255};
const Color LAST_MOVE_COLOR = {200, 0, 0, 200};

#endif