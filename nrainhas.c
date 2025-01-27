#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int** Tab; // Ponteiro para ponteiro representando o tabuleiro dinamicamente
int N; // Número de rainhas/tamanho do tabuleiro

// Função para criar o tabuleiro dinamicamente
int** Cria_tabuleiro(int tamanho) {
    int** tab = (int**)malloc(tamanho * sizeof(int*)); // Aloca as linhas
    if (tab == NULL) {
        printf("Erro: falha na alocação de memória para o tabuleiro.\n");
        exit(1);
    }
    for (int i = 0; i < tamanho; i++) {
        tab[i] = (int*)malloc(tamanho * sizeof(int)); // Aloca as colunas
        if (tab[i] == NULL) {
            printf("Erro: falha na alocação de memória para as colunas.\n");
            exit(1);
        }
        // Inicializa o tabuleiro com zeros
        for (int j = 0; j < tamanho; j++) {
            tab[i][j] = 0;
        }
    }
    return tab;
}

// Função para liberar a memória do tabuleiro
void Libera_tabuleiro(int** tab, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        free(tab[i]); // Libera cada linha
    }
    free(tab); // Libera o array de ponteiros
}

// Função para imprimir o tabuleiro
void Imprime_tab() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (Tab[i][j]) 
                printf(" Q ");
            else 
                printf(" . ");
        }
        printf("\n");
    }
    printf("\n");
}

// Verifica se é seguro colocar uma rainha em uma posição
bool Valida_posicao(int linha, int col) {
    int i, j;
    // Verifica a coluna atual
    for (i = 0; i < linha; i++) {
        if (Tab[i][col]) return false;
    }
    // Verifica a diagonal superior esquerda
    for (i = linha, j = col; i >= 0 && j >= 0; i--, j--) {
        if (Tab[i][j]) return false;
    }
    // Verifica a diagonal superior direita
    for (i = linha, j = col; i >= 0 && j < N; i--, j++) {
        if (Tab[i][j]) return false;
    }
    return true;
}

// Função que resolve o problema com backtracking
bool Slc_bckt(int linha) {
    // Caso onde todas as rainhas foram colocadas
    if (linha == N) {
        Imprime_tab();
        return true;
    }
    for (int col = 0; col < N; col++) {
        if (Valida_posicao(linha, col)) {
            Tab[linha][col] = 1; // Coloca a rainha

            // Tenta resolver para a próxima linha
            if (Slc_bckt(linha + 1)) 
                return true;

            // Backtracking: Remove a rainha
            Tab[linha][col] = 0;
        }
    }
    return false;
}

int main() {
    printf("Digite o tamanho do tabuleiro: ");
    scanf("%d", &N);

    if (N <= 1) {
        printf("O tamanho deve ser maior que 0.\n");
        return 1;
    }

    // Cria o tabuleiro dinamicamente
    Tab = Cria_tabuleiro(N);

    // Resolve o problema
    if (!Slc_bckt(0)) {
        printf("Nenhuma solução foi encontrada para %d rainhas nesse tamanho de tabuleiro.\n", N);
    }

    // Libera o tabuleiro da memória
    Libera_tabuleiro(Tab, N);

    return 0;
}
