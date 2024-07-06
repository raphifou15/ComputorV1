#include "math.h"

struct decalValue{
    char *ns1;
    char *ns2;
};

static int numberBiger(char *s1, char *s2){
    if (s1 == NULL || s2 == NULL) return -1;
    size_t num1 = strlen(s1);
    size_t num2 = strlen(s2);
    if (num1 > num2)
        return 1;
    if (num2 > num1)
        return -1;
    size_t i = 0;
    for (; s1[i] != '\0'; i++){
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    }
    return (s1[i] - s2[i]);
}

static char * makeDivision(struct decalValue *dcv){
    char *tmpval = NULL;
    char *subb = strdup(dcv->ns2);
    char *restf = strdup("0");
    char *rest = strdup("1");
    bool isFinnish = false;

    while (!isFinnish ){
        while (numberBiger(subb, dcv->ns1) < 0){
            char *tmp = NULL;
            if (strcmp(rest, "0") == 0){
                tmp = strdup("1");
            }else{
                tmp = mul(rest, "2");
            }
            free(rest);
            rest = tmp;
            // printf("%s = rest\n", rest);
            char *val = add(rest, restf);
            char *tmp2 = mul(dcv->ns2, val);
            free(subb);
            free(val);
            subb = tmp2;
        }
        tmpval = add(rest, restf);
        free(restf);
        restf = tmpval;
        if (numberBiger(subb, dcv->ns1) == 0){
            isFinnish = true;
            continue;
        }
        free(rest);
        rest = strdup("0");
        while (numberBiger(subb, dcv->ns1) > 0){
            char *tmp = NULL;
            if (strcmp(rest, "0") == 0){
                tmp = strdup("1");
            }else{
                tmp = mul(rest, "2");
            }
            free(rest);
            rest = tmp;
            char *val = sub(restf, rest);
            char *tmp2 = mul(dcv->ns2, val);
            free(subb);
            free(val);
            subb = tmp2;
        }
        tmpval = sub(restf, rest);
        free(restf);
        restf = tmpval;
        if (strcmp(rest, "1") == 0){
            isFinnish = true;
        }
        free(rest);
        rest = strdup("0");
    }
    char *result = sub(dcv->ns1, subb);
    free(dcv->ns1);
    dcv->ns1 = result;
    free(subb);
    free(rest);
    // free(restf);
    return restf;
}



static bool isPoint (char *s){
    for (size_t i = 0; s[i] != '\0'; i++){
        if (s[i] == '.') return true;
    }
    return false;
}

static void decalWithoutMalloc(char *s){
    for (size_t i = 0; s[i] != '\0'; i++){
        if (s[i] == '.' && s[i + 1] == '\0'){
            s[i] = '0';
            return;
        }
        else if (s[i] == '.'){
            s[i] = s[i + 1];
            s[i + 1] = '.';  
            return;
        }
    }
}

static void decalValueWithMalloc(struct decalValue *dcv, int v){
    if (v == 1){
        char *s = join(dcv->ns1, "0");
        free (dcv->ns1);
        dcv->ns1 = s;
    }else{
        char *s = join(dcv->ns2, "0");
        free (dcv->ns2);
        dcv->ns2 = s;
    }
}

static void decalValueBegin(char *s1, char *s2, struct decalValue *dcv){
    struct lenPointNumber lpns1 = strlenNumberPoint(s1);
    struct lenPointNumber lpns2 = strlenNumberPoint(s2);
    size_t sizedec = 0;
    dcv->ns1 = strdup(s1);
    dcv->ns2 = strdup(s2);
    if (isPoint(dcv->ns1)) dcv->ns1 = supprimZeroAfterNumber(dcv->ns1);
    if (isPoint(dcv->ns2)) dcv->ns2 = supprimZeroAfterNumber(dcv->ns2);
    if (lpns1.indexAPt > 0 && lpns2.indexAPt> 0){
        if (lpns1.indexAPt >= lpns2.indexAPt)
            sizedec = lpns1.indexAPt - 1;
        else
            sizedec = lpns2.indexAPt - 1;
    }
    else if (lpns1.indexAPt > 0){
        sizedec = lpns1.indexAPt - 1;
    }else if (lpns2.indexAPt > 0){
        sizedec = lpns2.indexAPt;
    }
    else{
        return;
    }
    for (size_t i = 0; i < sizedec; i++){
        if (isPoint(dcv->ns1) == true){
            decalWithoutMalloc(dcv->ns1);
        }else
            decalValueWithMalloc(dcv, 1);

        if (isPoint(dcv->ns2) == true){
            decalWithoutMalloc(dcv->ns2);
        }else
            decalValueWithMalloc(dcv, 2);
    }
    dcv->ns1 = supprimZeroBeforeNumber(dcv->ns1);
    dcv->ns2 = supprimZeroBeforeNumber(dcv->ns2);
    if (isNumberFloat(dcv->ns1)) dcv->ns1 = supprimZeroAfterNumber(dcv->ns1);
    if (isNumberFloat(dcv->ns2)) dcv->ns2 = supprimZeroAfterNumber(dcv->ns2);
}

