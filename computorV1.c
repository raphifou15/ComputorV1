// show the equation in its reduced form
// The degree of the equation
// It’s solution(s) and the polarity of the discriminant if it makes sens

// pour calculer le delta il faut faire b au carre - 4ac

// si delta > 0 l'equation admet deux solutions:
// x1 = ((-b - racine carre de delta) / 2a)
// x2 = ((-b + racine carre de delta) / 2a)

// si delta == 0 l'equation admet une solution  x0 = ((-b) / (2a))

// si delta < 0 l'equation n'admet pas de solution reelle, mais deux solutions complexes:
// x1 = ((-b - i racine carre de -delta) / (2a))
// x2 = ((-b + i racine carre de -delta) / (2a))



// mettre la facon dont c'est ecrit.

// fason 1 ecriture avec x et puissance;
// fason 2 ecriture avec x;
// fason 3 ecriture sans x;


#include "computorV1.h"

int ft_strlen_float(char *str, int *lenAfter){
    int i = 0;
    int k = -1;
    while (str[i] != '\0'){
        if (k >= 0)
            k++;
        if (str[i] == '.')
            k = 0;
        i++;
    }
    *lenAfter = k;
    return i;
}

int ft_strcmp(char *s1, char *s2){
    if (s1 == NULL || s2 == NULL)
        return (s1 - s2);
    int i = 0;
    for (; s1[i] != '\0'; i++){
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    }
    return (s1[i] - s2[i]);
}

int ft_error(int res){
    if (res == 1){
        fprintf(stderr, "\e[0;31mWrong character used\n\e[0m");
    }
    return 1;
}

char *join(char *res, char c){
    char *res2 = NULL;
    int len = 0;
    if (res == NULL){
        if ((res2 = malloc(sizeof(char) * 2)) == NULL)
            return res2;
        res2[0] = c;
        res2[1] = '\0';
        return res2;
    }
    len = strlen(res);
    if ((res2 = malloc(sizeof(char) * (len + 2))) == NULL)
        return res2;
    res2[0] = c;
    for (int i = 0; res[i] != '\0'; i++)
        res2[i + 1] = res[i];
    res2[len + 1] = '\0';
    free(res);
    res = NULL;
    return res2;
}

char *addString(char *str1, char *str2){
    char    *res = NULL;
    int     len1 = 0;
    int     len2 = 0;
    int     lenAfterPos1 = 0;
    int     lenAfterPos2 = 0;
    char    c = 0;
    char    nval = 0;

    if (str1 == NULL || str2 == NULL)
        return NULL;
    len1 = ft_strlen_float(str1, &lenAfterPos1);
    len2 = ft_strlen_float(str2, &lenAfterPos2);

    while (len1 > 0 || len2 > 0 || c > 0){
        if (lenAfterPos1 > 0 || lenAfterPos2 > 0){
            if ((lenAfterPos1 == lenAfterPos2) && (lenAfterPos1 > 0)){
                lenAfterPos1--; lenAfterPos2--; len1--; len2--;
                c = c + (str1[len1] - 48) + (str2[len2] - 48);
            }
            else if (lenAfterPos1 > lenAfterPos2){
                lenAfterPos1--; len1--;
                c = c + (str1[len1] - 48);
            }
            else if (lenAfterPos1 < lenAfterPos2){
                lenAfterPos2--; len2--;
                c = c + (str2[len2] - 48);
            }
            nval = c % 10;
            c = c / 10;
            res = join(res, nval + 48);
        }
        else{
            len1--;
            len2--;
            if (len1 >= 0 && len2 >= 0 && (str1[len1] == '.' || str2[len2] == '.')){
                res = join(res, '.');
                if (str1[len1] == '.'){
                    len1--;
                }
                if (str2[len2] == '.'){
                    len2--;
                }
                    
            }
            if (len1 >= 0 && len2 >= 0)
                c = c + (str1[len1] - 48) + (str2[len2] - 48);
            else if (len1 >= 0 && len2 < 0)
                c = c + (str1[len1] - 48);
            else if (len1 < 0 && len2 >= 0)
                c = c + (str2[len2] - 48);
            nval = c % 10;
            c = c / 10;
            res = join(res, nval + 48);
        }
    }
    return res;
}

