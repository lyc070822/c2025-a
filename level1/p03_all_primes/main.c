// primes_win.c
// Windows 下编译示例：
// MSVC: cl /O2 primes_win.c
// MinGW: gcc -O2 primes_win.c -o primes.exe

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>  // QueryPerformanceCounter, Sleep 等
// 切换控制台到 UTF-8 编码，避免中文乱码
void setUTF8(void) {
    // 切换代码页到 UTF-8
    system("chcp 65001 > nul");

    // 同时设置 C 语言标准库的本地化（让 printf、wprintf 支持 UTF-8）
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

int main(void) {
    setUTF8();
    const int N = 1000;           // 上限
    if (N < 2) return 0;
    // 只在数组中保存奇数（3,5,7,...），去掉所有偶数能节省约一半工作量。
    // 映射关系：索引 i 对应的实际数是 2*i + 3
    int oddCount = (N - 1) / 2;   // 例如 N=1000 -> (999)/2 = 499 (3..999 的奇数个数)
    // 用一个字节数组保存标记：0 表示未标记（可能是素数），1 表示已标记为合数
    unsigned char *isComposite = (unsigned char *)calloc(oddCount, 1);
    if (!isComposite) {
        fprintf(stderr, "内存分配失败\n");
        return 1;
    }
    // 开始计时（只计筛选计算部分，不包含后面的打印开销）
    LARGE_INTEGER freq, t_start, t_end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&t_start);

    // 埃拉托斯特尼筛（仅在奇数数组上操作）
    for (int i = 0; i < oddCount; ++i) {
        if (isComposite[i]) continue;      // 已被标记则跳过
        int p = 2 * i + 3;                // 当前素数候选（对应奇数）
        long long p2 = (long long)p * p;
        if (p2 > N) break;                // 若 p^2 > N，后面无需再标记

        // p^2 在奇数数组中的索引： j = (p^2 - 3) / 2
        int startIndex = (int)((p2 - 3) / 2);
        // 在奇数数组中，每次跳过 p 个索引（等价数值上跳 2*p）
        for (int j = startIndex; j < oddCount; j += p) {
            isComposite[j] = 1;
        }
    }

    QueryPerformanceCounter(&t_end);

    // 打印所有素数（注意：2 单独处理，因为数组里只保存奇数）
    printf("Primes up to %d:\n", N);
    if (N >= 2) printf("2 ");
    for (int i = 0; i < oddCount; ++i) {
        if (!isComposite[i]) {
            printf("%d ", 2 * i + 3);
        }
    }
    printf("\n");

    // 计算并打印耗时（毫秒）
    double elapsed_ms = (double)(t_end.QuadPart - t_start.QuadPart) * 1000.0 / (double)freq.QuadPart;
    printf("时间是: %.6f ms\n", elapsed_ms);

    free(isComposite);
    return 0;
}
