#include "pilha.h"
#include <stdlib.h>
#include <stdio.h>

p_pilha cria_pilha() {
    /*
    CRIA A BASE DE UMA PILHA
    */
    p_pilha p = malloc(sizeof(struct pilha));
    p->prox = NULL;
    return p;
}

void empilha_expressao(p_pilha topo) {
    /*
    EMPILHA TODOS OS CARACTERES FORNECIDOS PELO OPERADOR DO PROGRAMA
    EM UMA PILHA
    */
    while (1) {
        char dado;
        scanf("%c", &dado);
        if (dado == '\n'){
            break;
        }
        p_pilha novo = malloc(sizeof(struct pilha));
        novo->prox = topo->prox;
        topo->prox = novo;
        novo->dado = dado;
    }
}

void desempilha_dado(p_pilha topo) {
    /*
    DESEMPILHA UM CARACTERE DE UMA PILHA
    */
    p_pilha aux = malloc(sizeof(struct pilha));
    aux->prox = topo->prox;
    topo->prox = aux->prox->prox;
    free(aux->prox);
    free(aux);
}
