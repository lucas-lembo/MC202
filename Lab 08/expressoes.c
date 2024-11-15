#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"



int main() {
    int n_expressoes;
    scanf("%d ", &n_expressoes);
    p_pilha topo;
    p_no raiz;
    for (int i = 0; i < n_expressoes; i++) {
        topo = cria_pilha();
        empilha_expressao(topo);
        raiz = monta_arvore(topo, raiz);
        imprime_infixa(raiz);
        printf("\n");
        reduz_expressao(raiz);
        imprime_resultado(raiz);
        printf("\n");
        if (i < n_expressoes - 1) {
            printf("\n");
        }
        if (topo != NULL) {
            free(topo);
        }
        if (raiz != NULL) {
        desaloca_arvore(raiz);
        }
    }
    return 0;
}