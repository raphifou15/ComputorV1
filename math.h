#ifndef MATH
#define MATH
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define LIMIT 20741430600ULL

// elle additionera deux numero tant que le systeme permet de la memoire continue avec malloc.  
// renvoie une nouvelle string avec s1 et s2 additionner. si s1 ou s2 a un char qui n'est pas un numero ou si s1 ou s2 est null renvoie null;
char *   add(char *s1, char *s2); 

#endif