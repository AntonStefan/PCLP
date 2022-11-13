#include <stdio.h>
#include <stdlib.h>

int contine_cifra(int nr, int c) {
    if (nr < 0)
        nr = -nr;
    while (nr != 0) {
        if (nr % 10 == c)
            return 1;
        nr /= 10;
    }
    return 0;
}

void extrage_nr(int **a, int n, int *v, int *nr, int c) {
    *nr = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (contine_cifra(a[i][j], c) == 1) {
                v[*nr] = a[i][j];
                *nr += 1;
            }
}

int main() {
    int **mat, n, *v, nr, c, i, j;
    scanf("%d", &n);
    mat = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        mat[i] = malloc(n * sizeof(int));
    v = malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
        for(j = 0; j< n; j++)
            scanf("%d", &mat[i][j]);
    scanf("%d", &c);
    extrage_nr(mat, n, v, &nr, c);
    for (i=0; i<nr; i++)
        printf("%d ", v[i]);
    printf("\n");
    free(v);
    for (i=0; i<n; i++)
        free(mat[i]);
    free(mat);
}