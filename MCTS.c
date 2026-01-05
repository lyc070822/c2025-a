#include <float.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define EMPTY 0
#define BLACK 1
#define WHITE 2
#define BOARD_SIZE (15+1)
#define EXPEND_SIZE 10

typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];
    int player;
} State;

typedef struct {
    int x;
    int y;
} Move;

typedef struct node{
    int board[BOARD_SIZE][BOARD_SIZE];
    struct node* child[225];
    int child_count;
    struct node* parent;
    int visit_count;
    int win_count;
    int player;
    Move move;
} Node;

Node * initNode(Move move);

Node * selectNode(Node * root);

double computeUCT(Node* node);

State state;

void make_move(Move move);

void print_board(void);

Node * expandNode(Node * node);

Move get_legal_move(int board[BOARD_SIZE][BOARD_SIZE]);

int rollout(Node * n);

void backpropagate(Node * node, int winner);

Move get_best_move(Node * root);
int winChecker(State s, Move move);
int main() {
    srand(time(NULL));

    for (int j=0;j < BOARD_SIZE; j++) state.board[0][j] = j;
    for (int i = 1; i < BOARD_SIZE; i++) {
        state.board[i][0] = i;
        for (int j = 1; j < BOARD_SIZE; j++) {
            state.board[i][j] = 0;
        }
    }
    state.player = BLACK;



    print_board();

    while (1) {
        // Player move
        Move myMove;
        scanf("%d %d", &myMove.x, &myMove.y);
        make_move(myMove);

        if (winChecker(state, myMove) == BLACK) {
            system("cls");
            print_board();
            printf("You win!\n");
            return 0;
        }

        system("cls");
        print_board();

        Node* root = initNode(myMove);
        Node* current_node = root;

        for (int i = 0; i < 10000; i++) { // increased for smarter AI
            current_node = selectNode(current_node);
            if (current_node->visit_count == 0) {
                int winner = rollout(current_node);
                backpropagate(current_node, winner);
            } else {
                current_node = expandNode(current_node);
                int winner = rollout(current_node);
                backpropagate(current_node, winner);
            }
            current_node = root;
        }

        Move aiMove = get_best_move(root);
        make_move(aiMove);

        if (winChecker(state, aiMove) == WHITE) {
            system("cls");
            print_board();
            printf("AI wins!\n");
            return 0;
        }

        system("cls");
        print_board();
    }

}

void print_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%2d ", state.board[i][j]);
        }
        printf("\n");
    }
}

void make_move(Move move) {
    state.board[move.x][move.y] = state.player;
    state.player = 3-state.player;
}

Node* initNode(Move move) {
    Node* node = (Node*)malloc(sizeof(Node));

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            node->board[i][j] = state.board[i][j];
        }
    }
    for (int i = 0; i < 225; i++) {
        node->child[i] = NULL;
    }
    node->parent = NULL;
    node->visit_count=0;
    node->child_count=0;
    node->win_count=0;
    node->move=move;
    node->player=state.player;
    return node;
}


Node* selectNode(Node* root) {
    Node* cur = root;
    while (cur->child_count > 0) {
        // 优先返回任一未访问(child->visit_count == 0) 的子节点
        for (int i = 0; i < cur->child_count; i++) {
            if (cur->child[i]->visit_count == 0) return cur->child[i];
        }
        // 否则按 UCT 选择
        double best = -DBL_MAX;
        int best_idx = 0;
        for (int i = 0; i < cur->child_count; i++) {
            double val = computeUCT(cur->child[i]);
            if (val > best) {
                best = val;
                best_idx = i;
            }
        }
        cur = cur->child[best_idx];
    }
    return cur;
}

double computeUCT(Node* node) {
    // 根节点没有 parent，直接返回一个极小值避免崩溃
    if (node->parent == NULL) return -DBL_MAX;

    // 未访问节点给一个极大值，让它被优先探索
    if (node->visit_count == 0) return DBL_MAX;

    // 如果父节点还没被访问，避免除以 0
    if (node->parent->visit_count == 0) return 0;

    double win_rate = (double)node->win_count / (double)node->visit_count;
    double c = 0.8;
    double parent_visits = (double)node->parent->visit_count;

    double explore = sqrt(log(parent_visits + 1) / (double)node->visit_count); // 加1避免log(0)
    double u = win_rate + c * explore;

    return u;
}

