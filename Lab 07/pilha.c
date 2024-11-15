#include "pilha.h"
#include <stdlib.h>


p_pilha monta_pilha(int tamanho) {
    p_pilha p  = malloc(sizeof(struct pilha));
    p->uso = 0;
    p->capacidade = tamanho;
    p->topo = NULL;
    return p;
}

void libera_pilha(p_pilha pilha) {
    /*
    LIBERA A MEMORIA ALOCADA PARA UMA STRUCT PILHA
    */
    free(pilha->topo);
    free(pilha);
}

void retira_da_pilha(p_pilha pilha) {
    /*
    RETIRA UMA STRUCT PECA DA LISTA LIGADA DA STRUCT PILHA
    */
    pilha->topo = pilha->topo->prox;
    pilha->uso --;
}

void coloca_na_pilha(p_pilha pilha, p_func classificador) {
    /*
    COLOCA UMA STRUCT PECA A LISTA LIGADA DA STRUCT PILHA
    */
    classificador->segurando->prox = pilha->topo;
    pilha->topo = classificador->segurando;
    pilha->uso ++;
    classificador->segurando = NULL;
}

void embalador_segura(p_pilha pilha, p_func embalador) {
    /*
    FAZ COM QUE O EMBALADOR RETIRE UMA PECA DA PILHA E PASSE A SEGURÁ-LA
    */
    embalador->segurando = pilha->topo;
    embalador->t_a_trabalhar = pilha->topo->t_embalagem - 1;
}

