#ifndef ESTEIRA_H
#define ESTEIRA_H
#include "peca.h"

typedef struct esteira* p_est;

struct esteira {
    int uso, capacidade, ini, fim;
    p_peca* vetor;
};

p_est monta_esteira(int tamanho);

void retira_da_esteira(p_est esteira);

void coloca_na_esteira(p_est esteira);

void libera_esteira(p_est esteira);

#endif