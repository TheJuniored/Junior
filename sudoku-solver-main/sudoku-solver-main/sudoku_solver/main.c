#include <stdio.h>

#include <stdlib.h>

#include "filetab.h"
#include "already.h"
#include "solve.h"

int main(int argc, char *argv[])
{
    if (argc==2)
    {
        char *s=argv[1];
        int tab[81];

        file_to_tab(tab, s);
    
        solve(tab);
        char *end=".result";
        
        
        int i, i1, i2;
        char *sf = NULL;
        for (i1 = 0; s[i1] != '\0'; i1++)
            ;
        for (i2 = 0; end[i2] != '\0'; i2++)
            ;
        sf = malloc(i1 + i2 + 1);       // on ajoute 1 car on ne compte pas '\0' dans les 2 chaines
        for (i = 0; i < i1; i++)
            sf[i] = s[i];
        for (; i < i1 + i2; i++)
            sf[i] = end[i - i1];
        sf[i1 + i2] = '\0';
        

        tab_to_file(tab, sf);
        
        free(sf);

        return 0;
    }
    
    return 1;
}