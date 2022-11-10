#ifndef IS_SOLVED_H
#define IS_SOLVED_H

//we define all our functions which are in .c in the .h

int is_line_solved(int y, int tab[]);
int is_column_solved(int x, int tab[]);
int is_square_solved(int x, int y, int tab[]);
int is_solved(int tab[]);

#endif
