#include <stdio.h>
#include <windows.h>
#include <conio.h>
void printMaze(char[][6]);
#define exit_x 1
#define exit_y 5
int main() {
    char maze[6][6]= {
        "######",
        "#O # E",
        "# ## #",
        "#  # #",
        "##   #",
        "######"
    };
    int x0=1,y0=1;
    int x1=x0,y1=y0;
    while (1) {
        x0=x1;
        y0=y1;
        system("cls");
        printMaze(maze);
        char n;
        n=getch();
        if (n=='w'||n=='W') x1--;
        else if (n=='s'||n=='S') x1++;
        else if (n=='d'||n=='D') y1++;
        else if (n=='a'||n=='A') y1--;
        if (maze[x1][y1]=='#') {
            x1=x0;
            y1=y0;
        }
        else {
            maze[x0][y0]=' ';
            maze[x1][y1]='0';
        }
        if (x1==exit_x && y1==exit_y) {
            system("cls");
            printMaze(maze);
            printf("you win!!!");
            return 0;
        }
    }
}
void printMaze(char maze[][6]) {
    printf("Welcome to the maze game!!!\n");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%c",maze[i][j]);
        }
        printf("\n");
    }
}