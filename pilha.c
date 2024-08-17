#include "pilha.h"
//#include "carta.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>


// Funcao que cria uma pilha
PilhaEnc* criaPilhaEnc(){
   PilhaEnc *pilha = (PilhaEnc*)malloc(sizeof(PilhaEnc));
   if (pilha != NULL) // Idealmente, sempre checar!
      pilha->topo = NULL;
   return pilha;
}

// Funcao que destroi uma pilha
void destroiPilhaEnc(PilhaEnc *pilha){
   NodoPEnc *aux = pilha->topo;
   while(aux != NULL){
       NodoPEnc *tmp = aux->prox;
       free(aux); // Cuidar ordem do free
       aux = tmp;
   }
   free(pilha);
}

// Funcao que insere um elemento na pilha
void empilhaPilhaEnc(PilhaEnc *pilha, Info info){
   NodoPEnc *novo = (NodoPEnc*)malloc(sizeof(NodoPEnc));
   if (novo != NULL){ // Idealmente, sempre checar!
      novo->info = info;
      novo->prox = pilha->topo;
      pilha->topo = novo;
   }
}



// Funcao que remove um elemento da pilha
Info desempilhaPilhaEnc(PilhaEnc* pilha){
   NodoPEnc *aux = pilha->topo;
   /// Aqui assumimos que desempilha eh
   ///chamada apenas se a pilha nao eh vazia
   Info info = aux->info;
   pilha->topo = aux->prox;
   free(aux);
   return info;
}



void inverte_pilha(PilhaEnc* pilha) {
    NodoPEnc *prev = NULL;
    NodoPEnc *current = pilha->topo;
    NodoPEnc *next = NULL;

    while (current != NULL) {
        // Armazena o próximo nó
        next = current->prox;
        // Inverte o ponteiro
        current->prox = prev;
        // Avança os ponteiros
        prev = current;
        current = next;
    }

    // Atualiza o topo da pilha para ser o antigo último nó
    pilha->topo = prev;
}


