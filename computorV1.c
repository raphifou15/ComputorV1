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

bool isSyntaxError(char *s){
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
                        if (tmp2->side == tmp->side){
                            val = sub(valtmp, tmp2->val);
                        }else{
                            val = add(valtmp, tmp2->val);
                        }
                    }else{
                        if (tmp2->side == tmp->side){
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

struct values * supprimZeroOfData(struct values *data){
    struct values *tmp = data;
    while (tmp != NULL){
        if (tmp->val[0] == '0' && tmp->prev == NULL){
            struct values *tmp2 = tmp;
            tmp = tmp->next;
            free(tmp2->val);
            free(tmp2);
            tmp->prev = NULL;
            data = tmp;
        }
        else if (tmp->val[0] == '0' && tmp->prev->sign > 0 && tmp->prev->prev == NULL){
            struct values *tmp2 = tmp;
            tmp = tmp->next;
            if (tmp != NULL) tmp->prev = NULL;
            free(tmp2->prev->val);
            free(tmp2->prev);
            free(tmp2->val);
            free(tmp2);
            data = tmp;
        }
        else if (tmp->val[0] == '0' && tmp->prev->sign > 0){
            struct values *tmp2 = tmp;
            tmp = tmp->next;
            tmp2->prev->prev->next = tmp;
            if (tmp != NULL) tmp->prev = tmp2->prev->prev;
            free(tmp2->prev->val);
            free(tmp2->prev);
            free(tmp2->val);
            free(tmp2);
        }
        else if (tmp->val[0] == '0'){
            struct values *tmp2 = tmp;
            tmp = tmp->next;
            tmp2->prev->next = tmp;
            if (tmp != NULL) tmp->prev = tmp2->prev;
            free(tmp2->val);
            free(tmp2);
        }
        if (tmp!= NULL) tmp = tmp->next;
    }
    return data;
}

struct values * putDataOnLeftSide(struct values *data){
    struct values *tmp = data;
    struct values *equal = NULL;
    while (tmp != NULL){
        if (tmp->val[0] == '=') {
            equal = tmp;
        }
        if (tmp->val[0] >= '0' && tmp->val[0] <= '9' && tmp->side == 1 && tmp->prev->sign > 0){
            struct values *tmp2 = tmp->next;
            if (equal->prev == NULL){
                data = tmp->prev;
                data->prev = NULL;
                tmp->next = equal;
                equal->next = tmp2;
                if (tmp2 != NULL) tmp2->prev = equal;
                data->val[0] = (data->val[0] == '-') ? '+' : '-';
                data->side = 0;
                data->next->side = 0;
            }else{
                equal->prev->next = tmp->prev;
                tmp->prev->prev = equal->prev;
                tmp->next = equal;
                equal->prev = tmp;
                equal->next = tmp2;
                if (tmp2 != NULL) tmp2->prev = equal;
                tmp->prev->val[0] = (tmp->prev->val[0] == '-') ? '+' : '-';
                tmp->prev->side = 0;
                tmp->side = 0;
            }
        }
        else if (tmp->val[0] >= '0' && tmp->val[0] <= '9' && tmp->side == 1 && tmp->prev->val[0] == '='){
            struct values *tmp2 = tmp->next;
             struct values *new = malloc(sizeof(struct values));
                char *val = malloc(sizeof(char) * 2);
                val[0] = '-';
                val[1] = '\0';
                new->degree = -1;
                new->side = 0;
                new->sign = 2;
                new->val = val;
            if (equal->prev == NULL){
                data = new;
                new->prev = NULL;
                new->next = tmp;
                tmp->side = 0;
                tmp->prev = new;
                tmp->next = equal;
                equal->prev = tmp;
                equal->next = tmp2;
                if (tmp2 != NULL) tmp2->prev = equal;
            }else {
                new->prev = equal->prev;
                equal->prev->next = new;
                new->next = tmp;
                tmp->side = 0;
                tmp->prev = new;
                tmp->next = equal;
                equal->prev = tmp;
                equal->next = tmp2;
                if (tmp2 != NULL)tmp2->prev = equal;
            }
        }
        tmp = tmp->next;
    }
    return data;
}

void displayData(struct values *data){
    struct values *tmp = data;
    struct values *tmp2 = NULL;
    size_t i = 0;
    printf("Reduced form: ");
    while (tmp != NULL){
        tmp2 = tmp;
        if (i == 0 && tmp->val[0] == '='){
            printf("0 %s ", tmp->val);
        }
        else if(tmp->val[0] == '='){
            printf("%s ", tmp->val);
        }
        else if(tmp->val[0] >= '0' && tmp->val[0] <= '9'){
            printf ("%s * X^%d ", tmp->val, tmp->degree);
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

int degreeEquation(struct values *data){
    struct values *tmp = data;
    int degree = 0;
    while (tmp != NULL){
        if (tmp->val[0] >= '0' && tmp->val[0] <= '9'){
            if (tmp->degree > degree)
                degree = tmp->degree;
        }
        tmp = tmp->next;
    }
    return degree;
}

void solutionOneDegreeEquation(struct values *data){
    struct values *tmp = data;
    char *div = NULL;
    char *num = NULL;
    while (tmp != NULL){
        if (tmp->degree == 0){
            if (tmp->prev == NULL || tmp->prev->val[0] != '-'){
                num = join("-", tmp->val);
                free(tmp->val);
                tmp->val = num;
            }
            else if(tmp->prev->val[0] == '-'){
                num = tmp->val;
            }
        }
        else if (tmp->degree == 1){
            if (tmp->prev == NULL || tmp->prev->val[0] == '+'){
                div = tmp->val;
            }else if (tmp->prev->val[0] == '-'){
                div = join("-", tmp->val);
                free(tmp->val);
                tmp->val = div;
            }
        }
        tmp = tmp->next;
    }
    char *res = divi(num, div);
    printf("%s\n", res);
    free(res);
}

char *calculDelta(struct values *data){
    // ax^2 + bx + c = 0
    // delta = b^2 - 4ac
    char *delta = NULL;
    char *vala = NULL;
    char *valb = NULL;
    char *valc = NULL;
    struct values *tmp = data;
    while (tmp != NULL){
        if (tmp->degree == 2){
            if (tmp->prev == NULL || tmp->prev->val[0] == '+'){
                vala = strdup(tmp->val);
            }
            else{
                vala = join("-", tmp->val);
            }
        }
        if (tmp->degree == 1){
            if (tmp->prev == NULL || tmp->prev->val[0] == '+'){
                valb = strdup(tmp->val);
            }
            else{
                valb = join("-", tmp->val);
            }
        }
        if (tmp->degree == 0){
            if (tmp->prev == NULL || tmp->prev->val[0] == '+'){
                valc = strdup(tmp->val);
            }
            else{
                valc = join("-", tmp->val);
            }
        }
        tmp = tmp->next;
    }
    char  *bcaree = mul(valb, valb);
    
    char  *ac = mul(vala, valc);
  
    char  *quatreAC = mul("4", ac);
   
    delta = sub(bcaree, quatreAC);
    free(vala); free(valb); free(valc); free(bcaree); free(ac); free(quatreAC);
    return delta;
}

char *solutionPositifSecondDegree(struct values *data, char *delta, int l){
    char *soluce = NULL;
    char *vala = NULL;
    char *valb = NULL;
    struct values *tmp = data;
    while (tmp != NULL){
        if (tmp->degree == 2){
            if (tmp->prev == NULL || tmp->prev->val[0] == '+'){
                vala = strdup(tmp->val);
            }
            else{
                vala = join("-", tmp->val);
            }
        }
        if (tmp->degree == 1){
            if (tmp->prev == NULL || tmp->prev->val[0] == '+'){
                valb = join("-", tmp->val);
            }
            else{
                valb = strdup(tmp->val);
            }
        }
        tmp = tmp->next;
    }

    char *doublea = mul("2", vala);
    char *rdelta = squareRoot(delta);
    char *tmp2 = NULL;
    if (l == 1) tmp2 = sub(valb, rdelta);
    else tmp2 = add(valb, rdelta);
    soluce = divi(tmp2, doublea);
    free(doublea); free(rdelta); free(tmp2);free(vala); free(valb);
    return soluce;
}

char *solutionEqualZeroSecondDegree(struct values *data){
    char *soluce = NULL;
    char *vala = NULL;
    char *valb = NULL;
    struct values *tmp = data;
    while (tmp != NULL){
        if (tmp->degree == 2){
            if (tmp->prev == NULL || tmp->prev->val[0] == '+'){
                vala = strdup(tmp->val);
            }
            else{
                vala = join("-", tmp->val);
            }
        }
        if (tmp->degree == 1){
            if (tmp->prev == NULL || tmp->prev->val[0] == '+'){
                valb = join("-", tmp->val);
            }
            else{
                valb = strdup(tmp->val);
            }
        }
        tmp = tmp->next;
    }
    char *doublea = mul("2", vala);
    soluce = divi(valb, doublea);
    free(vala); free(valb); free(doublea);
    return soluce;
}

bool checkIfEquationPossible(struct values *data){
    struct values *tmp = data;
    size_t i = 0;
    while(tmp != NULL){
        tmp = tmp->next;
        i++;
    }
    if (i > 1) return false;
    return true; 
}

char *solutionNegatifSecondDegree(struct values *data, char *delta, int l){
    char *soluce = NULL;
    char *vala = NULL;
    char *valb = NULL;
    struct values *tmp = data;
    while (tmp != NULL){
        if (tmp->degree == 2){
            if (tmp->prev == NULL || tmp->prev->val[0] == '+'){
                vala = strdup(tmp->val);
            }
            else{
                vala = join("-", tmp->val);
            }
        }
        if (tmp->degree == 1){
            if (tmp->prev == NULL || tmp->prev->val[0] == '+'){
                valb = join("-", tmp->val);
            }
            else{
                valb = strdup(tmp->val);
            }
        }
        tmp = tmp->next;
    }
    char *doublea = mul("2", vala);
    char *rdelta = squareRoot(delta);
    char *div1 = divi(valb, doublea);
    char *div2 = divi(rdelta, doublea);
    if (l == 1){
        char *reu1 = join(div1, " - i * ");
        soluce = join(reu1, div2);
        free(reu1);

    } else if (l != 1){
        char *reu1 = join(div1, " + i * ");
        soluce = join(reu1, div2);
        free(reu1);
    }
    free(vala); free(valb); free(doublea); free(rdelta); free(div1); free(div2) ;
    return soluce;

}

void equation(char *s){
    if (isSyntaxError(s) == false){
        fprintf(stderr, "syntax error\n");
        return;
    }
    struct values *data = parseData(s);
    // creer une fonction qui fait les multiplications de chaque coter.
    data = multiplicationAndDivisionData(data);
    // creer une fonction qui fait les additions et soustraction de chaque coter.
    data = additionAndSubtractionData(data);
    // creer une fonction qui met tous les nombres du coter gauche.
    data = putDataOnLeftSide(data);
    // creer une fonction qui affiche la version reduite de l'equation
    displayData(data);
    data = supprimZeroOfData(data);
    // creer une fonction qui deduit le degrees de l'equation.
    int degree = degreeEquation(data);
    printf("Polynomial degree: %d\n", degree);
    if (degree > 2){
        printf("The polynomial degree is strictly greater than 2, I can't solve.\n");
    }
    else if (degree == 0){
        bool isPossible = checkIfEquationPossible(data);
        if (isPossible) printf("All number for X are possible.\n");
        else printf("There is no solution\n");
    }else if (degree == 1){
        printf("The solution is:\n");
        solutionOneDegreeEquation(data);
    }
    // si equation second degree.
     if (degree == 2){
        char *delta = calculDelta(data);
        printf("delta = %s\n", delta);
        int nbSolution = numberBigerLowerEqual(delta, "0");
        if (nbSolution == 1){
            printf("Discriminant is strictly positive, the two solutions are:\n");
            char *firstSolution = solutionPositifSecondDegree(data, delta, 1);
            printf("%s\n", firstSolution);
            char *secondSolution = solutionPositifSecondDegree(data, delta, 2);
            printf("%s\n", secondSolution);
            free(firstSolution);
            free(secondSolution);
        }
        else if (nbSolution == 0){
            printf("Discriminant is 0, the solution is:\n");
            char *solution = solutionEqualZeroSecondDegree(data);
            printf("%s\n", solution);
        }
        else if (nbSolution == -1){
            printf("The two complexes number are:\n");
            char *firstcomplexSolution = solutionNegatifSecondDegree(data, delta + 1, 1);
            printf("%s\n" ,firstcomplexSolution);
            char *secondcomplexSolution = solutionNegatifSecondDegree(data, delta + 1, 2);
            printf("%s\n" ,secondcomplexSolution);
            free(firstcomplexSolution);
            free(secondcomplexSolution);
        }
        free(delta);
     }
    struct values *tmp = data;
    tmp = data;
    while (tmp != NULL){
        struct values *tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2->val);
        free(tmp2);
    }
}

int main(int argc, char **av){
    if (argc != 2) return 0;
    equation(av[1]);
    return 0;
}