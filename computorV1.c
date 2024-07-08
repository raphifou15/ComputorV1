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
        else if(s[i] == '/' || s[i] == '*' || s[i] == '+' || s[i] == '-'){
            struct values *tmp = malloc(sizeof(struct values));
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
        } else if (s[i] <= '9' && s[i] >= '0'){
            struct values *tmp = malloc(sizeof(struct values));
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
            char *tmpVal2 = malloc(sizeof(char) * (sizeNumber + 1));
            tmpVal2[sizeNumber] = '\0';
            for (size_t j = 0; j < sizeNumber; j++){
                tmpVal2[j] = s[i + j];
            }
            tmp->degree = atoi(tmpVal2);
            free(tmpVal2);
            i += sizeNumber - 1;
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
        } else if (s[i] == '='){
            struct values *tmp = malloc(sizeof(struct values));
            tmp->side = 2;
            side++;
            tmp->sign = 0;
            tmp->degree = -1;
            char *tmp2 = strdup("=");
            tmp->val = tmp2;
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
        }
    }
    return data;
}

struct values *multiplicationAndDivisionData(struct values *data){
    struct values *tmp = data;
    size_t i = 0;
    while (tmp != NULL){
        if (tmp->val[0] == '*'){
            char *val = mul(tmp->prev->val, tmp->next->val);
            int degree = tmp->prev->degree + tmp->next->degree;
            struct values *new = malloc(sizeof(struct values));
            new->side = tmp->side;
            new->sign = 0;
            new->degree = degree;
            new->val = val;
            if (i == 1){
                struct values *tmp2 = tmp;
                free(data->val);
                free(data);
                data = new;
                tmp = tmp->next;
                free(tmp2->val);
                free(tmp2);
                tmp2 = tmp;
                tmp = tmp->next;
                free(tmp2->val);
                free(tmp2);
                new->prev = NULL;
                new->next = tmp;
                tmp->prev = new;
                tmp = data;
                i = 0;
            }else{
                struct values *tmp2 = tmp;
                new->prev = tmp->prev->prev;
                new->prev->next = new;
                free(tmp->prev->val);
                free(tmp->prev);
                tmp = tmp->next;
                free(tmp2->val);
                free(tmp2);
                tmp2 = tmp;
                tmp = tmp->next;
                free(tmp2->val);
                free(tmp2);
                new->next = tmp;
                tmp->prev = new;
                i = 0;
                tmp = data;
            }
        }else if (tmp->val[0] == '/'){
            char *val = divi(tmp->prev->val, tmp->next->val);
            int degree = tmp->prev->degree - tmp->next->degree;
            struct values *new = malloc(sizeof(struct values));
            new->side = tmp->side;
            new->sign = 0;
            new->degree = degree;
            new->val = val;
            if (i == 1){
                struct values *tmp2 = tmp;
                free(data->val);
                free(data);
                data = new;
                tmp = tmp->next;
                free(tmp2->val);
                free(tmp2);
                tmp2 = tmp;
                tmp = tmp->next;
                free(tmp2->val);
                free(tmp2);
                new->prev = NULL;
                new->next = tmp;
                tmp->prev = new;
                tmp = data;
                i = 0;
            }else{
                struct values *tmp2 = tmp;
                new->prev = tmp->prev->prev;
                new->prev->next = new;
                free(tmp->prev->val);
                free(tmp->prev);
                tmp = tmp->next;
                free(tmp2->val);
                free(tmp2);
                tmp2 = tmp;
                tmp = tmp->next;
                free(tmp2->val);
                free(tmp2);
                new->next = tmp;
                tmp->prev = new;
                i = 0;
                tmp = data;
            }
        }
        tmp = tmp->next;
        i++; 
    }
    return data;
}

