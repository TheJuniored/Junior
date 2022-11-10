#include <stdio.h>
#include <stdlib.h>
#include "is_solved.h"
#include "already.h"

int centerpos(int i) //find the center of the square for eache position
{
    if (i % 3 == 2)
    {
        i -= 1;
    }
    else if (i % 3 == 0)
    {
        i += 1;
    }
    if ((i / 9) % 3 == 0)
    {
        i += 9;
    }

    else if ((i / 9) % 3 == 2)
    {
        i -= 9;
    }

    return i;
}

void listposs(int x, int tab[], int poss[])
{
    int xm = centerpos(x); //find the center of the square
    int j = 0;

    for (size_t i = 1; i < 10; i++)
    {
        if (already_in_line(x / 9, i, tab) == 0 && already_in_column(x % 9, i, tab) == 0 && already_in_square(xm, i, tab)==0)//check if the value respect the rules
        {
            poss[j] = i;
            j++;
        }
    }
}

int solve_rec(int i, int tab[])
{
    if (i == 81)//if we have finished checking each box
    {
        return 1;
    }

    if (tab[i] != 0) //makes a backwards call on each cell containing a number different from 0
    {
        return solve_rec(i + 1, tab);
    }


    int poss[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    listposs(i, tab, poss);
    int j = 0;

    while (j < 9 && poss[j] != 0)
    {
        tab[i] = poss[j];
        if (solve_rec(i + 1, tab) == 1)
        {
            return 1; //return true
        }
        j++;
    }

    tab[i] = 0;

    return 0; //return false
}

//solve the sudoku
void solve(int tab[])
{
    solve_rec(0, tab);
    while (is_solved(tab)==0)
    {
        solve_rec(0, tab);
    }
}
