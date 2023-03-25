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

#include "computorV1.h"

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

int isGoodCharacter(char c){
    if ((c >= 45 && c <= 57) || c == 32 || c == 88 || (c >= 42 && c <= 43) || c == 94 || c == 61){
        return (1);
    }
    return (0);
}

char *  insertValueFromEquation(char *equation){
    int len = 0;
    char *val;
    while (equation[len] != '\0' && equation[len] != 32){
        len++;
    }
    if ((val = (char *)(malloc(sizeof(char) * (len + 1)))) == NULL)
        return NULL;
    for (int i = 0; i < len; i++){
        val[i] = equation[i];
    }
    val[len] = '\0';
    return val;
}

int isDouble(char *val){
    int point = 0;
    for (int i = 0; equation[i] != '\0'; i++){
        if (equation[i] == '.')
            point++;
        if (i == 0 && equation[i] == '.')
            return 0;
        if ((equation[i] < 48 || equation[i] > 57) && equation[i] == '.'){
            return 0;
        }
    }
    if (point > 1)
        return 0;
    return 1;
}

int findType(char *val, int len){
    if (len == 1){
        if (val[0] == '+') return ADD;
        else if (val[0] == '-') return SOUS;
        else if (val[0] == '/') return DIV
        else if (val[0] == '*') return MULT;
        else if (val[0] == '=') return EQ;
    }


}

void    saveData(char *equation, int *len, t_data **beginList){
    (void)beginList;
    int  type = 0;
    int lenVal = 0;
    char *val = NULL;
    val = insertValueFromEquation(equation);
    lenVal = strlen(val);
    type = findType(val, lenVal);
    printf("val = %s\n",val);
    *len += lenVal -1;
    free(val);
}

int parseData(char *equation, t_data **data){
    (void)data;
    for (int i = 0; equation[i] != '\0'; i++){
        if (equation[i] == 32) continue;
        saveData(equation + i, &i, data);
    }
    return 0;
}


int computorV1(char *equation){
    t_data  *data = NULL;
    int     res = 0;

    printf("equation : %s\n", equation);
    for (int i = 0; equation[i] != '\0'; i++){
        if (isGoodCharacter(equation[i]) == 0){
            return (1);
        }
    }
    if ((res = parseData(equation,&data)) != 0)
        return (res);
    return (0);
}

int main(int argc, char *argv[]){
    int res = 0;

    if (argc != 2 || (ft_strcmp(argv[0], "./computor") != 0 )){
        fprintf(stderr, "\e[0;31mWrong usage of %s\n\e[0m", "computor");
        return(EINVAL);
    }

    if ((res = computorV1(argv[1])) != 0)
        return (ft_error(res));
    return (0);
}





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