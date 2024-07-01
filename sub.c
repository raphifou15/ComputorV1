#include "math.h"

static char *sub_float_next(char *s1, char *s2, struct lenPointNumber *lpns1,
    struct lenPointNumber *lpns2, bool isneg){

    size_t size1 = lpns1->indexAPt + lpns1->indexBPt;
    size_t size2 = lpns2->indexAPt + lpns2->indexBPt;
    
    size_t tmp1 = (lpns1->indexBPt > lpns2->indexBPt) ? lpns1->indexBPt : lpns2->indexBPt;
    size_t tmp2 = (lpns1->indexAPt > lpns2->indexAPt) ? lpns1->indexAPt : lpns2->indexAPt;
    size_t sizeMalloc = tmp1 + tmp2;

    if (isneg){
        sizeMalloc++;
    }
    char *str = malloc(sizeof(char) * (sizeMalloc + 1));
    if (str == NULL) return NULL;
    str[sizeMalloc] = '\0';
    int rest = 0;
    bool afterPoint = true;

    
    for (;sizeMalloc > 0; sizeMalloc--){
        if (afterPoint){
            if (lpns1->indexAPt == 1 || lpns2->indexAPt == 1){
                if (lpns1->indexAPt == 1 && lpns2->indexAPt){
                    size1--;
                    size2--;
                    lpns1->indexAPt--;
                    lpns2->indexAPt--;
                }
                else if (lpns1->indexAPt == 1){
                    size1--;
                    lpns1->indexAPt--;
                }
                else{
                    size2--;
                    lpns2->indexAPt--;
                }
                str[sizeMalloc -1] = '.';
                afterPoint = false;
            }
            else if (lpns1->indexAPt > lpns2->indexAPt){
                size1--;
                lpns1->indexAPt--;
                str[sizeMalloc - 1] = s1[size1];
            }
            else if (lpns2->indexAPt > lpns1->indexAPt){
                size2--;
                lpns2->indexAPt--;
                char num1 = 0;
                char num2 = s2[size2] - 48;
                char num3 = 0;
                if (num1 < num2 + rest){
                    num1 += 10;
                    num3 = num1 - (num2 + rest);
                    str[sizeMalloc - 1] = num3 + 48;
                    rest = 1;
                }else{
                    num3 = num1 - (num2 + rest);
                    str[sizeMalloc - 1] = num3 + 48;
                    rest = 0;
                }
            }else{
                size1--;
                size2--;
                lpns1->indexAPt--;
                lpns2->indexAPt--;
                char num1 = s1[size1] - 48;
                char num2 = s2[size2] - 48;
                char num3 = 0;
                if (num1 < num2 + rest){
                    num1 += 10;
                    num3 = num1 - (num2 + rest);
                    str[sizeMalloc -1] = num3 + 48;
                    rest = 1;
                }else{
                    num3 = num1 - (num2 + rest);
                    str[sizeMalloc -1] = num3 + 48;
                    rest = 0;
                }
            }
        }else{
            if (lpns1->indexBPt > 0 && lpns2->indexBPt > 0){
                size1--;
                size2--;
                lpns1->indexBPt--;
                lpns2->indexBPt--;
                char num1 = s1[size1] - 48;
                char num2 = s2[size2] - 48;
                char num3 = 0;
                if (num1 < num2 + rest){
                    num1 += 10;
                    num3 = num1 - (num2 + rest);
                    rest = 1;
                }else{
                    num3 = num1 - (num2 + rest);
                    rest = 0;
                }
                str[sizeMalloc - 1] = num3 + 48;
            }
            else if (lpns1->indexBPt > 0 && lpns2->indexBPt == 0){
                size1--;
                lpns1->indexBPt--;
                char num1 = s1[size1] - 48;
                char num3 = 0;
                if (num1 < rest){
                    num1 += 10;
                    num3 = num1 - rest;
                    rest = 1;
                }else{
                    num3 = num1 - rest;
                    rest = 0;
                }
                str[sizeMalloc - 1] = num3 + 48;
            }
            else if (lpns1->indexBPt == 0 && lpns2->indexBPt == 0){
                if (isneg){
                    str[sizeMalloc - 1] = '-';
                }
            }
        }
    }
    str =supprimZeroBeforeNumber(str);
    str = supprimZeroAfterNumber(str);
   
    return str;
}

