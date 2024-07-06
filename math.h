#ifndef MATH
#define MATH
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define LIMIT 20741430600ULL

struct lenPointNumber{
    long indexBPt;
    long indexAPt;
};


char*   supprimZeroAfterNumber(char *str);
char*   supprimZeroBeforeNumber(char *str);
bool    isOnlyNumber(char *s1);
struct  lenPointNumber strlenNumberPoint(char *str);
bool    isNumberFloat(char *str);
char *  join(char *s1, char *s2);
void    decalValueOne(char *s);
char    *decalValue(char *s, struct lenPointNumber lpns1, struct lenPointNumber lpns2);

// elle additionera deux numero tant que le systeme permet de la memoire continue avec malloc.  
// renvoie une nouvelle string avec s1 et s2 additionner. si s1 ou s2 a un char qui n'est pas un numero ou si s1 ou s2 est null renvoie null;
char*   add(char *s1, char *s2);
char*   sub(char *s1, char *s2);
char*   mul(char *s1, char *s2);
char*   divi(char *s1, char *s2);


#endif