#ifndef SOLVE_H
#define SOLVE_H

//we define all our functions which are in .c in the .h

int centerpos(int i);
void listposs(int x, int tab[], int poss[]);
int solve_rec(int i, int tab[]);
void solve(int tab[]);

#endif
