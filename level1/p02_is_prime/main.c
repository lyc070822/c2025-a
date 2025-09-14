#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int n) {
    if (n == 1) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    //    只需检查到 sqrt(n) 即可。因为如果 n 有一个大于 sqrt(n) 的因子，
    //    那它必定还有一个小于 sqrt(n) 的因子。
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int num;
    scanf("%d",&num);
    printf("%d %s素数。\n", num, is_prime(num) ? "是" : "不是");
    return 0;
}