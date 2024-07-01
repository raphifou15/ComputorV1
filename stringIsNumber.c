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
    if (str[number_zero] == '.'){
        number_zero--;
    }
    size_t size = strlen(str);
    if (isneg)
        size -=  (number_zero - 1);
    else 
        size -= number_zero;
    char *s = (char *)malloc(sizeof(char) * (size + 1));
    if (s == NULL){
        free(str);
        return NULL;
    }
    s[size] = '\0';
    for (int i = 0; i < size; i++){
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
    if (size != 0 && str[size - 1] == '.')  size--;
    char *s = (char *)malloc(sizeof(char) * (size + 1));
    if (s == NULL){
        free(str);
        return NULL;
    }
    s[size] = '\0';
    for (int i = 0; i < size; i++){
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