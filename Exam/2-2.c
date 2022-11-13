#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titlu[30], autor[30];
    int nr_pagini;
} Carte;

typedef struct {
    char *nume;
    Carte *carti;
    int n;
} Biblioteca;

void scrie(Biblioteca b, char *fisier) {
    FILE *f = fopen(fisier, "w");
    fprintf(f, "Numele bibliotecii: ");
    fputs(b.nume, f);
    fprintf(f, "\nNumarul de carti: %d\n", b.n);
    for (int i = 0; i < b.n; i++) {
        fputs(b.carti[i].titlu, f);
        fprintf(f, " ");
        fputs(b.carti[i].autor, f);
        fprintf(f, " %d\n", b.carti[i].nr_pagini);
    }
    fclose(f);
}

void citire(Biblioteca *b, char *fisier) {
    FILE *f = fopen(fisier, "rb");
    int nr;
    fread(&nr, sizeof(int), 1, f);
    b->nume = malloc(nr * sizeof(char));
    fread(b->nume, sizeof(b->nume), 1, f);
    fread(&nr, sizeof(int), 1, f);
    b->carti = malloc(nr * sizeof(Carte));
    fread(b->carti, sizeof(Carte), nr, f);
    fclose(f);
}

int cmpCarti(const void *c1, const void *c2) {
    Carte *x = (Carte *)c1, *y = (Carte *)c2;
    return strcmp(x->titlu, y->titlu);
}

char *cautaAutor(char *titlu, Biblioteca b, int (*cmp)(const void *, const void *)) {
    Biblioteca aux = b;
    Carte *aux2, cautat;
    char mesaj[30] = "crapa";
    strcpy(cautat.titlu, titlu);
    qsort(aux.carti, aux.n, sizeof(Carte), cmp);
    aux2 = bsearch(&cautat, aux.carti, aux.n, sizeof(Carte), cmp);
    if (aux2 == NULL)
        return mesaj;
    return aux2->autor;
}