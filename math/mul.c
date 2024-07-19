#include "math.h"

static char *mul_float(char *s1, char *s2, bool isneg){
    if (strcmp(s1, "0") == 0 || strcmp(s2, "0") == 0){
        char *str = malloc(sizeof(char) * (1 + 1));
        if (str == NULL) return NULL;
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    if (strcmp(s1, "1") == 0){
        char *str = strdup(s2);
        if (str == NULL) return NULL;
        if (isneg){
            char *str2 = join("-", str);
            free(str);
            return str2;
        }
        return str;
    }else if (strcmp(s2, "1") == 0){
        char *str = strdup(s1);
        if (str == NULL) return NULL;
        if (isneg){
            char *str2 = join("-", str);
            free(str);
            return str2;
        }
        return str;
    }

    size_t size1 = strlen(s1);
    size_t size2 = strlen(s2);
    char *str = NULL;
    size_t sizeTab = 0;
    
    struct lenPointNumber lpns1 = strlenNumberPoint(s1);
    struct lenPointNumber lpns2 = strlenNumberPoint(s2);

    char *s3 = decalValue(s2, lpns1, lpns2); // s3 malloc
    
    if (s3 == NULL) return NULL;
    // printf("s3 = %s\n", s3);
    sizeTab = (lpns1.indexAPt == 0) ? size1 : size1 - 1;
    char **tab = malloc(sizeof(char *) * sizeTab);
    if (tab == NULL){
        free(s3);
        return NULL;
    };
    // size_t rest = 0;
    size_t j = size1;
    for (size_t i = 0; i < sizeTab; i++){
        size_t sizeMalloc = size1 + size2 + 1;
        size_t rest = 0;
        tab[i] = malloc(sizeof(char) * (sizeMalloc + 1));
        if (tab[i] == NULL){
            while (i > 0){
                free(tab[i - 1]);
                i--;
            }
            free(tab);
            free(s3);
            return NULL;
        }
        tab[i][sizeMalloc] = '\0';
        size_t index2 = strlen(s3);
        while(s3[index2 - 1] == '0'){
            index2--;
        }
        if (s3[index2 - 1] == '.')
            index2--;
        
        for (;sizeMalloc > 0; sizeMalloc--){
            if (s1[j - 1] == '.') j--;
            if (index2 > 0){
                index2--;
                if (s3[index2] == '.'){
                    tab[i][sizeMalloc - 1] = '.';
                }
                else {
                    char num1 = s3[index2] - 48;
                    char num2 = s1[j - 1] - 48;
                    char num3 = (num1 * num2) + rest;
                    tab[i][sizeMalloc - 1] = (num3 % 10) + 48;
                    rest = num3 / 10;
                }
            }else if (rest > 0){
                tab[i][sizeMalloc - 1] = rest + 48;
                rest = 0;
            }else{
                tab[i][sizeMalloc - 1] = '0';
            }
        }
        j--;
        decalValueOne(s3);

        if (i == 0){
            str = strdup(tab[i]);
            if (str == NULL){
                free(tab);
                free(s3);
                return NULL;
            }
            str = supprimZeroBeforeNumber(str);
        }
        else{
            char *str2 = str;
            str = add(str2, tab[i]);
            free(str2);
            if (str == NULL){
                while (i > 0){
                    free(tab[i - 1]);
                    i--;
                }
                free(tab);
                free(s3);
                return NULL;
            }
        }
    }
    for (size_t i = 0; i < sizeTab; i++){
        free(tab[i]);
    }
    free(tab);
    free(s3);
    char *str2 = NULL;
    if (isneg){
        if (strlen(str) == 0){
            str2 = join("0", str);
            free(str);
        }else{
            str2 = join("-", str);
            free(str);
        }
        return str2;
    }
    if (strlen(str) == 0){
        str2 = join("0", str);
        free(str);
        return str2;
    }else
        return str;
}

static char *mul_int(char *s1, char *s2, bool isneg){
    if (strcmp(s1, "0") == 0 || strcmp(s2, "0") == 0){
        char *str = malloc(sizeof(char) * (1 + 1));
        if (str == NULL) return NULL;
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    if (strcmp(s1, "1") == 0){
        char *str = strdup(s2);
        if (str == NULL) return NULL;
        if (isneg){
            char *str2 = join("-", str);
            free(str);
            return str2;
        }
        return str;
    }else if (strcmp(s2, "1") == 0){
        char *str = strdup(s1);
        if (str == NULL) return NULL;
        if (isneg){
            char *str2 = join("-", str);
            free(str);
            return str2;
        }
        return str;
    }

    size_t size1 = strlen(s1);
    size_t size2 = strlen(s2);
    char *str = NULL;
    size_t sizeTab = size1; 
    
    char **tab = malloc(sizeof(char *) * sizeTab);
    if (tab == NULL) return NULL;
    for (size_t i = 0; i < sizeTab; i++){
        size_t sizeMalloc = size1 + size2 + 1;
        size_t rest = 0;
        tab[i] = malloc(sizeof(char) * (sizeMalloc + 1));
        if (tab[i] == NULL){
            while (i > 0){
                free(tab[i - 1]);
                i--;
            }
            free(tab);
            return NULL;
        }
        tab[i][sizeMalloc] = '\0';
        for (size_t j = 0; j < i; j++){
            tab[i][sizeMalloc - 1] = '0';
            sizeMalloc--;
        }
        size_t index2 = size2;
        for(;sizeMalloc > 0; sizeMalloc--){
            if (index2 > 0){
                index2--;
                char num1 = s2[index2] - 48;
                char num2 = s1[size1 - i - 1] - 48;
                char num3 = (num1 * num2) + rest;
                tab[i][sizeMalloc - 1] = (num3 % 10) + 48;
                rest = num3 / 10;
            }else if (rest > 0){
                tab[i][sizeMalloc - 1] = rest + 48;
                rest = 0;
            }else{
                tab[i][sizeMalloc - 1] = '0';
            }
        }
        if (i == 0){
            str = strdup(tab[i]);
            if (tab[i] == NULL){
                free(tab);
                return NULL;
            }
            str = supprimZeroBeforeNumber(str);
        }
        else{
            char *str2 = str;
            str = add(str2, tab[i]);
            free(str2);
            if (str == NULL){
                while (i > 0){
                    free(tab[i - 1]);
                    i--;
                }
                free(tab);
                return NULL;
            }
        }
    }

    for (size_t i = 0; i < sizeTab; i++){
        free(tab[i]);
    }
    free(tab);
    if (isneg){
        char *str2 = join("-", str);
        free(str);
        return str2;
    }
    return str;
}


char *mul(char *s1, char *s2){
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
    bool isS1Float = isNumberFloat(s1);
    bool isS2Float = isNumberFloat(s2);
    if (!isS1Float && !isS2Float){
        return  mul_int(s1, s2, isneg);
    }
    return mul_float(s1, s2, isneg);
}