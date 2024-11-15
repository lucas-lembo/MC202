#ifndef PILHA_H
#define PILHA_H
#include "peca.h"
#include "funcionario.h"

typedef struct pilha* p_pilha;

struct pilha {
    int uso;
    int capacidade;
    p_peca topo;
};

p_pilha monta_pilha(int tamanho);

void libera_pilha(p_pilha pilha);

void retira_da_pilha(p_pilha pilha);

void coloca_na_pilha(p_pilha pilha, p_func classificador);

void embalador_segura(p_pilha pilha, p_func embalador);

#endif