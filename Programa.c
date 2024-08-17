
#include "baralho.h"
#include "pilha.h"
#include "fila.h"
#include <raylib.h>

int main(void)
{
    // O trecho que estava aqui, tem que estar depois de InitWindow();
    /* Isso porque existe todo um contexto de biblioteca gráfica e enquanto não existir
        a instância da tela ele não consegue carregar as imagens.
    */
    const int screenWidth = 1200; //largura da tela
    const int screenHeight = 650;  //altura da tela

    InitWindow(screenWidth, screenHeight, "Jogo Paciencia - trabalho final");
    SetTargetFPS(60);

    ///criacao do baralho, pilhas e filas
    ListaCircEnc *baralho = cria_baralho();
    PilhaEnc *pilha[12];
    FilaEnc *fila[7];


    ///Criando as estruturas pilha e fila
    for(int i = 0; i < 7; i++)
    {

        fila[i] =criaFilaEnc();
    }

    for(int i = 0; i < 12; i++)
    {

        pilha[i] = criaPilhaEnc();
    }


    Texture2D imagem_carta = baralho->prim->info.Imagem_carta; // estou pegando a imagem da primeira carta para saber largura e altura (todas as cartas tem o mesmo tamanho);
    float largura_carta = imagem_carta.width; //pegando a largura da carta
    float altura_carta = imagem_carta.height; // pegando a altura da carta
    int posX = 150;
    int posY = 20;


    if(baralho != NULL)
    {
        Info aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX, posY};
        enfileiraFilaEnc(fila[0], aux_carta);

        ///pilha 0, fila 1
        for(int i = 0; i < 1; i++)
        {
            aux_carta = remove_carta_fim(baralho);
            aux_carta.posicaoCarta = (Vector2){posX + largura_carta + 20, posY};
            empilhaPilhaEnc(pilha[0],aux_carta);
            posY += 30; ///atualizando aposicao das cartas uma embaixo da outra
        }
        aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX + largura_carta + 20, posY};
        enfileiraFilaEnc(fila[1], aux_carta);

        ///pilha 1, fila 2
        posY = 20;
        for(int i = 0; i < 2; i++)
        {
            aux_carta = remove_carta_fim(baralho);
            aux_carta.posicaoCarta = (Vector2){posX + 2*(largura_carta + 20), posY};
            empilhaPilhaEnc(pilha[1],aux_carta);
            posY += 30; ///atualizando aposicao das cartas uma embaixo da outra
        }
        aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX + 2*(largura_carta + 20), posY};
        enfileiraFilaEnc(fila[2], aux_carta);

        ///pilha 2, fila 3
        posY = 20;
        for(int i = 0; i < 3; i++)
        {
            aux_carta = remove_carta_fim(baralho);
            aux_carta.posicaoCarta = (Vector2){posX + 3*(largura_carta + 20), posY};
            empilhaPilhaEnc(pilha[2],aux_carta);
            posY += 30; ///atualizando aposicao das cartas uma embaixo da outra
        }
        aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX + 3*(largura_carta + 20), posY};
        enfileiraFilaEnc(fila[3], aux_carta);

        ///pilha 3, fila 4
        posY = 20;
        for(int i = 0; i < 4; i++)
        {
            aux_carta = remove_carta_fim(baralho);
            aux_carta.posicaoCarta = (Vector2){posX + 4*(largura_carta + 20), posY};
            empilhaPilhaEnc(pilha[3],aux_carta);
            posY += 30; ///atualizando aposicao das cartas uma embaixo da outra
        }
        aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX + 4*(largura_carta + 20), posY};
        enfileiraFilaEnc(fila[4], aux_carta);

        ///pilha 4, fila 5
        posY = 20;
        for(int i = 0; i < 5; i++)
        {
            aux_carta = remove_carta_fim(baralho);
            aux_carta.posicaoCarta = (Vector2){posX + 5*(largura_carta + 20), posY};
            empilhaPilhaEnc(pilha[4],aux_carta);
            posY += 30; ///atualizando aposicao das cartas uma embaixo da outra
        }
        aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX + 5*(largura_carta + 20), posY};
        enfileiraFilaEnc(fila[5], aux_carta);

        ///pilha 5, fila 6
        posY = 20;
        for(int i = 0; i < 6; i++)
        {
            aux_carta = remove_carta_fim(baralho);
            aux_carta.posicaoCarta = (Vector2){posX + 6*(largura_carta + 20), posY};
            empilhaPilhaEnc(pilha[5],aux_carta);
            posY += 30; ///atualizando aposicao das cartas uma embaixo da outra
        }
        aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX + 6*(largura_carta + 20), posY};
        enfileiraFilaEnc(fila[6], aux_carta);
    }

    ///Dando a posição inicial para as cartas do baralho
    NodoLEnc *cartas = baralho->prim;
    posX = 20;
    posY = 20;
    do{

            cartas->info.posicaoCarta =  (Vector2){posX , posY};
            posY += 20;
            cartas = cartas->prox;

    }while(cartas != baralho->prim);


    int arraste = 0;
    Info aux_carta;
    PilhaEnc *pilha_com_cartas_a_movimentar = criaPilhaEnc();
    int posicaoInicial_x; ////armazena a posicao inicial da aux_carta, usado quando a carta vai ser colocada de volta no seu lugar original
    int posicaoInicial_y;
    int pos_ini_cartas_pilha_x[50];
    int pos_ini_cartas_pilha_y[50];
    int quantidade_cartas_pegas = 0;
    Vector2 atualiza_posicao = { 0.0f, 0.0f };
    Vector2 atual_pos_cartas[50];