int main(int argc, char *argv[]){
    int res = 0;
    char *val = NULL;

    if (argc != 3)
        return 0;
    (void)res;
    // if (argc != 2 || (ft_strcmp(argv[0], "./computor") != 0 )){
    //     fprintf(stderr, "\e[0;31mWrong usage of %s\n\e[0m", "computor");
    //     return(EINVAL);
    // }

    val = addString(argv[1], argv[2]);
    printf("val = %s\n", val);
    if (val != NULL){
        free(val);
        val = NULL;
    }
    
    // if ((res = computorV1(argv[1])) != 0)
    //     return (ft_error(res));
    return (0);
}






// int isGoodCharacter(char c){
//     if ((c >= 45 && c <= 57) || c == 32 || c == 88 || (c >= 42 && c <= 43) || c == 94 || c == 61){
//         return (1);
//     }
//     return (0);
// }

// char *  insertValueFromEquation(char *equation){
//     int len = 0;
//     char *val;
//     while (equation[len] != '\0' && equation[len] != 32){
//         len++;
//     }
//     if ((val = (char *)(malloc(sizeof(char) * (len + 1)))) == NULL)
//         return NULL;
//     for (int i = 0; i < len; i++){
//         val[i] = equation[i];
//     }
//     val[len] = '\0';
//     return val;
// }

// int isDouble(char *val){
//     int point = 0;
//     for (int i = 0; val[i] != '\0'; i++){
//         if (val[i] == '.')
//             point++;
//         if (i == 0 && val[i] == '.')
//             return 0;
//         if ((val[i] < 48 || val[i] > 57) && val[i] != '.'){
//             return 0;
//         }
//     }
//     if (point > 1)
//         return 0;
//     return 1;
// }

// int findType(char *val, int len){
//     if (len == 1){
//         if (val[0] == '+') return ADD;
//         else if (val[0] == '-') return SOUS;
//         else if (val[0] == '/') return DIV;
//         else if (val[0] == '*') return MULT;
//         else if (val[0] == '=') return EQ;
//         else if (val[0] == 'X') return POWER;
//     }
//     if (isDouble(val) == 1) return FACTOR;
//     if (val[0] == 'X' && val[1] == '^' && isDouble(val + 2) == 1) return POWER;
//     return WRONG;
// }

// double  toDouble(char *val){
//     double  nb = 0;
//     int     point = 0;
//     double  div = 10;

//     if (val == NULL || val[0] == '.')
//         return -1;
//     for (int i = 0; val[i] != '\0'; i++){
//         if (val[i] == '.')
//             point++;
//         else if (point == 0 && (val[i] >= 48 && val[i] <= 57)){
//             nb *= 10;
//             nb += (val[i] - 48);
//         }
//         else if (point == 1 && (val[i] >= 48 && val[i] <= 57)){
//             nb += (double)((val[i] - 48) / div);
//             div *= 10;
//         }
//         else 
//             return -1;
//     }
//     return nb;
// }

// void    putToList(t_data **beginList, t_data *data){
//     t_data *new = NULL;
//     t_data *temp = NULL;
//     temp = *beginList;
//     new = malloc(sizeof(struct s_data));
//     new->val = data->val;
//     new->value = data->value;
//     new->type = data->type;
//     new->side = data->side;
//     new->next = data->next;
//     new->prev = data->prev;
//     if (temp == NULL){
//         *beginList = new;
//         return ;
//     }
//     while (temp->next != NULL){
//         temp = temp->next;
//     }
//     temp->next = new;
//     new->prev = temp;
// }




// void    saveData(char *equation, int *len, t_data **beginList, int *side){
//     t_data data;

//     data.type = 0;
//     int lenVal = 0;
//     data.value = 0;
//     data.val = NULL;
//     data.next = NULL;
//     data.prev = NULL;

//     data.val = insertValueFromEquation(equation);
//     lenVal = strlen(data.val);
//     data.type = findType(data.val, lenVal);
//     if (data.type == EQ)
//         *side = RIGHT;
//     data.side = *side;
//     data.value = (data.type == FACTOR) ? toDouble(data.val) : (data.type == POWER && lenVal == 1) ? 1 : (data.type == POWER) ? toDouble(data.val + 2) : 0;
//     putToList(beginList, &data);
//     // printf("side = %d type = %d val = %s value = %f\n",data.side, data.type, data.val, data.value);
//     *len += lenVal -1;
// }

// int parseData(char *equation, t_data **data){
//     (void)data;
//     int side = LEFT;

