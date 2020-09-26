#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* Define o tipo de dado no */
typedef struct NoTag {
    int info;
    struct NoTag* link;
} no;

void inicializa_Pilha(no** L) {
    /* atribui NULL ao ponteiro L */
    *L = NULL;
}

void imprime_Pilha(no** L) {
    no* P;
    P = *L; // P recebe o endereco do primeiro no da lista
    printf("\n Itens da Pilha (lista LIFO):");
    while (P != NULL) {
        printf("\n %d", P->info);
        P = P->link;
    }
}

void PUSH(no** L, int x) {
    /* declara um ponteiro denominado N */
    no* N;
    /* aloca memória para armazenar o novo nó e atribui o endereço da área reservada para N */
    N = (no*)malloc(sizeof(no));
    /* armazena a informação no novo nó */
    N->info = x;
    /* o link do novo nó recebe o endereço do nó apontado por L */
    N->link = *L;
    /* L recebe o endereço de N */
    *L = N;
}

void POP(no** L, int* n) {
    no* AUX;
    if (*L != NULL) {
        *n = (*L)->info;
        AUX = *L;
        *L = (*L)->link;
        free(AUX);
    }
}