//////    O JOGO COMECA AQUI ///////////
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        ///desenha as cartas do baralho
        cartas = baralho->prim;
        do{

            DrawTexture(cartas->info.Imagem_carta, cartas->info.posicaoCarta.x, cartas->info.posicaoCarta.y, WHITE);
            cartas = cartas->prox;

        }while(cartas != baralho->prim);

        ///desenha as cartas das pilhas
        int quantidade_de_pilha = 0;
        while(quantidade_de_pilha != 6)
        {
            inverte_pilha(pilha[quantidade_de_pilha]); ///preciso inverter se não a carta do topo sera desenhado embaixo das outras cartas
            NodoPEnc *aux_pilha = pilha[quantidade_de_pilha]->topo;
                while(aux_pilha != NULL)  ///Desenhando as cartas das pilhas
                {
                    DrawTexture(aux_pilha->info.Imagem_carta, aux_pilha->info.posicaoCarta.x, aux_pilha->info.posicaoCarta.y, WHITE);
                    aux_pilha = aux_pilha->prox;

                }
            inverte_pilha(pilha[quantidade_de_pilha]); ///voltando ao formato inicial, ou seja de cabeça pra baixo
            quantidade_de_pilha ++;

        }

        ///desenha as cartas da fila
        int quantidade_de_filas = 0;
        while(quantidade_de_filas != 7){
            NodoFEnc *aux_fila = fila[quantidade_de_filas]->ini;
        do{
            DrawTexture(aux_fila->info.Imagem_carta, aux_fila->info.posicaoCarta.x, aux_fila->info.posicaoCarta.y, WHITE);
            aux_fila = aux_fila->prox;
        }while(aux_fila != NULL);

        quantidade_de_filas ++;

        }

        /// Pega a posição atual do mouse
        Vector2 posicaoMouse = GetMousePosition();


        /// Verifica se o botão esquerdo do mouse foi pressionado
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            /// Verifica se o mouse está sobre a pilha 0 e se a fila 1 que esta em cima esta vazia
            if(pilha[0] != NULL && fila[1]->ini == NULL){
            if (CheckCollisionPointRec(posicaoMouse, (Rectangle){  pilha[0]->topo->info.posicaoCarta.x,  pilha[0]->topo->info.posicaoCarta.y, largura_carta, altura_carta }) && (fila[1]->ini == NULL))
            {
                arraste = 1;
                aux_carta = desempilhaPilhaEnc(pilha[0]);
                posicaoInicial_x = aux_carta.posicaoCarta.x;
                posicaoInicial_y = aux_carta.posicaoCarta.y;
                atualiza_posicao = (Vector2){ posicaoMouse.x - aux_carta.posicaoCarta.x, posicaoMouse.y - aux_carta.posicaoCarta.y };
            }
            }

            ///Verifica se o mouse esta em cima da fila 1
            inverte_fila(fila[1]); ///agora fila esta de cabeça pra baixo
            if (CheckCollisionPointRec(posicaoMouse, (Rectangle){  fila[1]->ini->info.posicaoCarta.x,  fila[1]->fim->info.posicaoCarta.y, largura_carta, altura_carta }))
            {
                if(fila[1]->ini->prox == NULL){ ///fila com uma carta
                    aux_carta = desenfileiraFilaEnc(fila[1]);
                    pos_ini_cartas_pilha_x[0] = aux_carta.posicaoCarta.x;
                    pos_ini_cartas_pilha_y[0] = aux_carta.posicaoCarta.y;
                    empilhaPilhaEnc(pilha_com_cartas_a_movimentar, aux_carta); //coloque a carta a ser movimentada na pilha aux
                    enfileiraFilaEnc(fila[1] ,desempilhaPilhaEnc(pilha[0])); //tirando a carta do topo da pilha e colocando na fila
                    quantidade_cartas_pegas ++; //importante na hora que o mouse eh solto, para o for
                }

                ///para descobrir quais quartas eu estou pegando da fila 1
       /*         else{
                NodoFEnc *aux_fila = fila[1]->ini;
                bool esta_sobre_carta;
                int encontrei_carta = 0;
                while(encontrei_carta != 1){
                    ///estou verificando uma a uma, em qual carta o mouse esta em cima
                    esta_sobre_carta = CheckCollisionPointRec(posicaoMouse, (Rectangle){  aux_fila->info.posicaoCarta.x,  aux_fila->info.posicaoCarta.y, largura_carta, altura_carta });
                    ///se eu encontrei eu vou tirar todas as cartas até onde o mouse esta e vou empilhar na pilha aux de movimento
                    if (esta_sobre_carta == true){
                        NodoFEnc *aux_fila_2 = fila[1]->ini;
                        while(aux_fila_2 != NULL && aux_fila_2 != aux_fila){

                            aux_carta = desenfileiraFilaEnc(fila[1]);
                            pos_ini_cartas_pilha_x[quantidade_cartas_pegas] = aux_carta.posicaoCarta.x;
                            pos_ini_cartas_pilha_y[quantidade_cartas_pegas] = aux_carta.posicaoCarta.y;
                            quantidade_cartas_pegas++;
                            empilhaPilhaEnc(pilha_com_cartas_a_movimentar,aux_carta);
                            aux_fila_2 = aux_fila_2->prox;
                        }
                       encontrei_carta = 1;
                    }
                    ///caso o mouse nao esteja sobre o retangulo desenhado, eu ando com aux_fila para desenhar o retangulo na proxima carta
                    else{

                        if (aux_fila->prox == NULL) {
                            break;
                        }
                        aux_fila = aux_fila->prox;
                    }
                }
                }  */
                arraste = 1;
                NodoPEnc *aux_pilha = pilha_com_cartas_a_movimentar->topo;
                int i = 0;
                while(aux_pilha != NULL){
                    atual_pos_cartas[i] = (Vector2){ posicaoMouse.x - aux_pilha->info.posicaoCarta.x, posicaoMouse.y - aux_pilha->info.posicaoCarta.y };
                    aux_pilha = aux_pilha->prox;
                    i++;
                }

          }
        inverte_fila(fila[1]); ///para voltar para o estado original

        }

        /// Verifica se o botão esquerdo do mouse foi liberado
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {


             ///verifica se o mouse esta sobre a fila
             if (CheckCollisionPointRec(posicaoMouse, (Rectangle){  fila[0]->fim->info.posicaoCarta.x,  fila[0]->fim->info.posicaoCarta.y, largura_carta, altura_carta }) && arraste == 1){
                aux_carta.posicaoCarta.x = fila[0]->fim->info.posicaoCarta.x;
                aux_carta.posicaoCarta.y = fila[0]->fim->info.posicaoCarta.y + 30;
                enfileiraFilaEnc(fila[0],aux_carta);
                arraste = 0;
             }
             else{
                    if(arraste == 1){
                        for(int i = 0; i < quantidade_cartas_pegas; i++){
                        aux_carta = desempilhaPilhaEnc(pilha_com_cartas_a_movimentar);
                        aux_carta.posicaoCarta.x = pos_ini_cartas_pilha_x[i];
                        aux_carta.posicaoCarta.y = pos_ini_cartas_pilha_y[i];
                        enfileiraFilaEnc(fila[1], aux_carta); //colocando de volta na fila

                        }
                    }
                    arraste = 0;
            }

        }



        /// Atualiza a posição da carta se estiver arrastando
        if (arraste == 1)
        {
            NodoPEnc *aux_pilha = pilha_com_cartas_a_movimentar->topo;
            int i = 0;
            while(aux_pilha != NULL){
                aux_pilha->info.posicaoCarta.x = posicaoMouse.x - atual_pos_cartas[i].x;
                aux_pilha->info.posicaoCarta.y = posicaoMouse.y - atual_pos_cartas[i].y;
                aux_pilha = aux_pilha->prox;
                i++;
            }
        }

        /// Desenha a carta sendo arrastada (se houver)
        if (arraste == 1 || IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            NodoPEnc *aux_pilha = pilha_com_cartas_a_movimentar->topo;
            while(aux_pilha != NULL){
                DrawTexture(aux_pilha->info.Imagem_carta, aux_pilha->info.posicaoCarta.x, aux_pilha->info.posicaoCarta.y, WHITE);
                aux_pilha = aux_pilha->prox;
            }
        }

        EndDrawing();
    }

    CloseWindow();

}