//     for (int i = 0; equation[i] != '\0'; i++){
//         if (equation[i] == 32) continue;
//         saveData(equation + i, &i, data, &side);
//     }
//     return 0;
// }

// void displayList(t_data **beginList){
//     t_data *temp = *beginList;
//     while (temp != NULL){
//         printf("side = %d type = %d val = %s value = %f\n", temp->side, temp->type, temp->val, temp->value);
//         temp = temp->next;
//     }
// }

// void clearListData(t_data **list){
//     t_data *temp = *list;
//     t_data *temp2 = *list;
//     while (temp != NULL){
//         temp2 = temp;
//         temp = temp->next;
//         free(temp2->val);
//         free(temp2);
//     }
// }

// int equationIsReduce(t_data **beginList, int *pos1, int *pos2){
//     t_data *temp = *beginList;
//     t_data *temp2 = *beginList;
//     int p1 = 0;
//     int p2 = 0;

//     while (temp !== NULL){
//         while (temp != NULL && temp->type !== POWER)
//             temp = temp->next;
//         temp2 = temp->next;
//         while (temp2 != NULL){
//             if (temp2->type == POWER && temp2->value == temp->value)
//                 return 0;
//             temp2 = temp2->next;
//         }

//     }
//     return (1);
// }

// void    reduceEquation(t_data **beginList){
//     int pos1 = 0;
//     int pos2 = 0;
//     while (equationIsReduce(beginList, &pos1, &pos2) == 0){
        
//     }
// }

// int computorV1(char *equation){
//     t_data  *data = NULL;
//     int     res = 0;

//     printf("equation : %s\n", equation);
//     for (int i = 0; equation[i] != '\0'; i++){
//         if (isGoodCharacter(equation[i]) == 0){
//             return (1);
//         }
//     }
//     if ((res = parseData(equation, &data)) != 0)
//         return (res);
//     // reduceEquation(&data);
//     displayList(&data);
//     clearListData(&data);
//     return (0);
// }


// int saveData(t_data **beginList, char *equation){
//     int side = 0;
//     for (int i = 0; equation[i] != '\0'; i++){
//         if (equation[i] == 61)
//             side++;
//         else if (equation[i] >= 48 && equation[i] <= 57)
//             saveOneBlockNumber(equation + i, &i, beginList, side);
//         // if (equation[i] == 42 || equation[i] == 43 || equation[i] == 45 || equation[i] == 47)
//         //     saveOneBlockSign(equation + i, beginList);
//         // if (eqution[i] == 88)
//         //     saveOneBlockPower(equation + i, beginList);
//     }
//     return (0);
// }

// int saveOneBlockNumber(char *equation, int *len, t_data **beginList, int side){
//     int type = NUMBER;
//     double num = 0;
//     int sup = 0;
//     int div = 10;
//     (void)div; (void)type; (void)beginList; (void)side;
//     for (int i = 0; equation[i] != '\0' && (((equation[i] >= '0' && equation[i] <= '9') || (equation[i] == '.'))); i++){
//         if (equation[i] == '.')
//             sup++;
//         else if (sup == 0){
//             num *= 10;
//             num += equation[i] - 48;
//         }
//         else if (sup == 1){
//             num += (double)((double)(equation[i] - 48) / (double)div);
//             div *= 10;
//         }
//         *len = *len + 1;
//     }
//     printf("num = %f\n", num);
//     return 0;
// }

// void    print_float(double nb, int fd){
//     if (nb < 0){
//         nb *= -1;
//         write('-')
//     }
// }


// int parseData(char *equation, t_data **left, t_data **right){
//     int side = 0;
//     (void)equation; (void)left; (void)right;
//     for (int i = 0; equation[i] != '\0'; i++){
//         if (equation[i] == '=')
//             side++;
//         else if (side == 0){
//             saveData(left, equation + i, &i);
//         }
//     }
//     // ici il faudra recuperer les donner une a une 
//     // si une seul donner n'ai pas correctement ecrit renvoyer une erreur.
//     // parcourir la string equation et renplir au fur et a mesur les donner dans une data.
//     return 0;
// }

// void    saveData(t_data **BeginList, char *equation, int *len){
//     (void)BeginList;
//     double power = 0;
//     double factor = 0;
//     printf("equation = %s\n", equation);
//     for (int i = 0; equation[i] != '\0'; i++){
//         if (equation[i] == 32) continue;
//         else if ()
//         *len = *len + 1;
//     }
// }