#include "math.h"

struct lenPointNumber strlenNumberPoint(char *str){
    struct lenPointNumber lpn;
    lpn.indexAPt = 0;
    lpn.indexBPt = 0;

    bool afterPoint = false;  
    for(long i = 0; str[i] != '\0'; i++){
        if (str[i] == '.') afterPoint = true;
        if (afterPoint){
            lpn.indexAPt++;
        }else{
            lpn.indexBPt++;
        }
    }
    return lpn;
}

char * supprimZeroBeforeNumber(char *str){
    if (str == NULL) return NULL;
    size_t number_zero = 0;
    bool isneg = false;
    if (str[0] == '-')  isneg = true;
    if (isneg == true)
        number_zero++;
    while (str[number_zero] != '\0' && (str[number_zero] == '0')){
        number_zero++;
    }
    if (str[number_zero] == '\0'){
        free(str);
        char *s = malloc(sizeof(char) * (1 + 1));
        if (s == NULL) return NULL;
        s[0] = '0';
        s[1] = '\0';
        return s;
    }
    if (str[number_zero] == '.'){
        number_zero--;
    }
    size_t size = strlen(str);
    if (isneg)
        size -= (number_zero - 1);
    else 
        size -= number_zero;
    char *s = (char *)malloc(sizeof(char) * (size + 1));
    if (s == NULL){
        free(str);
        return NULL;
    }
    s[size] = '\0';
    for (size_t i = 0; i < size; i++){
        if (isneg){
            if (i == 0)
                s[i] = '-';
            else{
                s[i] = str[number_zero - 1];
            } 
        }else{
            s[i] = str[number_zero];
        }
        number_zero++;
    }
    free(str);
    return s;
}

char * supprimZeroAfterNumber(char *str){
    if (str == NULL) return NULL;
    size_t size = 0;
    while (str[size] != '\0'){
        size++;
    }
    while (size != 0 && str[size - 1] == '0')   size--;
    if (size == 0){
        free(str);
        char *s = malloc(sizeof(char) * (1 + 1));
        if (s == NULL) return NULL;
        s[0] = '0';
        s[1] = '\0';
        return s;
    }
    if (size != 0 && str[size - 1] == '.')  size--;
    char *s = (char *)malloc(sizeof(char) * (size + 1));
    if (s == NULL){
        free(str);
        return NULL;
    }
    s[size] = '\0';
    for (size_t i = 0; i < size; i++){
        s[i] = str[i];
    }
    free(str);
    return s;
}

bool isOnlyNumber(char *s1){
    if (s1 == NULL) return false;
    int point = 0;
    char *s2 = s1;
    int i = 0;
    while(*s2 != '\0'){
        if (i == 0 && *s2 == '.') return false;
        if (i == 0) i = 1;
        if (point == 0 && *s2 == '.'){
            point++;
        }
        else if (*s2 < '0' || *s2 > '9') return false;
        s2++;
    }
    s2--;
    if (*s2 == '.') return false;
    return true;
}

bool isNumberFloat(char *str){
    char *s = str;
    while (*s != '\0'){
        if (*s == '.') return true;
        s++;
    }
    return false;
}

char *join (char *s1, char *s2){
    size_t size1 = strlen(s1);
    size_t size2 = strlen(s2);
    size_t size = size1 + size2;
    char *s = malloc(sizeof(char) * (size + 1));
    if (s == NULL) return NULL;
    s[size] = '\0';
    int i = 0;
    while(s1[i] != '\0'){
        s[i] = s1[i];
        i++;
    }
    int j = 0;
    while(s2[j] != '\0'){
        s[i] = s2[j];
        j++;
        i++;
    }
    return s;
}

void decalValueOne(char *s){
    for (size_t i = 0; s[i] != '\0'; i++){
        if (s[i] == '.'){
            char c = s[i];
            s[i] = s[i + 1];
            s[i + 1] = c;
            i++;
        }
    }
    if (s[0] == '0'){
        for (size_t i = 0; s[i] != '\0'; i++){
            if (s[i + 1] == '\0'){
                s[i] = '0';
            }
            else{
                s[i] = s[i + 1];
            }
        }
    }
}


char *decalValue(char *s, struct lenPointNumber lpns1, struct lenPointNumber lpns2){
    size_t sizeMalloc = lpns1.indexAPt + lpns1.indexBPt + lpns2.indexAPt + lpns2.indexBPt;
    char *str = malloc(sizeof(char) * (sizeMalloc + 1));
    if (str == NULL) return NULL;
    str[sizeMalloc] = '\0';
    bool isPoint = false;
    for (size_t i = 0; i < sizeMalloc; i++){
        if ((long)i < lpns2.indexBPt + lpns2.indexAPt){
            str[i] = s[i];
            if (s[i] == '.') isPoint = true;
        }
        else{
            if (isPoint == false){
                isPoint = true;
                str[i] = '.';
            }else
                str[i] = '0';
        }
    }
    
    if (lpns1.indexAPt == 0)
        return str;
    
    size_t dec = lpns1.indexAPt - 1;
    while (dec > 0){
        for (size_t i = 0; i < sizeMalloc; i++){
            if (str[i] == '.'){
                str[i] = str[i - 1];
                str[i - 1] = '.';
                break;
            }
        }
        if (str[0] == '.'){
            for (size_t i = sizeMalloc ; i > 0; i--){
                if (i == 1){
                    str[i - 1] = '0';
                }
                else{
                    str[i - 1] = str[i - 2];
                }
            }
        }
        dec--;
    }
    // printf("str2 final = %s\n", str);
    return str;
}

// si le nombre 1 est plus grand renvoie 1;
// si le mombre 1 est egal renvoie 0;
// si le nombre 1 est plus petit renvoie -1;
int numberBigerLowerEqual(char *s1, char *s2){
    struct lenPointNumber val1 = strlenNumberPoint(s1);
    struct lenPointNumber val2 = strlenNumberPoint(s2);

    if (s1[0] == '-' && s2[0] != '-') return -1;
    else if (s1[0] != '-' && s2[0] == '-') return 1;
    size_t i = 0;
    if (val1.indexBPt > val2.indexBPt) return 1;
    else if (val1.indexBPt < val2.indexBPt) return -1;
    else{
        for(; s1[i] != '\0' && s2[i] != '\0'; i++){
            if (s1[i] > s2[i]) return 1;
            else if (s1[i] < s2[i]) return -1;
        }
    }
    if (s1[i] == s2[i]) return 0;
    else if(s1[i] > s2[i]) return 1;
    else return -1;
}

char * joinTab(char **tab){
    size_t finalSize = 0;
    for (int i = 0; tab[i] != NULL; i++){
        size_t size = strlen(tab[i]);
        finalSize += size;
    }
    char *str = malloc(sizeof(char) * finalSize + 1);
    if (str == NULL)
        return NULL;
    str[finalSize] = '\0';
    finalSize = 0;
    for (int i = 0; tab[i] != NULL; i++){
        for (int j = 0; tab[i][j] != '\0'; j++){
            str[finalSize] = tab[i][j];
            finalSize ++;
        }
    }
    return str;
}