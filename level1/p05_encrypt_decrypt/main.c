#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void xor_crypt(const unsigned char *in, unsigned char *out, size_t len,
               const unsigned char *key, size_t keylen) {
    for (size_t i = 0; i < len; i++) {
        out[i] = in[i] ^ key[i % keylen];
    }
}

int main() {
    char message[1024];
    char key[256];

    printf("input target string:");
    if (!fgets(message, sizeof(message), stdin)) return 0;
    message[strcspn(message, "\n")] = 0;

    printf("input key string:");
    if (!fgets(key, sizeof(key), stdin)) return 0;
    key[strcspn(key, "\n")] = 0;

    size_t len = strlen(message);      // 明文长度（我们保存用于加/解密）
    size_t klen = strlen(key);
    if (klen == 0) {
        fprintf(stderr, "key length must be > 0\n");
        return 1;
    }

    unsigned char *encrypted = malloc(len);
    unsigned char *decrypted = malloc(len + 1); // 多一个字节放 '\0'

    // 加密
    xor_crypt((unsigned char*)message, encrypted, len, (unsigned char*)key, klen);

    // 以十六进制输出密文（安全，不会被 NUL 截断）
    printf("\nencrypted target string: ");
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", encrypted[i]);
    }
    printf("\n");

    // 解密
    xor_crypt(encrypted, decrypted, len, (unsigned char*)key, klen);
    decrypted[len] = '\0'; // 手动结尾，这里安全，因为 decrypted 是明文（文本）
    printf("decrypted target string: %s\n", decrypted);

    free(encrypted);
    free(decrypted);
    return 0;
}
