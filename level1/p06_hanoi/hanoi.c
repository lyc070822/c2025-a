#include <stdio.h>
void hanoi(int n,char from,char aux,char to);
void hanoi(int n,char from,char aux,char to) {
    if(n==1) {
        printf("%c->%c\n",from,to);
        return;
    }
    else {
        hanoi(n-1,from,to,aux);
        printf("%c->%c\n",from,to);
        hanoi(n-1,aux,from,to);
    }
}