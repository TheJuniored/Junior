#include <stdio.h>
#include <stdlib.h>
#include "already.h"

//function that checks if a column is resolved
int is_column_solved(int x, int tab[])
{
    int solved = 1;
    for (size_t i = 0; i < 9 && solved == 1; i++)
    {
        int val = tab[x + i * 9];
        for (size_t j = i + 1; j < 9 && solved == 1; j++)
        {
            if (tab[x + j * 9] == val || val == 0)//see if the value is in the column or if a cell is always at 0

            {
                solved = 0;
            }
        }
    }
    return solved; //return if the column is solved
}

int is_line_solved(int y, int tab[])
{
    int solved = 1;
    for (size_t i = 0; i < 9 && solved == 1; i++)
    {
        int val = tab[y * 9 + i];
        for (size_t j = i + 1; j < 9 && solved == 1; j++)
        {
            if (tab[y * 9 + j] == val || val == 0) //look if the value is in the line or if a cell is always at 0
            {
                solved = 0;
            }
        }
    }
    return solved; //return if the row is solved
}

//check if the square is solved
int is_square_solved(int i, int tab[])
{
    //create a tab with all the value around
    int t[] = {
        tab[i - 10],
        tab[i - 9],
        tab[i - 8],
        tab[i - 1],
        tab[i],
        tab[i + 1],
        tab[i + 8],
        tab[i + 9],
        tab[i + 10],
    };
    return is_line_solved(0, t);
}

//see if the sudoku is solved
int is_solved(int tab[])
{
    int solved = 1;
    int t[] = {10, 13, 16, 37, 40, 43, 64, 67, 70};

    for (size_t i = 0; i < 9 && solved == 1; i++)
    {
        if (is_column_solved(i, tab) == 0)//check if each column is solved
        {
            solved = 0;
        }
    }

    for (size_t i = 0; i < 9 && solved == 1; i++)//check if each row is solved
    {
        if (is_line_solved(i, tab) == 0)
        {
            solved = 0;
        }
    }

    for (size_t i = 0; i < 9 && solved == 1; i++)//check if each square is solved
    {
        if (is_square_solved(t[i], tab) == 0)
        {
            solved = 0;
        }
    }

    return solved;//return if the sudoku is solved or not
}
