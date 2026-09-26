// ============================================================
// JOGO DO LABIRINTO
// Trabalho N1 - Algoritmos II
//
// Aluna: Gabrielly de Oliveira
// Aluna: Rayssa Carasilo
// Professor: Alessandro João Brassanini
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

#define N 10

void mudarCor(int cor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

int pontos = 0;

// ============================================================
// FUNÇÃO PARA MOSTRAR O LABIRINTO
// ============================================================

void mostrarLabirinto(int labirinto[N][N], int x, int y, int bateuNaParede)
{
    int i, j;

    printf("=====================================\n");
    printf("          JOGO DO LABIRINTO\n");
    printf("=====================================\n\n");

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            // Jogador (Rato)
            if (i == x && j == y)
            {
                if (bateuNaParede)
                {
                    mudarCor(12); // Vermelho Claro
                    printf("💥"); 
                }
                else
                {
                    mudarCor(10); // Verde Claro
                    printf("🐭");
                }
            }
            // Parede
            else if (labirinto[i][j] == 1)
            {
                mudarCor(8);
                printf("X "); 
            }
            // NOVO: Armadilha / Buraco (Representado por 'O')
            else if (labirinto[i][j] == 2)
            {
                mudarCor(7); // Vermelho
                printf(". "); 
            }
            // Saida (Queijo)
            else if (labirinto[i][j] == -1)
            {
                mudarCor(14);
                printf("🧀");
            }
            // Caminho
            else
            {
                mudarCor(7);
                printf(". "); 
            }
        }
        printf("\n");
    }

    mudarCor(7);
    printf("\nLinha: %d | Coluna: %d\n", x + 1, y + 1);
    printf("\nW = Cima | S = Baixo | A = Esquerda | D = Direita\n");
    
    if (pontos > 0) mudarCor(10);
    else mudarCor(12);
    
    printf("Pontuacao: %d\n", pontos);
    mudarCor(7);
}

void tocarSom(int duracao, int tipoSom)
{
    if (tipoSom == 1)      Beep(750, duracao); // Parede
    else if (tipoSom == 2) Beep(300, duracao); // NOVO: Som grave de Armadilha
    else                   Beep(500, duracao); // Movimento normal
}

// Alterado para permitir que o jogador ande sobre o número 2 (armadilha)
int validarMovimento(int labirinto[N][N], int x, int y)
{
    if (x < 0 || x >= N || y < 0 || y >= N || labirinto[x][y] == 1)
    {
        return 0; 
    }
    return 1; 
}

// ============================================================
// PROGRAMA PRINCIPAL
// ============================================================

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    // Adicionado o número '2' em posições estratégicas do caminho
    int labirinto[N][N] =
        {
            {0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 1, 2, 1, 0, 1, 1, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 2, 0}, // Adicionado uma armadilha aqui (linha 3, coluna 5)
            {1, 1, 0, 1, 1, 1, 1, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // Adicionado uma armadilha aqui (linha 5, coluna 7)
            {0, 1, 1, 1, 1, 1, 1, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 1, 0}, // Adicionado uma armadilha aqui (linha 7, coluna 2)
            {2, 1, 1, 1, 1, 0, 1, 0, 1, 0},
            {0, 0, 0, 0, 1, 0, 2, 0, 1, 0},
            {1, 1, 1, 0, 0, 0, 2, 0, 0, -1}};

    int x = 0, y = 0;
    char comando;
    int jogando = 1;
    int bateuNaParede = 0;
    int contadorMovimentos = 0;

    while (jogando)
    {
        system("cls");
        mostrarLabirinto(labirinto, x, y, bateuNaParede);
        bateuNaParede = 0;

        // ----------------------------------------------------
        // NOVO: VERIFICA SE CAIU NA ARMADILHA
        // ----------------------------------------------------
        if (labirinto[x][y] == 2)
        {
            mudarCor(12);
            printf("\n💥 TRAP! Voce caiu em um buraco e perdeu 5 pontos!\n");
            tocarSom(600, 2);
            
            pontos -= 5;
            if (pontos < 0) pontos = 0; // Impede pontuação negativa se preferirem

            // Opcional: Faz o jogador voltar para o início do jogo
            x = 0;
            y = 0;

            mudarCor(7);
            Sleep(1500); // Pausa maior para ler o aviso
            continue;    // Reinicia o loop na posição inicial
        }

        if (labirinto[x][y] == -1)
        {
            tocarSom(800, 0);
            mudarCor(10);
            printf("\n🎉 🎉 🎉 PARABENS! 🎉 🎉 🎉\n");
            printf("🥳 O ratinho encontrou o queijo com sucesso! 🧀✨\n\n");
            mudarCor(11);
            printf("=====================================\n");
            printf("📊 ESTATISTICAS DA PARTIDA:\n");
            printf("=====================================\n");
            printf("🐾 Total de movimentos: %d\n", contadorMovimentos);
            printf("🏆 Total de pontos:     %d\n", pontos);
            printf("=====================================\n");
            mudarCor(7);
            break;
        }

        printf("\nDigite seu movimento: ");
        scanf(" %c", &comando);
        comando = toupper(comando);

        int novoX = x;
        int novoY = y;

        if (comando == 'W')      novoX--;
        else if (comando == 'S') novoX++;
        else if (comando == 'A') novoY--;
        else if (comando == 'D') novoY++;
        else
        {
            printf("\nComando invalido!\n");
            Sleep(600);
            continue;
        }

        if (validarMovimento(labirinto, novoX, novoY))
        {
            x = novoX;
            y = novoY;
            tocarSom(200, 0);
            contadorMovimentos++;
            pontos++;
        }
        else
        {
            bateuNaParede = 1;
            mudarCor(4);
            tocarSom(800, 1);
            printf("\nMovimento invalido! Parede ou fora do labirinto!\n");
            mudarCor(7);
            if (pontos > 0) pontos--;
            Sleep(900);
        }
    }

    return 0;
}
