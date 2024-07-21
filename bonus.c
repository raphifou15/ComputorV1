#include "computorV1.h"
void   bonusActivate(void){
    printf("bonus is activated\n");
}

static size_t sizeNumberFloat(char *s){
    size_t i = 0;
    while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.'){
        i++;
    }
    return i;
}

static size_t sizeNumberInt(char *s){
    size_t i = 0;
    while ((s[i] >= '0' && s[i] <= '9')){
        i++;
    }
    return i;
}

void displayCalcul(char *val1, char *val2, int degree, char sign){
    printf("Calcul : ");
    if (degree == 0){
        printf("%s %c %s\n", val1, sign, val2);
    }else if(degree == 1){
        printf("%sX %c %sX\n", val1, sign, val2);
    }else{
        printf("%sX^%d %c %sX^%d\n",val1, degree, sign, val2, degree);
    }
}

void  displayDataBonus(struct values *data, bool reduce){
    struct values *tmp = data;
    struct values *tmp2 = NULL;
    size_t i = 0;
    if (reduce == true) printf("Reduced form: ");
    else {
        printf("Intermediate Step  ");
    }
    while (tmp != NULL){
        tmp2 = tmp;
        if (i == 0 && tmp->val[0] == '='){
            printf("0 %s ", tmp->val);
        }
        else if(tmp->val[0] == '='){
            printf("%s ", tmp->val);
        }
        else if(tmp->val[0] >= '0' && tmp->val[0] <= '9'){
            if (tmp->degree == 0){printf("%s ", tmp->val);}
            else if(tmp->degree == 1){
                printf("%sX ", tmp->val);
            }else printf ("%sX^%d ", tmp->val, tmp->degree);
        }
        else{
            printf("%s ", tmp->val);
        }
        tmp = tmp->next;
        i++;
    }
    if (tmp2->val[0] == '='){
        printf("0 ");
    }
    printf("\n");
}

static size_t checkNumber(char *s){
    bool isPoint = false;
    size_t i = 0;
    for (; s[i] != '\0' && s[i] != 32; i++){
        if (s[i] == '.' && isPoint == true) return 0;
        if (s[i] == '.' && (s[i + 1] == '\0' || s[i + 1] == 32 || (s[i + 1] < '0' || s[i + 1] > '9'))){
            return 0;
        }
        if (isPoint == false && s[i] == '.'){
            isPoint = true;
            continue;
        }
        if (s[i] < '0' || s[i] > '9'){
            return i;
        }
    }
    return i;
}

static size_t checkNumberInt(char *s){
    size_t i = 0;
    while (s[i] != '\0' && s[i] != 32){
        if (s[i] < '0' || s[i] > '9')
            return i;
        i++;
    }
    return i;
}