Node* expandNode(Node* node) {
    Move mv;
    int tries = 0;
    while (1) {
        mv = get_legal_move(node->board);
        if (mv.x == 0 && mv.y == 0) return node; // 无法扩展
        int duplicate = 0;
        for (int k = 0; k < node->child_count; k++) {
            if (node->child[k]->move.x == mv.x && node->child[k]->move.y == mv.y) { duplicate = 1; break; }
        }
        if (!duplicate) break;
        if (++tries > 500) return node;
    }

    Node* child = (Node*)malloc(sizeof(Node));
    if (!child) return NULL;
    // 复制父节点棋盘到子节点并应用该落子
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            child->board[i][j] = node->board[i][j];

    child->board[mv.x][mv.y] = node->player;

    // 初始化 child 字段
    for (int i = 0; i < 225; i++) child->child[i] = NULL;
    child->child_count = 0;
    child->parent = node;
    child->visit_count = 0;
    child->win_count = 0;
    child->move = mv;
    // 下完 mv 后，轮到另一方
    child->player = 3 - node->player;

    // 将 child 加入父节点列表
    node->child[node->child_count] = child;
    node->child_count++;

    return child;
}
Move get_legal_move(int board[BOARD_SIZE][BOARD_SIZE]) {
    Move moves[225];
    int count = 0;
    for (int i = 1; i < BOARD_SIZE; i++) {
        for (int j = 1; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY) {
                moves[count].x = i;
                moves[count].y = j;
                count++;
            }
        }
    }
    Move legal_move;
    if (count == 0) {
        legal_move.x = 0;
        legal_move.y = 0;
        return legal_move;
    }
    legal_move = moves[rand() % count];
    return legal_move;
}



int rollout(Node* node) {
    State s;
    s.player = node->player;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            s.board[i][j] = node->board[i][j];

    while (1) {
        Move mv = get_legal_move(s.board);
        if (mv.x == 0 && mv.y == 0) return 0;
        s.board[mv.x][mv.y] = s.player;
        int w = winChecker(s, mv);
        if (w != 0) return w;
        s.player = 3 - s.player;
    }
}
void backpropagate(Node * node, int winner) {
    while (node != NULL) {
        node->visit_count++;
        int mover = 3 - node->player;
        if (winner == mover) node->win_count++;
        node = node->parent;
    }
}

Move get_best_move(Node * root) {
    Move best_move = {0,0};
    if (root->child_count == 0) return best_move;

    int best_idx = 0;
    int best_visits = -1;
    for (int i = 0; i < root->child_count; i++) {
        if (root->child[i]->visit_count > best_visits) {
            best_visits = root->child[i]->visit_count;
            best_idx = i;
        }
    }
    best_move = root->child[best_idx]->move;
    return best_move;
}

int winChecker(State s, Move move) {
    int player = s.board[move.x][move.y];
    if (player == EMPTY) return 0;
    int dir[4][2] = {
        {0, 1},
        {1, 0},
        {1, 1},
        {1, -1}
    };

    for (int d = 0; d < 4; d++) {
        int count = 1;
        int dx = dir[d][0], dy = dir[d][1];

        int x = move.x + dx, y = move.y + dy;
        while (x > 0 && x < BOARD_SIZE && y > 0 && y < BOARD_SIZE && s.board[x][y] == player) {
            count++;
            x += dx;
            y += dy;
        }

        x = move.x - dx;
        y = move.y - dy;
        while (x > 0 && x < BOARD_SIZE && y > 0 && y < BOARD_SIZE && s.board[x][y] == player) {
            count++;
            x -= dx;
            y -= dy;
        }
        if (count >= 5)
            return player;
    }
    return 0;
}
