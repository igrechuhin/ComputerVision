#ifndef SystemIncluded
#define SystemIncluded

#include <stdio.h>
#include <stdlib.h>

float ntohf(float);
float htonf(float);
double ntohd(double);
double htond(double);

long GetIdleTime();

long FileSize(char *fileName);

double RandomDouble();

void Sbrk(char *message);

#endif
