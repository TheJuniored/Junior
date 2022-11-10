#ifndef _SAVE_H_
#define _SAVE_H_

#include <stdlib.h>
#include "vector.h"
#include "xor.h"

void initNeurone(struct neurone *ln[], size_t s,int couche);
void saveNeurone(struct neurone *ln[], size_t s,int couche);


#endif