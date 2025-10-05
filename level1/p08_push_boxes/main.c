/*
# ：墙
@ ：玩家 Man
$ ：箱子 Box
. ：箱子目标位置 Target
*/
#include <stdio.h>
#include <windows.h>
#include <conio.h>
typedef struct {
    int x;
    int y;
} Pos;
#define ROW 7
#define COL 7
void printMap(char a[][COL+2]);
int main() {
    Pos posMan0,posMan1;
    Pos posBox;
    Pos posTarget;
    FILE *fp=fopen("map2.txt","r");
    char map[ROW][COL+2];
    int count=0;
    for (int i=0;i<ROW;i++) {
        fgets(map[i],COL+2,fp);
    }
    fclose(fp);
    for (int i=0;i<ROW;i++) {
        for (int j=0;j<COL+1;j++) {
            if (map[i][j]=='@') {
                posMan0.x=i;
                posMan0.y=j;
                posMan1=posMan0;
            }
            else if (map[i][j]=='$') {
                posBox.x=i;
                posBox.y=j;
            }
            else if (map[i][j]=='.') {
                posTarget.x=i;
                posTarget.y=j;
            }
        }
    }
    printMap(map);
    int score=0;
    while (1) {
        score++;
        posMan0.x=posMan1.x;
        posMan0.y=posMan1.y;
        char n;
        n=getch();
        if (n=='w'||n=='W') posMan1.x--;
        else if (n=='s'||n=='S') posMan1.x++;
        else if (n=='d'||n=='D') posMan1.y++;
        else if (n=='a'||n=='A') posMan1.y--;
        if (map[posMan1.x][posMan1.y]=='#') {
            posMan1.x=posMan0.x;
            posMan1.y=posMan0.y;
            score--;
        }
        else if (map[posMan1.x][posMan1.y]==' ') {
            map[posMan1.x][posMan1.y]='@';
            map[posMan0.x][posMan0.y]=' ';
        }
        else if (map[posMan1.x][posMan1.y]=='$') {
            posBox.x=posBox.x+posMan1.x-posMan0.x;
            posBox.y=posBox.y+posMan1.y-posMan0.y;
            if (map[posBox.x][posBox.y]==' ' || map[posBox.x][posBox.y]=='.') {
                map[posBox.x][posBox.y]='$';
                map[posMan1.x][posMan1.y]='@';
                map[posMan0.x][posMan0.y]=' ';
            }
            else if (map[posBox.x][posBox.y]=='#') {
                posBox.x=posMan1.x;
                posBox.y=posMan1.y;
                posMan1.x=posMan0.x;
                posMan1.y=posMan0.y;
            }
        }

        system("cls");
        printMap(map);
        if (posBox.x==posTarget.x && posBox.y==posTarget.y) {
            system("cls");
            printMap(map);
            printf("\nyou win!!!");
            break;
        }
    }
    fp=fopen("map2.txt","a");
    fprintf(fp,"your score is:%d\n",score);
    fclose(fp);
    return 0;

}
void printMap(char a[][COL+2]) {
    for (int i=0;i<ROW;i++) {
        printf("%s",a[i]);
    }
    printf("\n");
}