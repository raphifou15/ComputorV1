#include "math.h"

struct lenPointNumber{
    long indexBPt;
    long indexAPt;
};

static long strlenAfterPoint(char *str){
    long size = 0;
    bool afterPoint = false;  
    for(long i = 0; str[i] != '\0'; i++){
        if (str[i] == '.') afterPoint = true;
        if (afterPoint) size++;
    }
    return size;
}

static char * supprimZeroBeforeNumber(char *str){
    if (str == NULL) return NULL;
    size_t number_zero = 0;
    while (str[number_zero] != '\0' && str[number_zero] == '0'){
        number_zero++;
    }
    size_t size = strlen(str);
    size -= number_zero;
    char *s = (char *)malloc(sizeof(char) * (size + 1));
    if (s == NULL){
        free(str);
        return NULL;
    }
    s[size] = '\0';
    for (int i = 0; i < size; i++){
        s[i] = str[number_zero];
        number_zero++;
    }
    free(str);
    return s;
}

// static char *   supprimZeroAfterNumber(char *str){
//     // if (str == NULL) return NULL;
//     // size_t number_zero = 0;
//     // size_t size = strlen(str);
//     // while (str[i] )
// }

static bool isOnlyNumber(char *s1){
    if (s1 == NULL) return false;
    int point = 0;
    char *s2 = s1;
    while(*s2 != '\0'){
        if (point == 0 && *s2 == '.'){
            point++;
        }
        else if (*s2 < '0' || *s2 > '9') return false;
        s2++;
    }
    return true;
}

static bool isNumberFloat(char *str){
    char *s = str;
    while (*s != '\0'){
        if (*s == '.') return true;
        s++;
    }
    return false;
}

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

static char *add_float(char *s1, char *s2, long index1, long index2){

    // utiliser la structure se sera plus facile.
    // il y a la len avant le point et apres le point ce qui peut permettre de savoir la longuer max pour l'addition

    long index1AfterPoint = strlenAfterPoint(s1);
    long index2AfterPoint = strlenAfterPoint(s2);

    long sizeMalloc = 0;
    sizeMalloc = (index1 >= index2) ? index1 : index2;
    sizeMalloc++;
    char *str = malloc(sizeof(char) * (sizeMalloc + 1));
    if (str == NULL) return NULL;
    str[sizeMalloc] = '\0';

    
    int rest = 0;
    bool beforePoint = true;

    printf("index1AfterPoint = %ld    index2AfterPoint = %ld\n", index1AfterPoint, index2AfterPoint);
    for (; sizeMalloc > 0; sizeMalloc--){
        if (beforePoint){
            if (index1AfterPoint == 1 || index2AfterPoint == 1){
                if (index1AfterPoint == 1 && index2AfterPoint == 1){
                    index1--;
                    index2--;
                    index1AfterPoint--;
                    index2AfterPoint--;
                }
                else if (index1AfterPoint == 1){
                    index1--;
                    index1AfterPoint--;
                }
                else{
                    index2--;
                    index2AfterPoint--;
                }
                str[sizeMalloc - 1] = '.';
                beforePoint = false;
            }
            else if (index1AfterPoint > index2AfterPoint){
                index1AfterPoint--;
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
            // if (index1 > index2){
            //     index1--;
            //     str[sizeMalloc - 1] = s1[index1];
            //     if (s1[index1] == '.') beforePoint = false;
            // }else if (index2 > index1){
            //     index2--;
            //     str[sizeMalloc - 1] = s2[index2];
            //     if (s2[index2] == '.') beforePoint = false;
            // }else{
            //     index1--;
            //     index2--;
            //     if (s1[index1] == '.' && s2[index2] == '.'){
            //         str[sizeMalloc - 1] = s2[index2];
            //         beforePoint = false;
            //     }
            //     else {
            //         char num1 = s1[index1] - 48;
            //         char num2 = s2[index2] - 48;
            //         char num3 = num1 + num2;
            //         if (num3 + rest > 9){
            //             str[sizeMalloc - 1] = ((num3 + rest) % 10) + 48;
            //             rest = (num3 + rest) / 10;
            //         }else{
            //             str[sizeMalloc - 1] = num3 + rest + 48;
            //             rest = 0;
            //         }
            //     }
            // }
        }
        else{
            str[sizeMalloc - 1] = rest + '0';
        }
    }
    // str = supprimZeroBeforeNumber(str);
    return str;
}

// continuer a faire la fonction float add.
char *  add(char *s1, char *s2){
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
    if (isOnlyNumber(s1) == false || isOnlyNumber(s2) == false) return NULL;
    bool isS1Float = isNumberFloat(s1);
    bool isS2Float = isNumberFloat(s2);

    if (!isS1Float && !isS2Float)
        return add_int(s1, s2, index1, index2);
    return add_float(s1, s2, index1, index2);
}