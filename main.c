#include "math/math.h"

int main() {
    // Essayons d'allouer plus de mémoire que LONG_MAX
    // char *res = add("100", "2");
    // char *res2 = sub("200", "0.0000");
    // char *res3 = mul("1", "-10.2");
    // char *res4 = divi("355", "113");
    // char *res5 = squareRoot("3");
    char *res6 = modulo("5", "2");
    // if (res == NULL) return 0;
    // printf("res = %s\n", res);
    // free(res);
    // if (res2 == NULL) return 0;
    // printf("res2 = %s\n", res2);
    // free(res2);
    // if (res3 == NULL) return 0;
    // printf("res3 = %s\n", res3);
    // free(res3);
    printf("res = %s\n", res6);
    return 0;
}