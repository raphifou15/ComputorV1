#include "math.h"

static char *methodeHeron(char *val, char *s){
    // formule de la methode de heron xn + 1 = 0.5 * (xn + (nb / xn))
    char *val2 = sub(val, "1");
    char *power = mul(val, val);
    char *power2 = mul(val2, val2);
    char *val3 = sub(power, power2);
    char *xn = divi(val3, "2");
    free(val2); free(power); free(power2); free(val3);
    size_t i = 0;
    while(i < 5){
        // number diviser par xn
        char *nbdivixn = divi(s, xn);
        char *num2 = add(xn, nbdivixn);
        char *xn1 = mul("0.5", num2);
        free(nbdivixn); free(num2); free(xn);
        xn = xn1;
        i++;
    }
    return xn;
}

char *squareRoot(char *s){
    if (s[0] == '-') return NULL;
    char *val = add("0", "0");
    bool isFinnish = false;
    while (!isFinnish){
        char *power = mul(val, val);
        int num = numberBigerLowerEqual(power, s);
        free(power);
        if (num == 0)return val;
        else if (num > 0){
            char *nval = methodeHeron(val, s);
            free(val);
            val = nval;
            isFinnish = true;
        }else{
            char *addition = add("1", val);
            free(val);
            val = addition;
        }
    }
    return val;
}