#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "math.h"

int main() {
    // Essayons d'allouer plus de mémoire que LONG_MAX
    char *res = add("500.4589", "500");
    char *res2 = sub("200", "200.005898");
    char *res3 = mul("-158", "001");
    if (res == NULL) return 0;
    printf("res = %s\n", res);
    free(res);
    if (res2 == NULL) return 0;
    printf("res2 = %s\n", res2);
    free(res2);
    if (res3 == NULL) return 0;
    printf("res3 = %s\n", res3);
    free(res3);
    return 0;
}
