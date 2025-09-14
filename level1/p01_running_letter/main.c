#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#define width 20
int main(void) {
    int pos=0;
    int dir=1;
    char word[]="Hans";
    int len=(int)strlen(word);
    while (1) {
        system("cls");
        for (int i = 0; i < pos; i++) {
            putchar(' ');
        }
        printf("%s",word);
        fflush(stdout);
        Sleep(100);
        pos = pos + dir;
        if (pos <= 0) {
            dir=1;
        }
        if (pos + len >= width) {
            dir = -1;
        }

    }
    return 0;
}