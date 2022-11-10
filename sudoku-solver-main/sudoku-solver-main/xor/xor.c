#include <math.h>
#include <stdlib.h>
#include "save.h"
#include "vector.h"
#include "xor.h"
#include "learn.h"


//passage de li'information d'une couche a l'autre
float passage(float *x, float *w, size_t s){
    float res = 0;
    for(size_t i = 0;i < s; i++){
        res += (x[i] * w[i]);
    }
    return res;
}


//traitement de l'information par le neurone qui la resoi
float sigmoid(float x1, float b){
    return 1 / ( 1 + exp(-( x1 - b)));
}


//passage et traitement de l'information
void transmition(float *v, struct neurone **list_neurone, size_t len, float *tab){
    for (size_t i = 0; i < len; i++)
    {
        float res = passage(v, list_neurone[i]->liaison->data, 2);
        tab[i] = sigmoid(res, list_neurone[i]->data);
    }
}


float xor(float *input){

    //init la première couche
    struct neurone *list_neurone_couche_1[2];
    initNeurone(list_neurone_couche_1, 2, 1);
    //init la deuxième couche
    struct neurone *list_neurone_couche_2[1];
    initNeurone(list_neurone_couche_2,1,2);


    //transmition de l'information des entrer vers la premiere couche
    float *resulta_couche_1 = malloc(sizeof(float) * 2);
    transmition(input, list_neurone_couche_1, 2, resulta_couche_1);
    //transmition de l'information de la premiere couche vers la couche de sorti
    float *resulta_couche_2 = malloc(sizeof(float) * 1);
    transmition(resulta_couche_1, list_neurone_couche_2, 1, resulta_couche_2);


    //resulta
    float res = resulta_couche_2[0];


    //free
    free(resulta_couche_1);
    free(resulta_couche_2);
    for (size_t i = 0; i < 2; i++){
        vector_free(list_neurone_couche_1[i]->liaison);
    }
    for (size_t i = 0; i < 1; i++){
        vector_free(list_neurone_couche_2[i]->liaison);
    }

    return res;

}

void xor_learn(int iteration){

    //init la première couche
    struct neurone *list_neurone_couche_1[2];
    initNeurone(list_neurone_couche_1, 2, 1);
    //init la deuxième couche
    struct neurone *list_neurone_couche_2[1];
    initNeurone(list_neurone_couche_2,1,2);

    float *resulta_couche_1 = malloc(sizeof(float) * 2);
    float *resulta_couche_2 = malloc(sizeof(float) * 1);


    //fake input
    int input_1 = 0;
    int input_2 = 0;

    while (iteration > 0)
    {
        if(input_1 == input_2)
            input_1 = (input_1+1)%2;
        else
            input_2 = (input_2+1)%2;

        
        float input[2] = {(float) input_1, (float) input_2};
        //transmition de l'information des entrer vers la premiere couche
        transmition(input, list_neurone_couche_1, 2, resulta_couche_1);
        //transmition de l'information de la premiere couche vers la couche de sorti
        transmition(resulta_couche_1, list_neurone_couche_2, 1, resulta_couche_2);

        //resulta
        float res = (input_1 == input_2) ? 0 : 1;
        learn(list_neurone_couche_1, list_neurone_couche_2, resulta_couche_1,
         resulta_couche_2, res, input);

        if(input_1 == input_2)
            iteration--;
    }
    saveNeurone(list_neurone_couche_1, 2, 1);
    saveNeurone(list_neurone_couche_2, 1, 2);

    //free
    free(resulta_couche_1);
    free(resulta_couche_2);
    for (size_t i = 0; i < 2; i++){
        vector_free(list_neurone_couche_1[i]->liaison);
    }
    for (size_t i = 0; i < 1; i++){
        vector_free(list_neurone_couche_2[i]->liaison);
    }

}