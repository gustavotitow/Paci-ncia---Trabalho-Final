#include "fila.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>




// Função que cria uma fila
FilaEnc* criaFilaEnc() {
    FilaEnc *fila = (FilaEnc*)malloc(sizeof(FilaEnc));
    if (fila != NULL) {
        fila->ini = NULL;
        fila->fim = NULL;
    }
    return fila;
}

// Função que destrói uma fila
void destroiFilaEnc(FilaEnc *fila) {
    NodoFEnc *aux = fila->ini;
    while (aux != NULL) {
        NodoFEnc *tmp = aux->prox;
        free(aux);
        aux = tmp;
    }
    free(fila);
}

// Função que insere um elemento na fila
void enfileiraFilaEnc(FilaEnc *fila, Info info) {
    NodoFEnc *novo = (NodoFEnc*)malloc(sizeof(NodoFEnc));
    if (novo != NULL) {
        novo->info = info;
        novo->prox = NULL;
        novo->ant = fila->fim;
        if (fila->fim != NULL)
            fila->fim->prox = novo;
        else
            fila->ini = novo;
        fila->fim = novo;
    }
}

// Função que remove um elemento da fila
Info desenfileiraFilaEnc(FilaEnc *fila) {
    if (fila->ini == NULL) {
        fprintf(stderr, "Erro: fila vazia.\n");
        exit(EXIT_FAILURE);
    }
    NodoFEnc *aux = fila->ini;
    Info info = aux->info;
    fila->ini = aux->prox;
    if (fila->ini != NULL)
        fila->ini->ant = NULL;
    else
        fila->fim = NULL;
    free(aux);
    return info;
}

// Função que determina se uma fila é vazia
int vaziaFilaEnc(FilaEnc *fila) {
    return (fila->ini == NULL);
}

void inverte_fila(FilaEnc* fila) {
    if (fila->ini == NULL || fila->ini == fila->fim) {
        // Fila vazia ou com apenas um elemento já está invertida
        return;
    }

    NodoFEnc *current = fila->ini;
    NodoFEnc *temp = NULL;

    // Trocar os ponteiros prox e ant para cada nodo
    while (current != NULL) {
        temp = current->prox;
        current->prox = current->ant;
        current->ant = temp;
        current = temp;
    }

    // Trocar o início e o fim da fila
    temp = fila->ini;
    fila->ini = fila->fim;
    fila->fim = temp;
}

