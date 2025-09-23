#include <stdio.h>
void hanoi(int n,char from,char aux,char to) {
    if (n==0) {
        return;
    }
    if(n==1) {
        printf("%c -> %c\n",from,to);
    }
    if(n==2) {
        printf("%c -> %c\n",from,aux);
        printf("%c -> %c\n",from,to);
        printf("%c -> %c\n",aux,to);
    }
    if (n>2) {
        hanoi(n-1,from,to,aux);
        printf("%c -> %c\n",from,to);
        hanoi(n-1,aux,from,to);
    }
}
int main() {
    hanoi(24,'A','B','C');
}