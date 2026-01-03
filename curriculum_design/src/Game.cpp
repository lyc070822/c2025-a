#include "Game.h"

Game::Game() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Gomoku - AI Challenge");
    SetTargetFPS(60);
    reset();
}

void Game::reset() {
    board.init();
    ai.init(PIECE_WHITE);

    isGameOver = false;
    winner = 0;
    turn = PIECE_BLACK;
    lastMove = {-1, -1, 0};
}

void Game::run() {
    while (!WindowShouldClose()) {
        update();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        draw();
        EndDrawing();
    }
    CloseWindow();
}

void Game::update() {
    if (isGameOver) {
        if (IsKeyPressed(KEY_R)) {
            reset();
        }
        return;
    }

    if (turn == PIECE_BLACK) {
        handleInput();
    } else {
        Point move = ai.think(board);
        if (move.x != -1) {
            board.putPiece(move.x, move.y, PIECE_WHITE);
            lastMove = move;

            if (board.checkWin(PIECE_WHITE)) {
                isGameOver = true;
                winner = PIECE_WHITE;
            } else if (board.isFull()) {
                isGameOver = true;
                winner = 0;
            } else {
                turn = PIECE_BLACK;
            }
        }
    }
}

void Game::handleInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse = GetMousePosition();

        int col = (int)((mouse.x - MARGIN + CELL_SIZE / 2) / CELL_SIZE);
        int row = (int)((mouse.y - MARGIN + CELL_SIZE / 2) / CELL_SIZE);

        if (board.isValid(col, row)) {
            board.putPiece(col, row, PIECE_BLACK);
            lastMove = {col, row, 0};

            if (board.checkWin(PIECE_BLACK)) {
                isGameOver = true;
                winner = PIECE_BLACK;
            } else {
                turn = PIECE_WHITE;
            }
        }
    }
}

void Game::draw() {
    drawBoard();
    drawPieces();

    DrawRectangle(0, SCREEN_WIDTH, SCREEN_WIDTH, 60, LIGHTGRAY);

    if (!isGameOver) {
        if (turn == PIECE_BLACK) {
            DrawText("Your Turn (Black)", 20, SCREEN_WIDTH + 20, 20, BLACK);
        } else {
            DrawText("AI is Thinking...", 20, SCREEN_WIDTH + 20, 20, DARKGRAY);
        }
    } else {
        if (winner == PIECE_BLACK) // 修改
            DrawText("YOU WIN! Press 'R' to Restart", 20, SCREEN_WIDTH + 20, 20, DARKGREEN);
        else if (winner == PIECE_WHITE) // 修改
            DrawText("AI WINS! Press 'R' to Restart", 20, SCREEN_WIDTH + 20, 20, RED);
        else
            DrawText("DRAW! Press 'R' to Restart", 20, SCREEN_WIDTH + 20, 20, BLUE);
    }
}

void Game::drawBoard() {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_WIDTH, BOARD_COLOR);

    for (int i = 0; i < BOARD_SIZE; i++) {
        DrawLine(MARGIN + i * CELL_SIZE, MARGIN,
                 MARGIN + i * CELL_SIZE, MARGIN + (BOARD_SIZE - 1) * CELL_SIZE, GRID_COLOR);
        DrawLine(MARGIN, MARGIN + i * CELL_SIZE,
                 MARGIN + (BOARD_SIZE - 1) * CELL_SIZE, MARGIN + i * CELL_SIZE, GRID_COLOR);
    }

    int stars[] = {3, 7, 11};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
             DrawCircle(MARGIN + stars[i] * CELL_SIZE, MARGIN + stars[j] * CELL_SIZE, 5, GRID_COLOR);
        }
    }

    if(!isGameOver && turn == PIECE_BLACK) {
        Vector2 mouse = GetMousePosition();
        int col = (int)((mouse.x - MARGIN + CELL_SIZE / 2) / CELL_SIZE);
        int row = (int)((mouse.y - MARGIN + CELL_SIZE / 2) / CELL_SIZE);
        if(board.isValid(col, row)) {
            DrawCircle(MARGIN + col * CELL_SIZE, MARGIN + row * CELL_SIZE, 6, GRAY);
        }
    }
}

void Game::drawPieces() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int p = board.getPiece(i, j);
            if (p != PIECE_EMPTY) {
                int cx = MARGIN + i * CELL_SIZE;
                int cy = MARGIN + j * CELL_SIZE;

                DrawCircle(cx + 3, cy + 3, CELL_SIZE / 2 - 2, {0,0,0,100});

                if (p == PIECE_BLACK) {
                    DrawCircle(cx, cy, CELL_SIZE / 2 - 2, BLACK_PIECE_COLOR);
                } else {
                    DrawCircle(cx, cy, CELL_SIZE / 2 - 2, WHITE_PIECE_COLOR);
                }
            }
        }
    }

    if (lastMove.x != -1) {

        int cx = MARGIN + lastMove.x * CELL_SIZE;
        int cy = MARGIN + lastMove.y * CELL_SIZE;
        DrawCircleLines(cx, cy, CELL_SIZE/2, LAST_MOVE_COLOR);
        DrawCircle(cx, cy, 4, LAST_MOVE_COLOR);
    }
}