struct values * additionAndSubtractionData(struct values *data){
    struct values *tmp = data;
    struct values *tmpStrut;
    size_t i = 0;
    while (tmp != NULL){
        if (tmp->val[0] >= '0' && tmp->val[0] <= '9'){
            struct values *tmp2 = tmp->next;
            while (tmp2 != NULL){
                if (tmp2->degree == tmp->degree && tmp->sign == tmp2->sign && tmp2->val[0] >= '0' && tmp2->val[0] <= '9'){
                    char *valtmp = NULL;
                    if (i == 0){
                        valtmp = strdup(tmp->val);
                    }else if (tmp->prev->val[0] == '-'){
                        valtmp = join("-", tmp->val);
                    }else{
                        valtmp = strdup(tmp->val);
                    }
                    /////////// FAIRE ADDITION OU SOUSTRACTION //////////
                    char *val = NULL;
                    if (tmp2->prev->val[0] == '-'){
                        if (tmp2->side == 0){
                            val = sub(valtmp, tmp2->val);
                        }else{
                            val = add(valtmp, tmp2->val);
                        }
                    }else{
                        if (tmp2->side == 0){
                            val = add(valtmp, tmp2->val);
                        }else{
                            val = sub(valtmp, tmp2->val);
                        }
                    }
                    free(valtmp);
                    if (val[0] == '-' && i == 0){
                        struct values *new = malloc(sizeof(struct values));
                        new->degree = -1;
                        new->side = 0;
                        new->sign = 2;
                        new->val = strdup("-");
                        new->prev = NULL;
                        new->next = data;
                        data->prev = new;
                        data = new;
                        i++;
                    }
                    else if (val[0] == '-' && tmp->prev->val[0] == '='){
                        struct values *new = malloc(sizeof(struct values));
                        new->degree = -1;
                        new->side = 1;
                        new->sign = 2;
                        new->val = strdup("-");
                        struct values *tmp3 = tmp->prev;
                        tmp3->next = new;
                        new->prev = tmp3;
                        new->next = tmp;
                        tmp->prev = new;
                    }else if (val[0]  == '-' && tmp->prev->val[0] == '+'){
                        tmp->prev->val[0] = '-';
                    }else if (val[0]  != '-' && i != 0 && tmp->prev->val[0] == '-'){
                        tmp->prev->val[0] = '+';
                    }
                    free(tmp->val);
                    if (val[0] == '-'){
                        tmp->val = strdup(val + 1);
                        free(val);
                    }else{
                        tmp->val = val;
                    }
                    
                    if (tmp2->prev->val[0] == '='){
                        struct values *tmp3 = tmp2->prev;
                        tmp3->next = tmp2->next;
                        if (tmp2->next != NULL) tmp2->next->prev = tmp3;
                        free(tmp2->val);
                        free(tmp2);
                        tmp2 = tmp3;
                    }else{
                        struct values *tmp3 = tmp2->prev->prev;
                        tmp3->next = tmp2->next;
                        if (tmp2->next != NULL) tmp2->next->prev = tmp3;
                        free(tmp2->prev->val);
                        free(tmp2->prev);
                        free(tmp2->val);
                        free(tmp2);
                        tmp2 = tmp3;
                    }
                    
                }
                tmp2 = tmp2->next;
            }
        }
        
        tmp = tmp->next;
        i++;
    }
    return data;
}

void equation(char *s){
    if (isSyntaxError2(s) == false){
        fprintf(stderr, "syntax error\n");
        return;
    }
    struct values *data = parseData(s);
    // creer une fonction qui fait les multiplications de chaque coter.
    data = multiplicationAndDivisionData(data);
    // creer une fonction qui fait les additions et soustraction de chaque coter.
    data = additionAndSubtractionData(data);
    // faire une fonction qui supprimme tout les 0
    
    // creer une fonction qui met tous les nombres du coter gauche.
    // creer une fonction qui reduit au maximum le resultat.
    // creer une fonction qui deduit le degrees de l'equation.
    // si equation second degree.
    // creer plusieur fonction en fonction du discriminant.
    // si equation premier degree 1 solution.
    // si equation de degrer zero toutes les solutions de x sont possible.
    printf("s = %s\n", s);
    struct values *tmp = data;
    
    while (tmp != NULL){
        printf("%s ", tmp->val);
        tmp = tmp->next; 
    }
    printf("\n");
    tmp = data;
    while (tmp != NULL){
        struct values *tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2->val);
        free(tmp2);
    }
}

int main(int argc, char **av) {
    if (argc != 2) return 0;
    equation(av[1]);
    // The equation in its reduced form
    // The degree of the equation.
    // It’s solution(s) and the polarity of the discriminant if it makes sens.
    return 0;
}