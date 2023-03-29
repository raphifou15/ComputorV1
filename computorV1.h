#ifndef COMPUTORV1
#define COMPUTORV1
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define INT_MAX 2147483647
#define INT_MIN -2147483648

#define POWER 1
#define FACTOR 2
#define ADD 3
#define SOUS 4
#define MULT 5
#define DIV 6
#define EQ 7

#define WRONG -1

#define LEFT 0
#define RIGHT 1

typedef struct s_data{
        char *val;
        double value;
        int type;
        int side;
        struct s_data *next;
}       t_data;


// typedef struct s_data{
//         double  power;
//         double  mulFactor;
//         bool    side;
//         char    actNext;
//         s_data  *next;
// }       t_data;

// typedef struct s_data{
//         double  value;
//         int     type;
//         int     side;
// }       t_data;

// typedef struct s_data{
//         double  factor;
//         double  power;
// }       t_data;

#endif