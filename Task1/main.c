#include <stdio.h>

int main (int argc, const char* ardv[])
{
    int n, i , j;
    scanf ("%d", &n);
    int** a = (int**) malloc (n * sizeof(int*));
    for (i = 0; i < n; i++)
    {
        a[i] = (int*) malloc (n * sizeof(int));
    }
    for (i = 0; i < n; i ++)
    {
        for (j = 0; j < n; j++)
        {
            a[i][j] = (i + 1)*(j + 1);
        }
    }
    int x1, x2, y1, y2, max, maxsize = 0;
    scanf ("%d %d %d %d", &x1, &y1, &x2, &y2);
    max = a[i - 1][j - 1];
    while (max)
    {
        max /= 10;
        maxsize ++;
    }
    char length[4];
    sprintf (length, "%%%dd", maxsize + 1);

    for (i = x1 - 1; i <= x2 - 1; i++)
    {
        for (j = y1 - 1; j <= y2 - 1; j++)
        {
            printf (length, a[i][j]);
        }
        printf ("\n");
    }
    free (a);
}