bool isSyntaxErrorBonus(char *s){
    bool equal = false;
    bool sign = true;
    bool afterEqual = false;
    bool number = true;
    for (size_t i = 0; s[i] != '\0'; i++){
        if (s[i] == 32) continue;
        else if (sign == false && s[i] == '='){
            fprintf(stderr, "Syntax error\nThere is an error in this equation %s\nThere is a sign before =\n", s);
            return false;
        }
        else if (s[i] == '=' && equal == false){equal = true; number = true;}
        else if (s[i] == '=' && equal == true){
            fprintf(stderr, "Syntax error\nThere is an error in this equation %s\nThere is two equal '='\n", s);
            return false;
        }
        else if ((s[i] >= '0' && s[i] <= '9') && number == true){
            number = false;
            size_t y = checkNumber(s + i);
            if (equal == true){
                afterEqual = true;
            }
            if (y == 0){
                fprintf(stderr, "Syntax error\nThere is an error in this equation %s\nThe number is not good\n", s);
                return false;
            } 
            i += y;
            while (s[i] == 32) i++;
            if (s[i] != '*' && s[i] != 'X'){--i; sign = true; continue;}
            if (s[i] == '*'){
                i++;
                while (s[i] == 32) i++;
                if (s[i] != 'X'){
                    while (s[i] != '*') i--;
                    i--; sign = true; continue;
                }
            }
            i++;

            if (s[i] != '^'){--i; sign = true; continue;}
            i++;
            while (s[i] == 32) i++;
            if (s[i] >= '0' && s[i] <= '9'){
                y = checkNumberInt(s + i);
                if (y == 0){
                    fprintf(stderr, "Syntax error\nThere is an error in this equation %s\n %c is a wrong parameter\nPut a number in int for the power", s, s[i]);
                    return false;
                }
                i += y - 1;
                sign = true;
            }
            else{
                fprintf(stderr, "Syntax error\nThere is an error in this equation %s\n %c is a wrong parameter\nPut a number in int for the power", s, s[i]);
                return false;
            }
        }else if (sign == true && (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*')) {
            if (number == true && s[i] != '-'){
                fprintf(stderr, "Syntax error\nThere is an error in this equation %s\nthere is a sign before the first number\n", s);
                return false;
            }
            sign = false; number = true;
        }
        else if(s[i] == 'X' && number == true){
            number = false;
            if (equal == true){
                afterEqual = true;
            }
            i++;
            while (s[i] == 32) i++;
            if (s[i] != '^'){--i; sign = true; continue;}
            i++;
            while (s[i] == 32) i++;
            if (s[i] >= '0' && s[i] <= '9'){
                size_t y = checkNumberInt(s + i);
                if (y == 0){
                    fprintf(stderr, "Syntax error\nThere is an error in this equation %s\n %c is a wrong parameter\nPut a number in int for the power", s, s[i]);
                    return false;
                }
                i += y - 1;
                sign = true;
            }
            else{
                fprintf(stderr, "Syntax error\nThere is an error in this equation %s\n %c is a wrong parameter\n", s, s[i]);
                return false;
            }
        }else{
            fprintf(stderr, "Syntax error\nThere is an error in this equation %s\n %c is a wrong parameter\n", s, s[i]);
            return false;
        }
    }
    if (equal == false){
        fprintf(stderr, "Syntax error\nThere is an error in this equation %s\nMissing equal\n", s);
        return false;
    }
    if (afterEqual == false){
        fprintf(stderr, "Syntax error\nThere is an error in this equation %s\nMissing number after equal\n", s);
        return false;
    }
    if (sign == false){
        fprintf(stderr, "Syntax error\nThere is an error in this equation %s\nThe equation finnish by a sign\n", s);
        return false;
    }
    return true;
}

struct values * parseDataBonus(char *s){
    struct values *data = NULL;
    int side = 0;
    for (size_t i = 0; s[i] != '\0'; i++){
        if (s[i] == 32){continue;}
        else if(s[i] == '/' || s[i] == '*' || s[i] == '+' || s[i] == '-'){
            struct values *tmp = malloc(sizeof(struct values));
            tmp->display = NULL;
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
            tmp->display = NULL;
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
            //// change here ////
            while(s[i] == 32) i++;
            if (s[i] != '*' && s[i] != 'X'){tmp->degree = 0; --i;}
            else{
                if (s[i] == '*'){
                    i++;
                    while (s[i] == 32) i++;
                }if (s[i] != 'X' ){
                    while (s[i] != '*') i--;
                    i--;
                
                }
                else if (s[i] == 'X' && s[i + 1] != '^'){
                    tmp->degree = 1;
                }else{
                    i += 2;
                    sizeNumber = sizeNumberInt(s + i);
                    char *tmpVal2 = malloc(sizeof(char) * (sizeNumber + 1));
                    tmpVal2[sizeNumber] = '\0';
                    for (size_t j = 0; j < sizeNumber; j++){
                        tmpVal2[j] = s[i + j];
                    }
                    tmp->degree = atoi(tmpVal2);
                    free(tmpVal2);
                    i += sizeNumber - 1;
                }
            }
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
        else if(s[i] == 'X'){
            struct values *tmp = malloc(sizeof(struct values));
            tmp->display = NULL;
            tmp->side = side;
            tmp->sign = 0;
            char *tmpVal = malloc(sizeof(char) * (2));
            tmpVal[0] = '1';
            tmpVal[1] = '\0';
            tmp->val = tmpVal;
            i++;
            if (s[i] != '^'){tmp->degree = 0; --i;}
            else{
                i++;
                size_t sizeNumber = sizeNumberInt(s + i);
                char *tmpVal2 = malloc(sizeof(char) * (sizeNumber + 1));
                tmpVal2[sizeNumber] = '\0';
                for (size_t j = 0; j < sizeNumber; j++){
                    tmpVal2[j] = s[i + j];
                }
                tmp->degree = atoi(tmpVal2);
                free(tmpVal2);
                i += sizeNumber - 1;
            }
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
        else if (s[i] == '='){
            struct values *tmp = malloc(sizeof(struct values));
            tmp->display = NULL;
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