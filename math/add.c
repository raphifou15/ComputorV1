#include "math.h"

static char *add_int(char *s1, char *s2, long index1, long index2){
    long sizeMalloc = 0;
    sizeMalloc = (index1 >= index2) ? index1 : index2;
    sizeMalloc++;
    char *str = malloc(sizeof(char) * (sizeMalloc + 1));
    if (str == NULL) return NULL;
    str[sizeMalloc] = '\0';
    int rest = 0;
    for (;sizeMalloc > 0; sizeMalloc--){
        if (index1 > 0 && index2 > 0){
            index1--;
            index2--;
            char num1 = s1[index1] - 48;
            char num2 = s2[index2] - 48;
            char num3 = num1 + num2;
            if (num3 + rest > 9){
                str[sizeMalloc - 1] = ((num3 + rest) % 10) + 48;
                rest = (num3 + rest) / 10;
            }else{
            str[sizeMalloc - 1] = num3 + rest + 48;
            rest = 0;
            }
        }else if(index1 > 0 && index2 == 0){
            index1--;
            char num1 = s1[index1] - 48;
            if (num1 + rest > 9){
                str[sizeMalloc - 1] = ((num1 + rest) % 10) + 48;
                rest = (num1 + rest) / 10;
            }else{
                str[sizeMalloc - 1] = num1 + rest + 48;
                rest = 0;
            }
        }
        else if (index1 == 0 && index2 > 0){
            index2--;
            char num2 = s2[index2] - 48;
            if (num2 + rest > 9){
                str[sizeMalloc - 1] = ((num2 + rest) % 10) + 48;
                rest = (num2 + rest) / 10;
            }else{
                str[sizeMalloc - 1] = num2 + rest + 48;
                rest = 0;
            }
        }
        else{
            str[sizeMalloc - 1] = rest + 48;
        }
    }
    str = supprimZeroBeforeNumber(str);
    return str;
}