/*


#include "baralho.h"
#include "pilha.h"
#include "fila.h"
#include <raylib.h>

int main(void)
{
    // O trecho que estava aqui, tem que estar depois de InitWindow();
    /* Isso porque existe todo um contexto de biblioteca gráfica e enquanto não existir
        a instância da tela ele não consegue carregar as imagens.

    const int screenWidth = 1200; //largura da tela
    const int screenHeight = 650;  //altura da tela

    InitWindow(screenWidth, screenHeight, "Jogo Paciencia - trabalho final");
    SetTargetFPS(60);

    ///criacao do baralho, pilhas e filas
    ListaCircEnc *baralho = cria_baralho();
    PilhaEnc *pilha[12];
    FilaEnc *fila[7];


    ///Criando as estruturas pilha e fila
    for(int i = 0; i < 7; i++)
    {

        fila[i] =criaFilaEnc();
    }

    for(int i = 0; i < 12; i++)
    {

        pilha[i] = criaPilhaEnc();
    }


    Texture2D imagem_carta = baralho->prim->info.Imagem_carta; // estou pegando a imagem da primeira carta para saber largura e altura (todas as cartas tem o mesmo tamanho);
    float largura_carta = imagem_carta.width; //pegando a largura da carta
    float altura_carta = imagem_carta.height; // pegando a altura da carta
    int posX = 150;
    int posY = 20;


    if(baralho != NULL)
    {
        Info aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX, posY};
        enfileiraFilaEnc(fila[0], aux_carta);

        ///pilha 0, fila 1
        for(int i = 0; i < 1; i++)
        {
            aux_carta = remove_carta_fim(baralho);
            aux_carta.posicaoCarta = (Vector2){posX + largura_carta + 20, posY};
            empilhaPilhaEnc(pilha[0],aux_carta);
            posY += 30; ///atualizando aposicao das cartas uma embaixo da outra
        }
        aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX + largura_carta + 20, posY};
        enfileiraFilaEnc(fila[1], aux_carta);

        ///pilha 1, fila 2
        posY = 20;
        for(int i = 0; i < 2; i++)
        {
            aux_carta = remove_carta_fim(baralho);
            aux_carta.posicaoCarta = (Vector2){posX + 2*(largura_carta + 20), posY};
            empilhaPilhaEnc(pilha[1],aux_carta);
            posY += 30; ///atualizando aposicao das cartas uma embaixo da outra
        }
        aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX + 2*(largura_carta + 20), posY};
        enfileiraFilaEnc(fila[2], aux_carta);

        ///pilha 2, fila 3
        posY = 20;
        for(int i = 0; i < 3; i++)
        {
            aux_carta = remove_carta_fim(baralho);
            aux_carta.posicaoCarta = (Vector2){posX + 3*(largura_carta + 20), posY};
            empilhaPilhaEnc(pilha[2],aux_carta);
            posY += 30; ///atualizando aposicao das cartas uma embaixo da outra
        }
        aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX + 3*(largura_carta + 20), posY};
        enfileiraFilaEnc(fila[3], aux_carta);

        ///pilha 3, fila 4
        posY = 20;
        for(int i = 0; i < 4; i++)
        {
            aux_carta = remove_carta_fim(baralho);
            aux_carta.posicaoCarta = (Vector2){posX + 4*(largura_carta + 20), posY};
            empilhaPilhaEnc(pilha[3],aux_carta);
            posY += 30; ///atualizando aposicao das cartas uma embaixo da outra
        }
        aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX + 4*(largura_carta + 20), posY};
        enfileiraFilaEnc(fila[4], aux_carta);

        ///pilha 4, fila 5
        posY = 20;
        for(int i = 0; i < 5; i++)
        {
            aux_carta = remove_carta_fim(baralho);
            aux_carta.posicaoCarta = (Vector2){posX + 5*(largura_carta + 20), posY};
            empilhaPilhaEnc(pilha[4],aux_carta);
            posY += 30; ///atualizando aposicao das cartas uma embaixo da outra
        }
        aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX + 5*(largura_carta + 20), posY};
        enfileiraFilaEnc(fila[5], aux_carta);

        ///pilha 5, fila 6
        posY = 20;
        for(int i = 0; i < 6; i++)
        {
            aux_carta = remove_carta_fim(baralho);
            aux_carta.posicaoCarta = (Vector2){posX + 6*(largura_carta + 20), posY};
            empilhaPilhaEnc(pilha[5],aux_carta);
            posY += 30; ///atualizando aposicao das cartas uma embaixo da outra
        }
        aux_carta = remove_carta_fim(baralho);
        aux_carta.posicaoCarta = (Vector2){posX + 6*(largura_carta + 20), posY};
        enfileiraFilaEnc(fila[6], aux_carta);
    }

    ///Dando a posição inicial para as cartas do baralho
    NodoLEnc *cartas = baralho->prim;
    posX = 20;
    posY = 20;
    do{

            cartas->info.posicaoCarta =  (Vector2){posX , posY};
            posY += 20;
            cartas = cartas->prox;

    }while(cartas != baralho->prim);


    int arraste = 0;
    Info aux_carta;
    PilhaEnc *pilha_com_cartas_a_movimentar = criaPilhaEnc();
    int posicaoInicial_x; ////armazena a posicao inicial da aux_carta, usado quando a carta vai ser colocada de volta no seu lugar original
    int posicaoInicial_y;
    int pos_ini_cartas_pilha_x[50];
    int pos_ini_cartas_pilha_y[50];
    int quantidade_cartas_pegas = 0;
    Vector2 atualiza_posicao = { 0.0f, 0.0f };
    Vector2 atual_pos_cartas[50];


//////    O JOGO COMECA AQUI ///////////
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        ///desenha as cartas do baralho
        cartas = baralho->prim;
        do{

            DrawTexture(cartas->info.Imagem_carta, cartas->info.posicaoCarta.x, cartas->info.posicaoCarta.y, WHITE);
            cartas = cartas->prox;

        }while(cartas != baralho->prim);

        ///desenha as cartas das pilhas
        int quantidade_de_pilha = 0;
        while(quantidade_de_pilha != 6)
        {
            inverte_pilha(pilha[quantidade_de_pilha]); ///preciso inverter se não a carta do topo sera desenhado embaixo das outras cartas
            NodoPEnc *aux_pilha = pilha[quantidade_de_pilha]->topo;
                while(aux_pilha != NULL)  ///Desenhando as cartas das pilhas
                {
                    DrawTexture(aux_pilha->info.Imagem_carta, aux_pilha->info.posicaoCarta.x, aux_pilha->info.posicaoCarta.y, WHITE);
                    aux_pilha = aux_pilha->prox;

                }
            inverte_pilha(pilha[quantidade_de_pilha]); ///voltando ao formato inicial
            quantidade_de_pilha ++;

        }

        ///desenha as cartas da fila
        int quantidade_de_filas = 0;
        while(quantidade_de_filas != 7){
            NodoFEnc *aux_fila = fila[quantidade_de_filas]->ini;
        do{
            DrawTexture(aux_fila->info.Imagem_carta, aux_fila->info.posicaoCarta.x, aux_fila->info.posicaoCarta.y, WHITE);
            aux_fila = aux_fila->prox;
        }while(aux_fila != NULL);

        quantidade_de_filas ++;

        }

        /// Pega a posição atual do mouse
        Vector2 posicaoMouse = GetMousePosition();


        /// Verifica se o botão esquerdo do mouse foi pressionado
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            /// Verifica se o mouse está sobre a pilha 0 e se a fila 1 que esta em cima esta vazia
            if (CheckCollisionPointRec(posicaoMouse, (Rectangle){  pilha[0]->topo->info.posicaoCarta.x,  pilha[0]->topo->info.posicaoCarta.y, largura_carta, altura_carta }) && (fila[1]->ini == NULL))
            {
                arraste = 1;
                aux_carta = desempilhaPilhaEnc(pilha[0]);
                posicaoInicial_x = aux_carta.posicaoCarta.x;
                posicaoInicial_y = aux_carta.posicaoCarta.y;
                atualiza_posicao = (Vector2){ posicaoMouse.x - aux_carta.posicaoCarta.x, posicaoMouse.y - aux_carta.posicaoCarta.y };
            }

            ///Verifica se o mouse esta em cima da fila 1
            inverte_fila(fila[1]);
            if (CheckCollisionPointRec(posicaoMouse, (Rectangle){  fila[1]->ini->info.posicaoCarta.x,  fila[1]->fim->info.posicaoCarta.y, largura_carta, altura_carta }))
            {
                ///para descobrir quais quartas eu estou pegando da fila 1
                NodoFEnc *aux_fila = fila[1]->ini;
                bool esta_sobre_carta;
                int encontrei_carta = 0;
                while(encontrei_carta != 1){
                    ///estou verificando uma a uma, em qual carta o mouse esta em cima
                    esta_sobre_carta = CheckCollisionPointRec(posicaoMouse, (Rectangle){  aux_fila->info.posicaoCarta.x,  aux_fila->info.posicaoCarta.y, largura_carta, altura_carta });
                    ///se eu encontrei eu vou tirar todas as cartas até onde o mouse esta e vou empilhar na pilha aux de movimento
                    if (esta_sobre_carta == true){
                        NodoFEnc *aux_fila_2 = fila[1]->ini;
                        while(aux_fila_2 != NULL && aux_fila_2 != aux_fila){

                            aux_carta = desenfileiraFilaEnc(fila[1]);
                            pos_ini_cartas_pilha_x[quantidade_cartas_pegas] = aux_carta.posicaoCarta.x;
                            pos_ini_cartas_pilha_y[quantidade_cartas_pegas] = aux_carta.posicaoCarta.y;
                            quantidade_cartas_pegas++;
                            empilhaPilhaEnc(pilha_com_cartas_a_movimentar,aux_carta);
                            aux_fila_2 = aux_fila_2->prox;
                        }
                       encontrei_carta = 1;
                    }
                    ///caso o mouse nao esteja sobre o retangulo desenhado, eu ando com aux_fila para desenhar o retangulo na proxima carta
                    else{

                        if (aux_fila->prox == NULL) {
                            break;
                        }
                        aux_fila = aux_fila->prox;
                    }
                }
                arraste = 1;
                NodoPEnc *aux_pilha = pilha_com_cartas_a_movimentar->topo;
                int i = 0;
                while(aux_pilha != NULL){
                    atual_pos_cartas[i] = (Vector2){ posicaoMouse.x - aux_pilha->info.posicaoCarta.x, posicaoMouse.y - aux_pilha->info.posicaoCarta.y };
                    aux_pilha = aux_pilha->prox;
                    i++;
                }

            }
            inverte_fila(fila[1]); ///para voltar para o estado original

        }

        /// Verifica se o botão esquerdo do mouse foi liberado
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {


             ///verifica se o mouse esta sobre a fila
             if (CheckCollisionPointRec(posicaoMouse, (Rectangle){  fila[0]->fim->info.posicaoCarta.x,  fila[0]->fim->info.posicaoCarta.y, largura_carta, altura_carta }) && arraste == 1){
                aux_carta.posicaoCarta.x = fila[0]->fim->info.posicaoCarta.x;
                aux_carta.posicaoCarta.y = fila[0]->fim->info.posicaoCarta.y + 30;
                enfileiraFilaEnc(fila[0],aux_carta);
                arraste = 0;
             }
             else{
                    int i = 0;
                    while(pilha_com_cartas_a_movimentar != NULL){
                        aux_carta = desempilhaPilhaEnc(pilha_com_cartas_a_movimentar);
                        aux_carta.posicaoCarta.x = pos_ini_cartas_pilha_x[i];
                        aux_carta.posicaoCarta.y = pos_ini_cartas_pilha_y[i];
                        enfileiraFilaEnc(fila[1], aux_carta);
                        i++;


                    }
                    arraste = 0;
             }

        }

        /// Atualiza a posição da carta se estiver arrastando
        if (arraste)
        {
            NodoPEnc *aux_pilha = pilha_com_cartas_a_movimentar->topo;
            int i = 0;
            while(aux_pilha != NULL){
                aux_pilha->info.posicaoCarta.x = posicaoMouse.x - atual_pos_cartas[i].x;
                aux_pilha->info.posicaoCarta.y = posicaoMouse.y - atual_pos_cartas[i].y;
                aux_pilha = aux_pilha->prox;
                i++;
            }
        }

        /// Desenha a carta sendo arrastada (se houver)
        if (arraste || IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            NodoPEnc *aux_pilha = pilha_com_cartas_a_movimentar->topo;
            while(aux_pilha != NULL){
                DrawTexture(aux_pilha->info.Imagem_carta, aux_pilha->info.posicaoCarta.x, aux_pilha->info.posicaoCarta.y, WHITE);
                aux_pilha = aux_pilha->prox;
            }
        }

        EndDrawing();
    }

    CloseWindow();

}

*/
