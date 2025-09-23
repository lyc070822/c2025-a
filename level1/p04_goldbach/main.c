#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int is_prime(int n) {
    for (int i = 2; i <= n-1; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}
int main() {
    int num;
    scanf("%d",&num);//输入一个4到100以内的偶数
    for(int i = 2;i <= num/2;i++) {
        int dif=num-i;//计算差值
        if (is_prime(i) == 1 && is_prime(dif) == 1) {
            printf("%d=%d+%d\n",num,i,dif);
        }
    }
}