static char *add_float(char *s1, char *s2){
    struct lenPointNumber lpnS1 = strlenNumberPoint(s1);
    struct lenPointNumber lpnS2 = strlenNumberPoint(s2);

    long size1 = lpnS1.indexAPt + lpnS1.indexBPt;
    long size2 = lpnS2.indexAPt + lpnS2.indexBPt;

    long tmp1 = (lpnS1.indexAPt >= lpnS2.indexAPt) ? lpnS1.indexAPt : lpnS2.indexAPt;
    long tmp2 = (lpnS1.indexBPt >= lpnS2.indexBPt) ? lpnS1.indexBPt : lpnS2.indexBPt;

    long sizeMalloc = tmp1 + tmp2;
    sizeMalloc++;
    char *str = malloc(sizeof(char) * (sizeMalloc + 1));
    if (str == NULL) return NULL;
    str[sizeMalloc] = '\0';

    int rest = 0;
    bool afterPoint = true;

    for (; sizeMalloc > 0; sizeMalloc--){
        if (afterPoint){
            if (lpnS1.indexAPt == 1 || lpnS2.indexAPt == 1){
                if (lpnS1.indexAPt == 1 && lpnS2.indexAPt == 1){
                    size1--;
                    size2--;
                    lpnS1.indexAPt--;
                    lpnS2.indexAPt--;
                }
                else if (lpnS1.indexAPt == 1){
                    size1--;
                    lpnS1.indexAPt--;
                }
                else{
                    size2--;
                    lpnS2.indexAPt--;
                }
                str[sizeMalloc - 1] = '.';
                afterPoint = false;
            }
            else if (lpnS1.indexAPt > lpnS2.indexAPt){
                lpnS1.indexAPt--;
                size1--;
                char num1 = s1[size1] - 48;
                if (num1 + rest > 9){
                    str[sizeMalloc - 1] = ((num1 + rest) % 10) + 48;
                    rest = (num1 + rest) / 10;
                }else{
                    str[sizeMalloc - 1] = num1 + rest + 48;
                    rest = 0;
                }
            }
            else if (lpnS1.indexAPt < lpnS2.indexAPt){
                lpnS2.indexAPt--;
                size2--;
                char num2 = s2[size2] - 48;
                if (num2 + rest > 9){
                    str[sizeMalloc - 1] = ((num2 + rest) % 10) + 48;
                    rest = (num2 + rest) / 10;
                }else{
                    str[sizeMalloc - 1] = num2 + rest + 48;
                    rest = 0;
                }
            }else{
                size1--;
                size2--;
                lpnS1.indexAPt--;
                lpnS2.indexAPt--;
                char num1 = s1[size1] - 48;
                char num2 = s2[size2] - 48;
                char num3 = num1 + num2;
                if (num3 + rest > 9){
                    str[sizeMalloc - 1] = ((num3 + rest) % 10) + 48;
                    rest = (num3 + rest) / 10;
                }else{
                    str[sizeMalloc - 1] = num3 + rest + 48;
                    rest = 0;
                }
            }  
        }
        else{
            if (size1 > 0 && size2 > 0){
                size1--;
                size2--;
                char num1 = s1[size1] - 48;
                char num2 = s2[size2] - 48;
                char num3 = num1 + num2;
                if (num3 + rest > 9){
                    str[sizeMalloc - 1] = ((num3 + rest) % 10) + 48;
                    rest = (num3 + rest) / 10;
                }else{
                    str[sizeMalloc - 1] = num3 + rest + 48;
                    rest = 0;
                }
            }else if(size1 > 0 && size2 == 0){
                size1--;
                char num1 = s1[size1] - 48;
                if (num1 + rest > 9){
                    str[sizeMalloc - 1] = ((num1 + rest) % 10) + 48;
                    rest = (num1 + rest) / 10;
                }else{
                    str[sizeMalloc - 1] = num1 + rest + 48;
                    rest = 0;
                }
            }
                else if (size1 == 0 && size2 > 0){
                size2--;
                char num2 = s2[size2] - 48;
                if (num2 + rest > 9){
                    str[sizeMalloc - 1] = ((num2 + rest) % 10) + 48;
                    rest = (num2 + rest) / 10;
                }else{
                    str[sizeMalloc - 1] = num2 + rest + 48;
                    rest = 0;
                }
            }
            else{
                str[sizeMalloc - 1] = rest + 48;
            }
        }
    }
    str = supprimZeroBeforeNumber(str);
    if (str == NULL) return NULL; 
    str = supprimZeroAfterNumber(str);
    return str;
}

char *  add(char *s1, char *s2){
    bool isneg = false;
    if (s1 == NULL || s2 == NULL) return NULL;
    long index1 = 0;
    long index2 = 0;
    for(; s1[index1] != '\0'; index1++) {
        if ((unsigned long)(index1) > LIMIT)
            return NULL;
    }
    for(; s2[index2] != '\0'; index2++){
        if ((unsigned long)(index2) > LIMIT)
            return NULL;
    }
    if (s1[0] == '-' && s2[0] != '-') return sub(s2, s1 + 1);
    if (s1[0] != '-' && s2[0] == '-') return sub(s1, s2 + 1);
    if (s1[0] == '-' && s2[0] == '-') isneg = true;

    if (isneg){
        if (isOnlyNumber(s1 + 1) == false || isOnlyNumber(s2 + 1) == false) return NULL;
    }
    else if (isOnlyNumber(s1) == false || isOnlyNumber(s2) == false) return NULL;
    bool isS1Float = isNumberFloat(s1);
    bool isS2Float = isNumberFloat(s2);


    if (!isS1Float && !isS2Float){
        if (isneg){
            char *str = add_int(s1 + 1, s2 + 1, --index1, --index2);
            if (str == NULL ) return NULL;
            char *str2 = join("-", str);
            free(str);
            return str2;
        }
        return add_int(s1, s2, index1, index2);
    }
    if (isneg){
            char *str = add_float(s1 + 1, s2 + 1);
            if (str == NULL) return NULL;
            char *str2 = join("-", str);
            free(str);
            return str2;
        }
    return add_float(s1, s2);
}