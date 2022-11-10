#ifndef _XOR_H_
#define _XOR_H_

#include <stdlib.h>
#include "vector.h"

struct neurone
{
    float data;
    struct vector *liaison;
};

float xor(float *input);
void xor_learn(int iteration);


#endif