static char *sub_float(char *s1, char *s2){
    struct lenPointNumber lpnS1 = strlenNumberPoint(s1);
    struct lenPointNumber lpnS2 = strlenNumberPoint(s2);
    if (lpnS1.indexBPt > lpnS2.indexBPt)
        return sub_float_next(s1, s2, &lpnS1, &lpnS2, false);
    else if(lpnS2.indexBPt > lpnS1.indexBPt){
        return sub_float_next(s2, s1, &lpnS2, &lpnS1, true);
    }
    else{
        for(size_t i = 0; s1[i] != '\0' || s2[i] != '\0'; i++){
            if (s1[i] != '\0' && s2[i] == '\0')
                return sub_float_next(s1, s2, &lpnS1, &lpnS2, false);
            else if(s1[i] == '\0' && s2[i] != '\0')
                return sub_float_next(s2, s1, &lpnS2, &lpnS1, true);
            else if (s1[i] > s2[i]) return sub_float_next(s1, s2, &lpnS1, &lpnS2, false);
            else if (s2[i] > s1[i]) return sub_float_next(s2, s1, &lpnS2, &lpnS1, true);
        }
    }
    char *str = malloc(sizeof(char) * (1 + 1));
    if (str == NULL) return NULL;
    str[0] = '0';
    str[1] = '\0';
    return str;
    return NULL;
}

static char *sub_int_next(char *s1, char *s2, struct lenPointNumber *lpns1, struct lenPointNumber *lpns2, bool isneg){
    size_t sizeMalloc = 0;
    sizeMalloc = lpns1->indexBPt;
    if (isneg) sizeMalloc++;
    char *str = malloc(sizeof(char) * (sizeMalloc + 1));
    if (str == NULL) return NULL;
    str[sizeMalloc] = '\0';
    int rest = 0;
    for (;sizeMalloc > 0; sizeMalloc--){
        if (lpns1->indexBPt > 0 && lpns2->indexBPt > 0){
            lpns1->indexBPt--;
            lpns2->indexBPt--;
            char num1 = s1[lpns1->indexBPt] - 48;
            char num2 = s2[lpns2->indexBPt] - 48;
            char num3 = 0;
            if (num1 < num2 + rest){
                num1 += 10;
                num3 = num1 - (num2 + rest);
                rest = 1;
            }else{
                num3 = num1 - (num2 + rest);
                rest = 0;
            }
            printf("%d = num3\n", num3);
            str[sizeMalloc - 1] = num3 + 48;
        }
        else if (lpns1->indexBPt > 0 && lpns2->indexBPt == 0){
            lpns1->indexBPt--;
            char num1 = s1[lpns1->indexBPt] - 48;
            char num3 = 0;
            if (num1 < rest){
                num1 += 10;
                num3 = num1 - rest;
                rest = 1;
            }else{
                num3 = num1 - rest;
                rest = 0;
            }
            str[sizeMalloc - 1] = num3 + 48;
        }
        else if (lpns1->indexBPt == 0 && lpns2->indexBPt == 0){
            if (isneg){
                str[sizeMalloc - 1] = '-';
            }
        }
    }
    str =supprimZeroBeforeNumber(str);
    return str;
}

static char *sub_int(char *s1, char *s2){
    struct lenPointNumber lpnS1 = strlenNumberPoint(s1);
    struct lenPointNumber lpnS2 = strlenNumberPoint(s2);
    if (lpnS1.indexBPt > lpnS2.indexBPt)
        return sub_int_next(s1, s2, &lpnS1, &lpnS2, false);
    else if(lpnS2.indexBPt > lpnS1.indexBPt){
        return sub_int_next(s2, s1, &lpnS2, &lpnS1, true);
    }
    else{
        for (size_t i = 0; s1[i] != '\0'; i++){
            if (s1[i] > s2[i]) return sub_int_next(s1, s2, &lpnS1, &lpnS2, false);
            else if (s2[i] > s1[i]) return sub_int_next(s2, s1, &lpnS2, &lpnS1, true);
        }
    }
    char *str = malloc(sizeof(char) * (1 + 1));
    if (str == NULL) return NULL;
    str[0] = '0';
    str[1] = '\0';
    return str;
}

char    *sub(char *s1, char *s2){
    if (s1 == NULL || s2 == NULL) return NULL;
    long index1 = 0;
    long index2 = 0;
    for(; s1[index1] != '\0'; index1++) {
        if (index1 > LIMIT)
            return NULL;
    }
    for(; s2[index2] != '\0'; index2++){
        if (index2 > LIMIT)
            return NULL;
    }
    if (s1[0] == '-' && s2[0] != '-'){
        char *sjoin = join("-", s2);
        if (sjoin == NULL) return NULL;
        char *s = add(s1, sjoin);
        free(sjoin);
        return s;
    }
    if (s1[0] != '-' && s2[0] == '-'){
        char *s = add(s1, s2 + 1);
        return s;
    }
    if (s1[0] == '-' && s2[0] == '-'){
        s1++;
        s2++;
        char * s3 = s1;
        s1 = s2;
        s2 = s3;
    }
    if (isOnlyNumber(s1) == false || isOnlyNumber(s2) == false) return NULL;
    bool isS1Float = isNumberFloat(s1);
    bool isS2Float = isNumberFloat(s2);
    if (!isS1Float && !isS2Float){
        return sub_int(s1, s2);
    }
    return sub_float(s1, s2);
}