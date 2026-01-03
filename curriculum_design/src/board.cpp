#include "Board.h"

Board::Board() {
    init();
}

void Board::init() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            map[i][j] = PIECE_EMPTY;
        }
    }
    pieceCount = 0;
}

bool Board::isValid(int x, int y) {
    if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) return false;
    return map[x][y] == PIECE_EMPTY;
}

void Board::putPiece(int x, int y, int color) {
    if(isValid(x, y)) {
        map[x][y] = color;
        pieceCount++;
    }
}

void Board::removePiece(int x, int y) {
    map[x][y] = PIECE_EMPTY;
    pieceCount--;
}

int Board::getPiece(int x, int y) {
    if(x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) return -1;
    return map[x][y];
}

bool Board::checkWin(int color) {
    int dx[4] = {1, 0, 1, 1};
    int dy[4] = {0, 1, 1, -1};

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(map[i][j] != color) continue;

            for(int dir = 0; dir < 4; dir++) {
                int count = 1;
                for(int k = 1; k < 5; k++) {
                    int nx = i + dx[dir] * k;
                    int ny = j + dy[dir] * k;
                    if(getPiece(nx, ny) == color) {
                        count++;
                    } else {
                        break;
                    }
                }
                if(count == 5) return true;
            }
        }
    }
    return false;
}

bool Board::isFull() {
    return pieceCount >= BOARD_SIZE * BOARD_SIZE;
}