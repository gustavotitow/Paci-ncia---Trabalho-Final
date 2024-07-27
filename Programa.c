#include "baralho.h"
#include <raylib.h>



int main(void)
{
    ListaCircEnc *baralho;
    NodoLEnc *carta;
    const int screenWidth = 1000;
    const int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "Jogo Paciencia - trabalho final");

    baralho = cria_baralho();
    carta = baralho->prim;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);


        int posX = 50;
        int posY = 50;


        do
        {
            DrawTexture(carta->info.Imagem_carta, posX, posY, WHITE);
            carta = carta->prox;
            posX = posX+15;
            posY = posY+10;
        }
        while(carta != baralho->fim);


        EndDrawing();
    }

    CloseWindow();

    return 0;
}
