#include "math.h"

struct values{
    int             side; //0 left, 1 right, 2 middle;
    int             sign; // 0: pas de sign, 1:+, 2:-, 3:*, 4:/     
    int             degree;
    char            *val;
    struct values   *next;
    struct values   *prev;
};

static size_t sizeNumberFloat(char *s){
    size_t i = 0;
    while (s[i] != '\0' && s[i] != 32){
        i++;
    }
    return i;
}


static size_t checkNumberInt(char *s){
    size_t i = 0;
    while (s[i] != '\0' && s[i] != 32){
        if (s[i] < '0' || s[i] > '9')
            return 0;
        i++;
    }
    return i;
}

static size_t checkNumber(char *s){
    bool isPoint = false;
    size_t i = 0;
    for (; s[i] != '\0' && s[i] != 32; i++){
        if (s[i] == '.' && isPoint == true) return 0;
        if (s[i] == '.' && (s[i + 1] == '\0' || s[i + 1] == 32)){
            return 0;
        }
        if (isPoint == false && s[i] == '.'){
            isPoint = true;
            continue;
        }
        if (s[i] < '0' || s[i] > '9'){
            return 0;
        }
    }
    return i;
}

// static bool isSyntaxError(char *s){
//     bool haveSpace = false;
//     for (size_t i = 0; s[i] != '\0'; i++){
//         if (s[i] != 32 && haveSpace) return false;
//         else if(s[i] == 32){
//             haveSpace = false;
//         }
//         else if(i == 0 && (s[i] == '*' || s[i] == '/')) return false;
//         else if(s[i + 1] == '\0' && (s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-')){
//             return false;
//         }
//         else if(s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-'){
//             haveSpace = true;
//         }
//         else if(s[i] >= '0' && s[i] <= '9'){
//             size_t y = checkNumber(s + i);
//             if (y == 0) return false; 
//             i += y - 1;
            
//             haveSpace = true;
//         }
//         else if(s[i] == 'X'){
//             if (s[i + 1] != '^') return false;
//             i++;
//             if (s[i + 1] < '0' || s[i + 1] > '9') return false;
//             i++;
//             size_t y = checkNumber(s + i);
//             if (y == 0) return false; 
//             i += y - 1;
//             haveSpace = true;
//         }
//         else{
//             return false;
//         }
//     }
//     return true;
// }

bool isSyntaxError2(char *s){
    bool haveSpace = false;
    bool equal = false;
    bool sign = true;
    for (size_t i = 0; s[i] != '\0'; i++){
        if (s[i] != 32 && haveSpace) return false;
        if (s[i] == 32){
            haveSpace = false;
        }
        else if (s[i] <= '9' && s[i] >= '0'){
            size_t y = checkNumber(s + i);
            if (y == 0) return false; 
            i += y;
            if (s[i] != 32) return false;
            i++;
            if (s[i] != '*') return false;
            i++;
            if (s[i] != 32) return false;
            i++;
            if (s[i] != 'X') return false;
            i++;
            if (s[i] != '^') return false;
            i++;
            y = checkNumberInt(s + i);
            if (y == 0) return false;
            i += y - 1;
            haveSpace = true;
            sign = false;
        }
        else if ((i == 0) && s[i] == '-'){
            sign = true;
            haveSpace = true;
        }
        else if ((i != 0) && (s[i] == '/' || s[i] == '*' || s[i] == '+' || s[i] == '-') && sign == false){
            sign = true;
            haveSpace = true;
        }
        else if ((s[i + 1] == '\0' || s[i + 2] == '=') && (s[i] == '/' || s[i] == '*' || s[i] == '+' || s[i] == '-')){
            return false;
        }
        else if (s[i] == '=' && equal == false){
            equal = true;
        }
        else if (s[i] == '=' && equal == true){
            return false;
        }else{
            return false;
        }
    }
    if (equal == false) return false;
    return true;
}

struct values * parseData(char *s){
    struct values *data = NULL;
    int side = 0;
    for (size_t i = 0; s[i] != '\0'; i++){
        if (s[i] == 32){continue;}
        else if(s[i] == '/' && s[i] == '*' && s[i] == '+' && s[i] == '-'){
            struct values *tmp = malloc(sizeof(data));
            char *tmp2 = NULL;
            tmp->side = side;
            if (s[i] == '+'){
                tmp->sign = 1;
                tmp->val = strdup("+");
            }
            else if (s[i] == '-'){
                tmp->sign = 2;
                tmp->val = strdup("-");
            }
            else if (s[i] == '*'){
                tmp->sign = 3;
                tmp->val = strdup("*");
            }
            else if (s[i] == '/'){
                tmp->sign = 4;
                tmp->val = strdup("/");
            }
            tmp->degree = -1;
            if (data == NULL){
                data = tmp;
                data->next = NULL;
                data->prev = NULL;
            }else{
                struct values *tmpData = data;
                while (tmpData->next != NULL){
                    tmpData = tmpData->next;
                }
                tmpData->next = tmp;
                tmp->next = NULL;
                tmp->prev = tmpData;
            }
        }else if (s[i] <= '9' && s[i] >= '0'){
            struct values *tmp = malloc(sizeof(data));
            tmp->side = side;
            tmp->sign = 0;
            size_t sizeNumber = sizeNumberFloat(s + i);
            char *tmpVal = malloc(sizeof(char) * (sizeNumber + 1));
            tmpVal[sizeNumber] = '\0';
            for (size_t j = 0; j < sizeNumber; j++){
                tmpVal[j] = s[i + j];
            }
            tmp->val = tmpVal;
            i += sizeNumber;
            i += 5;
            sizeNumber = checkNumberInt(s + i);
            tmpVal = malloc(sizeof(char) * (sizeNumber + 1));
            tmpVal[sizeNumber] = '\0';
            for (size_t j = 0; j < sizeNumber; j++){
                tmpVal[j] = s[i + j];
            }
            tmp->degree = atoi(tmpVal);
            free(tmpVal);
        }
    }
    return NULL;
}

void equation(char *s){
    if (isSyntaxError2(s) == false){
        fprintf(stderr, "syntax error\n");
        return;
    }
    struct values *data = parseData(s);
    printf("s = %s\n", s);    
}

int main(int argc, char **av) {
    if (argc != 2) return 0;
    equation(av[1]);
    // The equation in its reduced form
    // The degree of the equation.
    // It’s solution(s) and the polarity of the discriminant if it makes sens.
    return 0;
}