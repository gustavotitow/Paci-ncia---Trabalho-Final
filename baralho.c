
#include "baralho.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include "baralho.h"

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



void carrega_imagem_cartas(ListaCircEnc* baralho)
{
    NodoLEnc *carta;
    int i, quant_cartas_mesmo_valor = 1, valor_da_carta = 1;
    int primeiro_numero = 0, segundo_numero = 0;
    char nome[30];


    carta = baralho->prim;

    for(i=0; i < QUANTIDADE_DE_CARTAS; i++)
    {
        if(quant_cartas_mesmo_valor == 1)
        {
            if(valor_da_carta < 10)
            {
                strcpy(nome, "cartas/0_of_clubs.png");
                nome[7] = '0' + valor_da_carta; //convertendo inteiro para char
            }
            else
            {
                strcpy(nome, "cartas/00_of_clubs.png");
                primeiro_numero = valor_da_carta/10;
                nome[7] = '0' + primeiro_numero;
                segundo_numero = valor_da_carta%10;
                nome[8] = '0' + segundo_numero;
            }
            quant_cartas_mesmo_valor++;

        }
        else if(quant_cartas_mesmo_valor == 2)
        {
            if(valor_da_carta < 10)
            {
                strcpy(nome, "cartas/0_of_diamonds.png");
                nome[7] = '0' + valor_da_carta; //convertendo inteiro para char
            }
            else
            {
                strcpy(nome, "cartas/00_of_diamonds.png");
                primeiro_numero = valor_da_carta/10;
                nome[7] = '0' + primeiro_numero;
                segundo_numero = valor_da_carta%10;
                nome[8] = '0' + segundo_numero;
            }
            quant_cartas_mesmo_valor++;
        }
        else if(quant_cartas_mesmo_valor == 3)
        {
            if(valor_da_carta < 10)
            {
                strcpy(nome, "cartas/0_of_hearts.png");
                nome[7] = '0' + valor_da_carta; //convertendo inteiro para char
            }
            else
            {
                strcpy(nome, "cartas/00_of_hearts.png");
                primeiro_numero = valor_da_carta/10;
                nome[7] = '0' + primeiro_numero;
                segundo_numero = valor_da_carta%10;
                nome[8] = '0' + segundo_numero;
            }
            quant_cartas_mesmo_valor++;
        }
        else if(quant_cartas_mesmo_valor == 4)
        {
            if(valor_da_carta < 10)
            {
                strcpy(nome, "cartas/0_of_spades.png");
                nome[7] = '0' + valor_da_carta; //convertendo inteiro para char
            }
            else
            {
                strcpy(nome, "cartas/00_of_spades.png");
                primeiro_numero = valor_da_carta/10;
                nome[7] = '0' + primeiro_numero;
                segundo_numero = valor_da_carta%10;
                nome[8] = '0' + segundo_numero;
            }
            quant_cartas_mesmo_valor = 1;
            valor_da_carta++;
        }
        Image imagem_carta = LoadImage(nome);
        ImageResize(&imagem_carta, (imagem_carta.width - imagem_carta.width * 0.8), (imagem_carta.height - imagem_carta.height * 0.8));
        carta->info.Imagem_carta = LoadTextureFromImage(imagem_carta);
        UnloadImage(imagem_carta);
        carta = carta->prox;
    }

}


ListaCircEnc* cria_baralho()
{
    ListaCircEnc *baralho = criaListaCircEnc();
    NodoLEnc *carta = (NodoLEnc*)malloc(sizeof(NodoLEnc));
    int i, valor_da_carta = 1, quant_cartas_mesmo_valor = 1;


    for(i = 0; i < QUANTIDADE_DE_CARTAS; i++)  //preenchendo as infos das cartas
    {
        carta->info.chave = i+1;
        carta->info.valor = valor_da_carta;
        carta->info.sentido = 0;

        if(quant_cartas_mesmo_valor == 1)
        {
            strcpy(carta->info.naipe, "paus");
        }
        else if(quant_cartas_mesmo_valor == 2)
        {
            strcpy(carta->info.naipe, "ouros");
        }
        else if(quant_cartas_mesmo_valor == 3)
        {
            strcpy(carta->info.naipe, "copas");
        }
        else if(quant_cartas_mesmo_valor == 4)
        {
            strcpy(carta->info.naipe, "espadas");
            valor_da_carta++;
            quant_cartas_mesmo_valor = 1;  //reinicia a contagem apos 4 naipes;
        }
        quant_cartas_mesmo_valor++;
        insereFimListaCircEnc(baralho, carta->info);


    }
    carrega_imagem_cartas(baralho);

    ///AVISO: o que eu fiz asseguir foi para consertar o problema da inversao
    /// dos pnteiros de prim e fim do baralho, não encontrei onde o erro esta acontecendo
    /// mas o codiigo que segue conserta isso.
    carta = baralho->prim;
    baralho->prim = baralho->fim;
    baralho->fim = carta;

    return baralho;

}
