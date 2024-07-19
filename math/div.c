#include "math.h"

struct decalValue{
    char *ns1;
    char *ns2;
};

static int numberBiger(char *s1, char *s2){
    if (s1 == NULL || s2 == NULL) return -1;
    size_t num1 = strlen(s1);
    size_t num2 = strlen(s2);
    if (num1 > num2) return 1;
    if (num2 > num1) return -1;
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
    if (subb == NULL || restf == NULL || rest == NULL){
        if (subb != NULL) free(subb);
        if (restf != NULL) free(restf);
        if (rest != NULL) free(rest);
        return NULL;
    }
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
            if (tmp == NULL){
                free(subb); free(restf);
                return NULL;
            }
            rest = tmp;
            // printf("%s = rest\n", rest);
            char *val = add(rest, restf);
            if (val == NULL){
                free(subb); free(rest); free(restf);
                return NULL;
            }
            char *tmp2 = mul(dcv->ns2, val);
            free(subb);
            free(val);
            if (tmp2 == NULL){
                free(rest); free(restf);
                return NULL;
            }
            subb = tmp2;
        }
        tmpval = add(rest, restf);
        free(restf);
        if (tmpval == NULL){
            free(rest); free(subb);
            return NULL;
        }
        restf = tmpval;
        if (numberBiger(subb, dcv->ns1) == 0){
            isFinnish = true;
            continue;
        }
        free(rest);
        rest = strdup("0");
        if (rest == NULL){
            free(subb); free(restf);
            return NULL;
        }
        while (numberBiger(subb, dcv->ns1) > 0){
            char *tmp = NULL;
            if (strcmp(rest, "0") == 0){
                tmp = strdup("1");
            }else{
                tmp = mul(rest, "2");
            }
            free(rest);
            if (tmp == NULL){
                free(subb); free(restf);
                return NULL;
            }
            rest = tmp;
            char *val = sub(restf, rest);
            if (val == NULL){
                free(subb); free(rest); free(restf);
                return NULL;
            }
            char *tmp2 = mul(dcv->ns2, val);
            free(subb);
            free(val);
            if (tmp2 == NULL){
                free(rest); free(restf);
                return NULL;
            }
            subb = tmp2;
        }
        tmpval = sub(restf, rest);
        free(restf);
        if (tmpval == NULL){
            free(subb); free(rest);
            return NULL;
        }
        restf = tmpval;
        if (strcmp(rest, "1") == 0){
            isFinnish = true;
        }
        free(rest);
        rest = strdup("0");
        if (rest == NULL){
            free(subb); free(restf);
            return NULL;
        }
    }
    char *result = sub(dcv->ns1, subb);
    if (result == NULL){
        free(subb); free(rest); free(restf);
        return NULL;
    }
    free(dcv->ns1);
    dcv->ns1 = result;
    free(subb);
    free(rest);

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

static bool decalValueBegin(char *s1, char *s2, struct decalValue *dcv){
    struct lenPointNumber lpns1 = strlenNumberPoint(s1);
    struct lenPointNumber lpns2 = strlenNumberPoint(s2);
    size_t sizedec = 0;
    dcv->ns1 = strdup(s1);
    if (dcv->ns1 == NULL) return false;
    dcv->ns2 = strdup(s2);
    if (dcv->ns2 == NULL){
        free(dcv->ns1);
        return false;
    }
    if (isPoint(dcv->ns1)){
        dcv->ns1 = supprimZeroAfterNumber(dcv->ns1);
        if (dcv->ns1 == NULL){
            free(dcv->ns2);
            return false;
        }
    }
    if (isPoint(dcv->ns2)){
        dcv->ns2 = supprimZeroAfterNumber(dcv->ns2);
        if (dcv->ns2 == NULL){
            free(dcv->ns1);
            return false;
        }
    }
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
        return true;
    }
    for (size_t i = 0; i < sizedec; i++){
        if (isPoint(dcv->ns1) == true){
            decalWithoutMalloc(dcv->ns1);
        }else{
            decalValueWithMalloc(dcv, 1);
            if (dcv->ns1 == NULL){
                free(dcv->ns2);
                return false;
            }
        }

        if (isPoint(dcv->ns2) == true){
            decalWithoutMalloc(dcv->ns2);
        }else{
            decalValueWithMalloc(dcv, 2);
            if (dcv->ns2 == NULL){
                free(dcv->ns1);
                return false;
            }
        }
    }
    dcv->ns1 = supprimZeroBeforeNumber(dcv->ns1);
    if (dcv->ns1 == NULL){
        free(dcv->ns2);
        return false;
    }
    dcv->ns2 = supprimZeroBeforeNumber(dcv->ns2);
    if (dcv->ns2 == NULL){
        free(dcv->ns1);
        return false;
    }
    if (isNumberFloat(dcv->ns1)){
        dcv->ns1 = supprimZeroAfterNumber(dcv->ns1);
        if (dcv->ns1 == NULL){
            free(dcv->ns2);
            return false;
        }
    }
    if (isNumberFloat(dcv->ns2)){
        dcv->ns2 = supprimZeroAfterNumber(dcv->ns2);
        if (dcv->ns2 == NULL){
            free(dcv->ns1);
            return false;
        }
    }
    return true;
}

static char *div_number(char *s1, char *s2, bool isneg){
    struct decalValue dcv;
    dcv.ns1 = NULL;
    dcv.ns2 = NULL;
    if (decalValueBegin(s1, s2, &dcv) == false){
        return NULL;
    }
    
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
        if (dividende == NULL){
            free(dcv.ns1); free(dcv.ns2);
            return NULL;
        }
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
            if (tmp == NULL){
                free(dcv.ns1); free(dcv.ns2);
                return NULL;
            }
            dividende = tmp;
        }
    }
    else{
        dividende = strdup("0.");
        if (dividende == NULL){
            free(dcv.ns1); free(dcv.ns2);
            return NULL;
        }
    }
    int k = 0;
    while (strcmp(dcv.ns1, "0") != 0 && k < 100){
        char *tmp = join(dcv.ns1, "0");
        free(dcv.ns1);
        if (tmp == NULL){
            free(dcv.ns2); free(dividende);
            return NULL;
        }
        dcv.ns1 = tmp;
        diff = numberBiger(dcv.ns1, dcv.ns2);
        if (diff < 0){
            char *tmp2 = join(dividende, "0");
            free(dividende);
            if (tmp2 == NULL){
                free(dcv.ns1); free(dcv.ns2);
                return NULL;
            }
            dividende = tmp2;
        }else{
            char *dividende2 = makeDivision(&dcv);
            if (dividende2 == NULL){
                free(dividende); free(dcv.ns1); free(dcv.ns2);
                return NULL;
            }
            char *tmp2 = join(dividende, dividende2);
            free(dividende);
            free(dividende2);
            if (tmp2 == NULL){
                free(dcv.ns1); free(dcv.ns2);
                return NULL;
            }
            dividende = tmp2;
        }
        k++;
    }
    

    if (isneg){
        char *tmp = join("-", dividende);
        free(dividende);
        if (tmp == NULL){
            free(dcv.ns1); free(dcv.ns2);
            return NULL;
        }
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
        if ((unsigned long)index1 > LIMIT)
            return NULL;
    }
    for(; s2[index2] != '\0'; index2++){
        if ((unsigned long)index2 > LIMIT)
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
    return div_number(s1, s2, isneg);
}