#include <stdio.h>
#include "vector.h"

struct vector *vector_new()
{
    struct vector *new = malloc(sizeof(struct vector));
    
    if(new == NULL){
	printf("Not enough memory!");
    return NULL;
    }

    new->capacity = 1;
    new->size = 0;
    new->data = malloc(sizeof(int));

    if(new->data == NULL){
	printf("Not enough memory!");
    return NULL;
    }
    return new;
}

void vector_free(struct vector *v)
{
    free(v->data);
    free(v);
}

void double_capacity(struct vector *v)
{
    v->capacity *=2;
    v->data = realloc(v->data, sizeof(int)*v->capacity);
    if(v->data == NULL){
	    printf("Not enough memory!");
    }
}

void vector_push(struct vector *v, float x)
{
    if(v->capacity == v->size){
	double_capacity(v);
    }
    v->data[v->size] = x;
    v->size++;
}

float vector_pop(struct vector *v, float *x)
{
    if(v == NULL || v->size == 0){
	return 0;
    }

    *x = v->data[v->size-1];
    v->size--;
    return 1;
}

float vector_get(struct vector *v, size_t i, float *x)
{
    if(i >= v->size){
	return 0;
    }
    *x = v->data[i];
    return 1;
}

void vector_insert(struct vector *v, size_t i, float x)
{
    if(i > v->size){
	    return;
    }
    if(i == v->size && v->capacity == v->size){
	    double_capacity(v);
    }

    int tmp;
    for(;i <= v->size;i++){
        tmp = v->data[i];
        v->data[i] = x;
        x = tmp;
    }
    v->size++;
}

float vector_remove(struct vector *v, size_t i, float *x)
{
    if(i >= v->size){
	return 0;
    }

    *x = v->data[i];
    for(; i < v->size-1;i++){
	v->data[i] = v->data[i+1];
    }
    v->size--;
    return 1;
}
