#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "math.h"

int main() {
    // Essayons d'allouer plus de mémoire que LONG_MAX
    char *res = add("-500.4589", "-500.1");
    char *res2 = sub("500.45", "500.45");
    if (res == NULL) return 0;
    if (res2 == NULL) return 0;
    printf("res = %s\n", res);
    printf("res2 = %s\n", res2);
    free(res);
    free(res2);
    return 0;
}
