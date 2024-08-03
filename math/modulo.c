#include "math.h"

static char *floatToInt(char *floatNum){
    if (floatNum == NULL) return NULL;
    long i = 0;
    for(;floatNum[i] != '.' && floatNum[i] != '\0'; i++){
    }
    char *intNumber = malloc(sizeof(char) * i + 1);
    if (intNumber == NULL) return NULL;
    intNumber[i] = '\0';
    for (long k = 0; k < i; k++){
        intNumber[k] = floatNum[k];
    }
    return intNumber;
}

char*   modulo(char *num1, char *num2){
    if (num1 == NULL || num2 == NULL) return NULL;
    char *numDiv = divi(num1, num2, false);
    if (numDiv == NULL) return NULL;

    char *tmpsign = NULL;
    if (numDiv[0] == '-'){
        tmpsign = numDiv + 1;
    }else{
        tmpsign = numDiv;
    }
    if (!isNumberFloat(tmpsign)){
        char *res = malloc(sizeof(char) * 1 + 1);
        if (res == NULL){free(numDiv); return NULL;}
        res[1] = '\0';
        res[0] = '0';
        free(numDiv);
        return res;
    }
    char *intNumber = floatToInt(numDiv);
    if (intNumber == NULL) {free(numDiv); return NULL;}
    char *mulNumber = mul(intNumber, num2);
    if (mulNumber == NULL){free(numDiv); free(intNumber); return NULL;}
    char *res = sub(num1, mulNumber);
    free(intNumber); free(mulNumber); free(numDiv);
    return res;
}