#include "AI.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int WIN_SCORE = 1000000;
const int LIVE_4 = 10000;
const int LIVE_3 = 1000;
const int LIVE_2 = 100;

AI::AI() {
    std::srand(std::time(0));
}

void AI::init(int color) {
    myColor = color;
    humanColor = (color == PIECE_BLACK) ? PIECE_WHITE : PIECE_BLACK;
    searchDepth = 4;
}

Point AI::think(Board &board) {
    if(board.pieceCount == 0) {
        return {BOARD_SIZE/2, BOARD_SIZE/2, 0};
    }

    Point bestMove = {-1, -1, -2000000000};
    int alpha = -2000000000;
    int beta = 2000000000;

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(!board.isValid(i, j)) continue;
            if(!hasNeighbor(board, i, j)) continue;

            board.putPiece(i, j, myColor);
            int score = alphaBeta(board, searchDepth - 1, alpha, beta, false);
            board.removePiece(i, j);

            if(score > bestMove.score) {
                bestMove.x = i;
                bestMove.y = j;
                bestMove.score = score;
            }
            if(score > alpha) alpha = score;
        }
    }
    return bestMove;
}

int AI::alphaBeta(Board &board, int depth, int alpha, int beta, bool isAI) {
    if(board.checkWin(myColor)) return WIN_SCORE + depth;
    if(board.checkWin(humanColor)) return -WIN_SCORE - depth;
    if(depth == 0) return evaluate(board);

    if(isAI) {
        int maxScore = -2000000000;
        for(int i = 0; i < BOARD_SIZE; i++) {
            for(int j = 0; j < BOARD_SIZE; j++) {
                if(!board.isValid(i, j)) continue;
                if(!hasNeighbor(board, i, j)) continue;

                board.putPiece(i, j, myColor);
                int score = alphaBeta(board, depth - 1, alpha, beta, false);
                board.removePiece(i, j);

                if(score > maxScore) maxScore = score;
                if(maxScore > alpha) alpha = maxScore;
                if(beta <= alpha) return maxScore;
            }
        }
        return maxScore;
    } else {
        int minScore = 2000000000;
        for(int i = 0; i < BOARD_SIZE; i++) {
            for(int j = 0; j < BOARD_SIZE; j++) {
                if(!board.isValid(i, j)) continue;
                if(!hasNeighbor(board, i, j)) continue;

                board.putPiece(i, j, humanColor);
                int score = alphaBeta(board, depth - 1, alpha, beta, true);
                board.removePiece(i, j);

                if(score < minScore) minScore = score;
                if(minScore < beta) beta = minScore;
                if(beta <= alpha) return minScore;
            }
        }
        return minScore;
    }
}

bool AI::hasNeighbor(Board &board, int x, int y) {
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if(i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if(nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE) {
                if(board.map[nx][ny] != PIECE_EMPTY) return true;
            }
        }
    }
    return false;
}

int AI::evaluate(Board &board) {
    int totalScore = 0;
    int dx[4] = {1, 0, 1, 1};
    int dy[4] = {0, 1, 1, -1};

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(board.map[i][j] == PIECE_EMPTY) continue;

            int color = board.map[i][j];
            bool isMe = (color == myColor);

            for(int dir = 0; dir < 4; dir++) {
                int count = 1;
                int emptyEnds = 0;

                int prevX = i - dx[dir];
                int prevY = j - dy[dir];

                bool isStart = false;
                if(prevX < 0 || prevX >= BOARD_SIZE || prevY < 0 || prevY >= BOARD_SIZE) {
                    isStart = true;
                } else if(board.map[prevX][prevY] != color) {
                    isStart = true;
                }

                if(isStart) {
                    int k;
                    for(k = 1; k < 5; k++) {
                        int nx = i + dx[dir] * k;
                        int ny = j + dy[dir] * k;
                        if(nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && board.map[nx][ny] == color) {
                            count++;
                        } else {
                            break;
                        }
                    }

                    if(prevX >= 0 && prevX < BOARD_SIZE && prevY >= 0 && prevY < BOARD_SIZE && board.map[prevX][prevY] == PIECE_EMPTY) {
                        emptyEnds++;
                    }
                    int nextX = i + dx[dir] * k;
                    int nextY = j + dy[dir] * k;
                    if(nextX >= 0 && nextX < BOARD_SIZE && nextY >= 0 && nextY < BOARD_SIZE && board.map[nextX][nextY] == PIECE_EMPTY) {
                        emptyEnds++;
                    }

                    int score = getLineScore(count, emptyEnds, isMe ? 1 : -1);
                    if(isMe) totalScore += score;
                    else totalScore -= score;
                }
            }
        }
    }
    return totalScore;
}

int AI::getLineScore(int count, int emptyEnds, int turn) {
    if(count >= 5) return 100000;
    if(count == 4) {
        if(emptyEnds == 2) return 10000;
        if(emptyEnds == 1) return 1000;
    }
    if(count == 3) {
        if(emptyEnds == 2) return 1000;
        if(emptyEnds == 1) return 100;
    }
    if(count == 2) {
        if(emptyEnds == 2) return 100;
    }
    return 0;
}