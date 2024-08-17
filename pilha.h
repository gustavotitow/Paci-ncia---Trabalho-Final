#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include "carta.h"

#define NOME_NAIPE 10
#define TAMANHO_NOME_IMAGEM 30



typedef struct nodoPEnc
{
    Info info;
    struct nodoPEnc *prox;
    //struct nodoLEnc *ant;
} NodoPEnc;

//typedef NodoLEnc NodoPEnc;

typedef struct pilhaEnc{
   NodoPEnc *topo;
} PilhaEnc;

// Funcao que cria uma pilha
PilhaEnc* criaPilhaEnc();

// Funcao que destroi uma pilha
void destroiPilhaEnc(PilhaEnc *pilha);

// Funcao que insere um elemento na pilha
void empilhaPilhaEnc(PilhaEnc *pilha, Info info);

// Funcao que remove um elemento da pilha
Info desempilhaPilhaEnc(PilhaEnc *pilha);


void inverte_pilha(PilhaEnc* pilha);


#endif // PILHA_H_INCLUDED
