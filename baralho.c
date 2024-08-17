
#include "baralho.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>


#define QUANTIDADE_DE_CARTAS 52
#define TAMANHO_DO_VETOR 51

// Função que cria uma lista
ListaCircEnc* criaListaCircEnc()
{
    ListaCircEnc *lista = (ListaCircEnc*)malloc(sizeof(ListaCircEnc));
    if (lista != NULL)
    {
        lista->prim = NULL;
        lista->fim = NULL;
        printf("criei a lista vazia");
    }
    return lista;
}

// Função que destrói uma lista
void destroiListaCircEnc(ListaCircEnc *lista)
{
    if (lista->prim != NULL)
    {
        NodoLEnc *atual = lista->prim;
        do
        {
            NodoLEnc *prox = atual->prox;
            free(atual);
            atual = prox;
        }
        while (atual != lista->prim);
    }
    free(lista);
}



// Função que insere um nó no início de uma lista
int insereInicioListaCircEnc(ListaCircEnc *lista, Info info)
{
    NodoLEnc *novo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
    if (novo == NULL) return 0;
    novo->info = info;

    if (lista->prim == NULL)
    {
        novo->prox = novo;
        novo->ant = novo;
        lista->prim = novo;
        lista->fim = novo;  // Atualiza o ponteiro fim
    }
    else
    {
        NodoLEnc *ultimo = lista->fim;
        novo->prox = lista->prim;
        novo->ant = ultimo;
        lista->prim->ant = novo;
        ultimo->prox = novo;
        lista->prim = novo;
    }
    return 1;
}

int insereFimListaCircEnc(ListaCircEnc *lista, Info info)
{
    NodoLEnc *novoNodo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
    if (!novoNodo)
    {
        return 0;
    }

    novoNodo->info = info;

    if (lista->prim == NULL)
    {
        lista->prim = novoNodo;
        lista->fim = novoNodo;
        novoNodo->prox = novoNodo;
        novoNodo->ant = novoNodo;
    }
    else
    {
        NodoLEnc *ultimo = lista->fim;
        novoNodo->prox = lista->prim;
        novoNodo->ant = ultimo;
        ultimo->prox = novoNodo;
        lista->prim->ant = novoNodo;
        lista->fim = novoNodo;  // Atualiza o ponteiro fim
    }
    return 1;
}

Info remove_carta_fim(ListaCircEnc *baralho){
    NodoLEnc *carta = baralho->fim;
    Info info = carta->info;

    if(baralho->prim == baralho->fim){ ///quando baralho so tem um nodo
        baralho->prim = NULL;
        baralho->fim = NULL;
    } else{ ///quando baralho tem mais de um nodo;
    baralho->fim->ant->prox = baralho->prim;
    baralho->fim->prox->ant = baralho->fim->ant;
    baralho->fim = baralho->fim->ant;
    }
    free(carta);
    return info;
}


ListaCircEnc* cria_baralho(){
    FILE *txtcartas;
    txtcartas = fopen("cartas.txt", "r");
    char nome_imagem [40];
    ListaCircEnc *baralho = criaListaCircEnc();



    for (int i=0; i< QUANTIDADE_DE_CARTAS; i++) {
        NodoLEnc *carta = (NodoLEnc*)malloc(sizeof(NodoLEnc));
        fscanf(txtcartas, " %d %s %d %s", &carta->info.valor, carta->info.naipe, &carta->info.chave, nome_imagem);
        carta->info.sentido = 0;
         carta->info.posicaoCarta = (Vector2){0, 0};

        Image imagem_carta = LoadImage(nome_imagem);
        ImageResize(&imagem_carta, (imagem_carta.width - imagem_carta.width * 0.85), (imagem_carta.height - imagem_carta.height * 0.85));
        carta->info.Imagem_carta = LoadTextureFromImage(imagem_carta);///algo faz o programa morrer aqui, mas eu não consegui encontrar
        printf("      passei     ");
        UnloadImage(imagem_carta);

        insereFimListaCircEnc(baralho, carta->info);
        free(carta);
        }

        //embaralha_baralho(baralho)
    return baralho;

}


ListaCircEnc* embaralha_baralho(ListaCircEnc* baralho)
{
    int cartas[QUANTIDADE_DE_CARTAS];
    int i, j, aux;
    ListaCircEnc *baralho_embaralhado = criaListaCircEnc();
    NodoLEnc *nodoAux;

    srand(time(NULL));

    // Preenchendo o vetor de 1 a 52
    for(i = 0; i < QUANTIDADE_DE_CARTAS; i++) {
        cartas[i] = i + 1;
    }

    // Algoritmo de Fisher-Yates para embaralhar os valores no vetor
    for(i = QUANTIDADE_DE_CARTAS - 1; i > 0; i--) {
        j = rand() % (i + 1);
        aux = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = aux;
    }

    // Passando os valores embaralhados para o novo baralho
    for (int k = 0; k < QUANTIDADE_DE_CARTAS; k++) {
        nodoAux = buscaInfoListaCircEnc(baralho, cartas[k]);
        insereInicioListaCircEnc(baralho_embaralhado, nodoAux->info);
    }

    return baralho_embaralhado;
}

NodoLEnc* buscaInfoListaCircEnc(ListaCircEnc* lista, int chave)
{
    if (lista->prim != NULL)
    {
        NodoLEnc *atual = lista->prim;
        do
        {
            if (atual->info.chave == chave) return atual;
            atual = atual->prox;
        }
        while (atual != lista->prim);
    }
    return NULL;
}


