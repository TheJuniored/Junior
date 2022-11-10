#include <stdio.h>
#include <stdlib.h>

//check if the value we are trying to insert is already in the column
int already_in_column(int x, int val, int tab[])
{
    int already = 0;
    for (size_t i = 0; i < 9 && already == 0; i++)
    {
        if (tab[x + i * 9] == val)
        {
            already = 1; //the value is in the column
        }
    }
    return already;
}

//check if the value we are trying to insert is already in the row
int already_in_line(int y, int val, int tab[])
{
    int already = 0;
    for (size_t i = 0; i < 9; i++)
    {
        if (tab[y * 9 + i] == val)
        {
            already = 1; //the value is in the line
        }
    }

    return already;
}

//check if the value we are trying to insert is already in the square
int already_in_square(int i, int val, int tab[])
{
    //we take all the values around our cell in an array
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

    return already_in_line(0, val, t);
}
