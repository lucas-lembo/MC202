#include "esteira.h"
#include <stdlib.h>

p_est monta_esteira(int tamanho) {
    p_est esteira = malloc(sizeof(struct esteira));
    esteira->uso = 0;
    esteira->capacidade = tamanho;
    esteira->vetor = malloc(tamanho * sizeof(struct peca));
    esteira->ini = 0;
    esteira->fim = 0;
    return esteira;
}

void retira_da_esteira(p_est esteira) {
    /*
    RETIRA UMA STRUCT PECA DO VETOR DE UMA STRUCT ESTEIRA
    */
    esteira->ini = (esteira->ini + 1) % esteira->capacidade;
    esteira->uso --;
}

void coloca_na_esteira(p_est esteira) {
    /*
    ADICIONA UMA STRUCT PECA AO VETOR DA STRUCT ESTEIRA
    */
    esteira->vetor[esteira->fim] = cria_peca();
    esteira->uso ++;
    esteira->fim = (esteira->fim + 1) % esteira->capacidade;
}

void libera_esteira(p_est esteira) {
    /*
    LIBERA A MEMORIA ALOCADA PARA UMA UMA STRUCT ESTEIRA
    */
    free(esteira->vetor);
    free(esteira);
}