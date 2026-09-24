// Desenvolvido por Alessandro Jo�o Brassanini
// Data: 19 de Abril de 2022

/*
Uso de matriz bidimensional (5x5) para armazenar o cen�rio.
La�os de repeti��o para imprimir o labirinto a cada rodada.
Condicionais para validar os movimentos e impedir atravessar paredes.
Leitura de teclado com scanf para capturar as dire��es.
Verifica��o de vit�ria quando o jogador chega na sa�da.

Regras:
P - posi��o atual do jogador.
0 - caminho livre.
1 - parede (n�o pode atravessar).
S - sa�da (objetivo do jogo).

*/


#include <stdio.h>   // Necess�rio para printf e scanf
#include <stdlib.h>  // Necess�rio para system (limpar tela em alguns sistemas)
#include <ctype.h>   // Necess�rio para toupper (converter tecla para mai�scula)

#define N 5 // Tamanho da matriz do labirinto

int main()
{
    // Matriz que representa o labirinto
    // 0 = caminho, 1 = parede, S = sa�da (marcada por -1 aqui)
    int labirinto[N][N] =
    {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, -1} // -1 indica sa�da (ser� exibida como 'S')
    };

    int x = 0, y = 0; // Posi��o inicial do jogador (linha, coluna)
    char comando;     // Vari�vel para armazenar o comando do jogador
    int jogando = 1;  // Controle do loop principal do jogo

    // Loop principal do jogo
    while (jogando)
    {
        // Limpa a tela (funciona no Windows com "cls", em Linux/Mac com "clear")
        // Se estiver testando no Code::Blocks ou terminal, pode comentar a linha abaixo
        system("clear || cls");

        // Exibe o labirinto
        printf("Jogo do Labirinto 5x5\n");
        printf("Use W (cima), S (baixo), A (esquerda), D (direita)\n");
        printf("Objetivo: chegar na saida (S)\n\n");

        int i, j;
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (i == x && j == y)
                {
                    printf("P "); // Mostra jogador
                }
                else if (labirinto[i][j] == 1)
                {
                    printf("# "); // Mostra parede
                }
                else if (labirinto[i][j] == -1)
                {
                    printf("S "); // Mostra sa�da
                }
                else
                {
                    printf(". "); // Mostra caminho livre
                }
            }
            printf("\n");
        }

        // Verifica se chegou � sa�da
        if (labirinto[x][y] == -1)
        {
            printf("\nParabens! Voce encontrou a saida!\n");
            break; // Sai do jogo
        }

        // Solicita movimento do jogador
        printf("\nDigite seu movimento (W/A/S/D): ");
        scanf(" %c", &comando);
        comando = toupper(comando); // Converte para mai�scula para facilitar

        // Calcula nova posi��o do jogador
        int novoX = x;
        int novoY = y;

        if (comando == 'W')
        {
            novoX--; // Move para cima
        }
        else if (comando == 'S')
        {
            novoX++; // Move para baixo
        }
        else if (comando == 'A')
        {
            novoY--; // Move para esquerda
        }
        else if (comando == 'D')
        {
            novoY++; // Move para direita
        }
        else
        {
            printf("Comando invalido!\n");
        }

        // Verifica se nova posi��o � v�lida (dentro da matriz e n�o � parede)
        if (novoX >= 0 && novoX < N && novoY >= 0 && novoY < N && labirinto[novoX][novoY] != 1)
        {
            x = novoX;
            y = novoY; // Atualiza posi��o do jogador
        }
        else
        {
            printf("Movimento invalido! Parede ou fora dos limites!\n");
        }
    }

    return 0; // Fim do jogo
}
