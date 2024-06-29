#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "math.h"

int main() {
    // Essayons d'allouer plus de mémoire que LONG_MAX
    char *res = add("0.15", "155");
    if (res == NULL) return 0;
    printf("res = %s\n", res);
    free(res);
    return 0;
}
