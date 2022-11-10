#include <stdio.h>
#include <stdlib.h>
#include "xor.h"


//lecture d'un fichier contenant un neurone
struct neurone *read_floats(const char* file_name)
{
    FILE* file = fopen (file_name, "r");

    if (file == NULL) {
        printf("Erreur fopen\n");
    }

    float i = 0;
    size_t j = 0;


    fscanf (file, "%f", &i);

    struct neurone *n = malloc(sizeof(struct neurone));
    n->data = i;
    n->liaison = vector_new();
    fscanf (file, "%f", &i);
    while (!feof (file))
    {
        vector_insert(n->liaison, j, i);
        fscanf (file, "%f", &i);
        j++;
    }
    fclose (file);
    return n;
}


//sauvegarde un neurone dans un fichier
void Wfile(struct neurone *n, char *file_name){
    FILE *fp;

    fp = fopen(file_name, "w");

    if (fp == NULL) {
        printf("Erreur fopen\n");
    }

    fprintf(fp, "%f\n", n->data);
    for (size_t i = 0; i < n->liaison->size; i++)
    {
        fprintf(fp, "%f\n", n->liaison->data[i]);
    }

    fclose(fp);
}


//lit tout les fichiers et initialises tout les neurones
void initNeurone(struct neurone *ln[], size_t s,int couche){
    char name[16] = "Value/n____.txt\0";
    name[7] = couche + 48;
    for(size_t i = 0; i < s; i++){
        if (i%26 == 0)
            name[9] = 65 + (i/26)%26;
        if (i%676 == 0)
            name[8] = 65 + i/676;
        name[10] = i%26 + 65;
        ln[i] = read_floats(name);
    }
}


//sauvegarde tout les neurones dans des fichiers
void saveNeurone(struct neurone *ln[], size_t s,int couche){
    char name[16] = "Value/n____.txt\0";
    name[7] = couche + 48;
    for(size_t i = 0; i < s; i++){
        if (i%26 == 0)
            name[9] = 65 + (i/26)%26;
        if (i%676 == 0)
            name[8] = 65 + i/676;
        name[10] = i%26 + 65;
        Wfile(ln[i], name);
    }
}
