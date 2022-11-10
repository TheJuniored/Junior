#include <stdio.h>
#include "xor.h"


int main(){
    float input[2] = {0, 0};
    printf("0 xor 0 = %f\n", xor(input));

    float input2[2] = {0, 1};
    printf("0 xor 1 = %f\n", xor(input2));

    float input3[2] = {1, 0};
    printf("1 xor 0 = %f\n", xor(input3));

    float input4[2] = {1, 1};
    printf("1 xor 1 = %f\n", xor(input4));

    printf("learn\n");
    xor_learn(10000);

    printf("0 xor 0 = %f\n", xor(input));

    printf("0 xor 1 = %f\n", xor(input2));

    printf("1 xor 0 = %f\n", xor(input3));

    printf("1 xor 1 = %f\n", xor(input4));

    return 0;
}
