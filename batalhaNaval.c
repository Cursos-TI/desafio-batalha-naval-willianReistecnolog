#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define TAM_HAB 5
#define NAVIO 3
#define HABILIDADE 5

void inicializarMatriz(int matriz[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            matriz[i][j] = 0;
        }
    }
}

void exibirMatriz(int linhas, int colunas, int matriz[linhas][colunas]) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("   ");
    for (int j = 0; j < TAM; j++) printf("%d ", j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%c  ", 'A' + i);
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int offset = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = origemLinha - offset + i;
                int colTab = origemColuna - offset + j;
                if (linhaTab >= 0 && linhaTab < TAM && colTab >= 0 && colTab < TAM) {
                    if (tabuleiro[linhaTab][colTab] != NAVIO)
                        tabuleiro[linhaTab][colTab] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarMatriz(tabuleiro);

    int tamanhoNavio = 3;

    for (int i = 0; i < tamanhoNavio; i++) tabuleiro[1][2 + i] = NAVIO;
    for (int i = 0; i < tamanhoNavio; i++) tabuleiro[5 + i][6] = NAVIO;
    for (int i = 0; i < tamanhoNavio; i++) tabuleiro[2 + i][1 + i] = NAVIO;
    for (int i = 0; i < tamanhoNavio; i++) tabuleiro[4 + i][8 - i] = NAVIO;

    printf("=== TABULEIRO INICIAL ===\n\n");
    exibirTabuleiro(tabuleiro);

    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB / 2 - i) && j <= (TAM_HAB / 2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int distancia = abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2);
            if (distancia <= TAM_HAB / 2)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }

    printf("=== MATRIZ DE HABILIDADE: CONE ===\n");
    exibirMatriz(TAM_HAB, TAM_HAB, cone);

    printf("=== MATRIZ DE HABILIDADE: CRUZ ===\n");
    exibirMatriz(TAM_HAB, TAM_HAB, cruz);

    printf("=== MATRIZ DE HABILIDADE: OCTAEDRO ===\n");
    exibirMatriz(TAM_HAB, TAM_HAB, octaedro);

    aplicarHabilidade(tabuleiro, cone, 3, 3);
    aplicarHabilidade(tabuleiro, cruz, 7, 2);
    aplicarHabilidade(tabuleiro, octaedro, 6, 7);

    printf("=== TABULEIRO COM HABILIDADES ===\n\n");
    exibirTabuleiro(tabuleiro);
    
    printf("Legenda:\n");
    printf("0 = Água\n");
    printf("3 = Navio\n");
    printf("5 = Área afetada pela habilidade\n");


    return 0;
}
