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

int saveOneBlockNumber(char *equation, int *len, t_data **beginList, int side){
    int type = NUMBER;
    double num = 0;
    int sup = 0;
    int div = 10;
    (void)div; (void)type; (void)beginList; (void)side;
    for (int i = 0; equation[i] != '\0' && (((equation[i] >= '0' && equation[i] <= '9') || (equation[i] == '.'))); i++){
        if (equation[i] == '.')
            sup++;
        else if (sup == 0){
            num *= 10;
            num += equation[i] - 48;
        }
        else if (sup == 1){
            num += (double)((double)(equation[i] - 48) / (double)div);
            div *= 10;
        }
        *len = *len + 1;
    }
    printf("num = %f\n", num);
    return 0;
}

int saveData(t_data **beginList, char *equation){
    int side = 0;
    for (int i = 0; equation[i] != '\0'; i++){
        if (equation[i] == 61)
            side++;
        else if (equation[i] >= 48 && equation[i] <= 57)
            saveOneBlockNumber(equation + i, &i, beginList, side);
        // if (equation[i] == 42 || equation[i] == 43 || equation[i] == 45 || equation[i] == 47)
        //     saveOneBlockSign(equation + i, beginList);
        // if (eqution[i] == 88)
        //     saveOneBlockPower(equation + i, beginList);
    }
    return (0);
}


int computorV1(char *equation){
    t_data  *data = NULL;

    printf("equation = %s\n", equation);
    for (int i = 0; equation[i] != '\0'; i++){
        if (isGoodCharacter(equation[i]) == 0){
            return (1);
        }
    }
    if (saveData(&data, equation) != 0){
        // clear data et return value error
    }
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