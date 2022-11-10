#include "xor.h"

void error_externe(float *tab_res, float *tab_error, size_t len, float answer){
    for (size_t i = 0; i < len; i++){
        tab_error[i] = tab_res[i] * (1 - tab_res[i]) * (answer - tab_res[i]);
    }
}


void learn_externe(struct neurone **list_neurone, float *tab_error, float *resulta_couche, size_t len){
     for (size_t i = 0; i < 1; i++){
        list_neurone[i]->data += 0.1 * (-1) * tab_error[i];
    }

    for (size_t i = 0; i < 1; i++){ 
        for (size_t j = 0; j < len; j++){
            list_neurone[i]->liaison->data[j] += 0.1 * resulta_couche[j] * tab_error[i];
        }
    }
}


void error_iden(struct neurone **list_neurone, float *resulta_couche, float *tab_error, float *tab_error_res, size_t len){
    for (size_t i = 0; i < len; i++){
        float tmp = tab_error[0] * list_neurone[0]->liaison->data[i];
        tab_error_res[i] = resulta_couche[i] * (1 - resulta_couche[i]) * tmp;
    }
}


void learn_iden(struct neurone **list_neurone, float *tab_error, float *input, size_t len){
    for (size_t i = 0; i < len; i++){
        list_neurone[i]->data += 0.1 * (-1) * tab_error[i];
    }

    for (size_t i = 0; i < len; i++){
        for (size_t j = 0; j < len; j++){
            float tmp = 0.1 * input[j] * tab_error[i];
            list_neurone[i]->liaison->data[j] += tmp;
        }
    }
}


void learn(struct neurone **list_neurone_couche_1, struct neurone **list_neurone_couche_2, 
    float *resulta_couche_1, float *resulta_couche_2, float answer, float *input){
    float tab_error[1];
    error_externe(resulta_couche_2, tab_error, 1, answer);
    learn_externe(list_neurone_couche_2, tab_error, resulta_couche_1, 2);
    float tab_error_res[2];
    error_iden(list_neurone_couche_2, resulta_couche_1, tab_error, tab_error_res, 2);
    learn_iden(list_neurone_couche_1, tab_error_res, input, 2);

}