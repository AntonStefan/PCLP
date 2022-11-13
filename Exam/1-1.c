#include <stdio.h>
#include <stdlib.h>

int e_prim(int x) {
    if (x <= 1)
        return 0;
    for (int i = 2; i <= x / 2; i++)
        if (x % i == 0)
            return 0;
    return 1;
}

void extrage_prime_diag(int **mat, int n, int *v, int *nr, int a, int b) {
    *nr = 0;
    for (int i = 0; i < n; i++)
        if (e_prim(mat[i][i]) == 1 && mat[i][i] >= a && mat[i][i] <= b) {
            v[*nr] = mat[i][i];
            *nr += 1;
        }
}

int main() {
    int **mat, n, *v, nr, a, b, i, j;
    scanf("%d", &n);
    mat = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        mat[i] = malloc(n * sizeof(int));
    v = malloc (n * sizeof(int));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);
    scanf("%d%d", &a, &b);
    extrage_prime_diag(mat, n, v, &nr, a, b);
    for (i = 0; i < nr; i++)
        printf("%d ", v[i]);
    printf("\n");
    for (i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
    free(v);
}