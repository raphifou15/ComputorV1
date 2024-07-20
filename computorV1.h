#ifndef COMPUTORV1
#define COMPUTORV1

#include "math/math.h"

struct values{
    int             side; //0 left, 1 right, 2 middle;
    int             sign; // 0: pas de sign, 1:+, 2:-, 3:*, 4:/     
    int             degree;
    char            *val;
    char            *display;
    struct values   *next;
    struct values   *prev;
};

#ifdef BONUS
void   bonusActivate(void);
bool   isSyntaxErrorBonus(char *s);
struct values * parseDataBonus(char *s);
#endif

#endif