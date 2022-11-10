#include <stdio.h>
#include <stdlib.h>

//function that writes in an array the numbers of a file
void file_to_tab(int tab[], char *filename)
{

    FILE *f;
    int i = 0;
    char c;

    f = fopen(filename, "r");//we open the file on read only

    while ((c = fgetc(f)) != EOF)
    {

        if (c == '.') //we replace the '.' by 0
        {
            tab[i] = 0;
            i++;
        }

        else if (c >= '0' && c <= '9')//we insert in the table the value found in the text file
        {
            tab[i] = c - '0'; //convert char in int
            i++;
        }
    }

    fclose(f);//we close the file
}

//function that writes the sudoku answer number to a file
void tab_to_file(int tab[], char *filename)
{

    FILE *f;
    int i = 0;
    int j;
    int r = 0;

    f = fopen(filename, "w");//we open a file on write

    while (i < 9)//row
    {
        j = 0;

        while (j < 9)//column
        {
            int n = tab[r];

            if (n == 0)
            {
                fputc('.', f); //put '.' if the character is a 0
            }

            else
            {
                char c1 = n + '0'; //we transform the number in char
                fputc(c1, f); //we put the value in the file
            }

            if (j == 2 || j == 5) //if we are on the end of a small square in a line
            {
                fputc(' ', f); //put a space to seperate
            }

            if (j == 8 && i != 8)//if you are at the end of a line but not of the grid
            {
                fputc('\n', f); //we return to the line
            }

            r++;
            j++;
        }

        if (i == 2 || i == 5) //if we just finished the edges
        {
            fputs("\n", f);//skip a line
        }

        i++;
    }
}
