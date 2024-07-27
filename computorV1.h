#ifndef COMPUTORV1
#define COMPUTORV1

#include "math/math.h"
#include <signal.h>

struct values{
    int             side; //0 left, 1 right, 2 middle;
    int             sign; // 0: pas de sign, 1:+, 2:-, 3:*, 4:/     
    int             degree;
    char            *val;
    struct values   *next;
    struct values   *prev;
};

void freeData(struct values *data);

#ifdef BONUS
void   bonusActivate(void);
bool   isSyntaxErrorBonus(char *s);
struct values * parseDataBonus(char *s);
void  displayDataBonus(struct values *data, bool reduce);
void displayCalcul(char *val1, char *val2, int degree, char sign);
#endif

#endif