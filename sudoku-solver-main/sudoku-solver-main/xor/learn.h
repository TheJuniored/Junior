#ifndef _LEARN_H_
#define _LEARN_H_

#include <stdlib.h>
#include "vector.h"
#include "xor.h"

void learn(struct neurone **list_neurone_couche_1, struct neurone **list_neurone_couche_2, 
            float *resulta_couche_1, float *resulta_couche_2, float answer, float *input);

#endif