#ifndef COMPUTORV1
#define COMPUTORV1
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#define INT_MAX 2147483647
#define INT_MIN -2147483648

typedef struct s_data{
        double  power;
        double  mulFactor;
        bool    side;
        char    actNext;
        s_data  *next;
}       t_data;

#endif