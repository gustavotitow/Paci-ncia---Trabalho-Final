#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include "carta.h"

#define NOME_NAIPE 10
#define TAMANHO_NOME_IMAGEM 30



typedef struct nodoFEnc
{
    Info info;
    struct nodoFEnc *prox;
    struct nodoFEnc *ant;
} NodoFEnc;

//typedef NodoLEnc NodoFEnc;

typedef struct filaEnc
{
    struct nodoFEnc *ini;
    struct nodoFEnc *fim;
} FilaEnc;


// Funcao que cria uma fila
FilaEnc* criaFilaEnc();

// Funcao que destroi uma fila
void destroiFilaEnc(FilaEnc *fila);

// Funcao que insere um elemento na fila
void enfileiraFilaEnc(FilaEnc *fila, Info info);

// Funcao que remove um elemento da fila
Info desenfileiraFilaEnc(FilaEnc *fila);

void inverte_fila(FilaEnc* fila);



#endif // FILA_H_INCLUDED
