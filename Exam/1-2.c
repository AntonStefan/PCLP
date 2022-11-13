#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nume[20];
    float pret, cantitate;
} Produs;

typedef struct {
    char *id;
    int nr;
    Produs *prod;
} Magazin;

int cmpProduse(const void *p1, const void *p2) {
    Produs *x = (Produs *)p1, *y = (Produs *)p2;
    if (strcmp(x->nume, y->nume) != 0)
        return strcmp(x->nume, y->nume);
    else if (-(x->pret - y->pret) < 0.000001)
        return 0;
    else
        return -(x->pret - y->pret);
}

void scrie(Magazin lidl, char *fisier, int (*cmp)(const void *, const void *)) {
    FILE *f = fopen(fisier, "w");
    qsort(lidl.prod, lidl.nr, sizeof(Produs), cmp);
    fprintf(f, "Numele magazinului: ");
    fputs(lidl.id, f);
    fprintf(f, "\nNumarul de produse: %d\n", lidl.nr);
    for (int i = 0; i < lidl.nr; i++) {
        fputs(lidl.prod[i].nume, f);
        fprintf(f, "%f %f\n", lidl.prod[i].pret, lidl.prod[i].cantitate);
    }
    fclose(f);
}

void modificaFisier(char *fisier, char *nume, float pret, float cantitate) {
    FILE *f = fopen(fisier, "rb+");
    Produs p, aux;
    int n, poz;
    strcpy(aux.nume, nume);
    aux.pret = pret;
    aux.cantitate = cantitate;
    fread(&n, sizeof(int), 1, f);
    poz = sizeof(int) + n* sizeof(char);
    fseek(f, poz, SEEK_SET);
    fread(&n, sizeof(int), 1, f);
    poz += sizeof(int);
    for (int i = 0; i < n; i++) {
        fread(&p, sizeof(Produs), 1, f);
        if (cmpProduse(&p, &aux) == 0) {
            fseek(f, poz + i*sizeof(Produs), SEEK_SET);
            fwrite(&aux, sizeof(Produs), 1, f);
        }
    }
}