static char *div_number(char *s1, char *s2, bool isneg){
    // printf("s1 = %s\n", s1);
    // printf("s2 = %s\n", s2);
    struct decalValue dcv;
    dcv.ns1 = NULL;
    dcv.ns2 = NULL;
    decalValueBegin(s1, s2, &dcv);
    // printf("dcv.ns1 = %s\n", dcv.ns1);
    // printf("dcv.ns2 = %s\n", dcv.ns2);

    if (strcmp(dcv.ns1, "0") == 0){
        free(dcv.ns2);
        return dcv.ns1;
    }
    if (strcmp(dcv.ns2, "0") == 0){
        free(dcv.ns1);
        free(dcv.ns2);
        return NULL;
    }
    if (strcmp(dcv.ns2, "1") == 0){
        free(dcv.ns2);
        if (isneg == false) return dcv.ns1;
        char *ns1 = join("-", dcv.ns1);
        free(dcv.ns1);
        return ns1;
    }

    int diff = numberBiger(dcv.ns1, dcv.ns2);
    char *dividende = NULL;
    if (diff >= 0){
        dividende = makeDivision(&dcv);
        if (strcmp(dcv.ns1, "0") == 0){
            free(dcv.ns1);
            free(dcv.ns2);
            if (isneg){
                char *tmp = join("-",dividende);
                free(dividende);
                dividende = tmp;
            }
            return dividende;
        }
        else{
            char *tmp = join(dividende, ".");
            free(dividende);
            dividende = tmp;
        }
    }
    else{
        dividende = strdup("0.");
    }
    int k = 0;
    while (strcmp(dcv.ns1, "0") != 0 && k < 100){
        char *tmp = join(dcv.ns1, "0");
        free(dcv.ns1);
        dcv.ns1 = tmp;
        diff = numberBiger(dcv.ns1, dcv.ns2);
        if (diff < 0){
            char *tmp2 = join(dividende, "0");
            free(dividende);
            dividende = tmp2;
        }else{
            char *dividende2 = makeDivision(&dcv);
            char *tmp2 = join(dividende, dividende2);
            free(dividende);
            free(dividende2);
            dividende = tmp2;
        }
        k++;
    }
    

    if (isneg){
        char *tmp = join("-", dividende);
        free(dividende);
        dividende = tmp;
    }

    free(dcv.ns1);
    free(dcv.ns2);
    return dividende;
}

char *divi(char *s1, char *s2){
    if (s1 == NULL || s2 == NULL) return NULL;
    long index1 = 0;
    long index2 = 0;
    bool isneg = false;
    for(; s1[index1] != '\0'; index1++) {
        if (index1 > LIMIT)
            return NULL;
    }
    for(; s2[index2] != '\0'; index2++){
        if (index2 > LIMIT)
            return NULL;
    }
    if (s1[0] == '-' && s2[0] == '-'){
        s1++;
        s2++;
        if (isOnlyNumber(s1) == false || isOnlyNumber(s2) == false) return NULL;
    }
    else if (s1[0] == '-'){
        s1++;
        isneg = true;
        if (isOnlyNumber(s1) == false || isOnlyNumber(s2) == false) return NULL;
    }
    else if (s2[0] == '-'){
        s2++;
        isneg = true;
        if (isOnlyNumber(s1) == false || isOnlyNumber(s2) == false) return NULL;      
    }
    div_number(s1, s2, isneg);
}