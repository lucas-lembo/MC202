#include "no.h"
#include <stdlib.h>
#include <stdio.h>

p_no criar_lista() {
    /*
    CRIA A CABECA DE UMA ESTRUTURA DE LISTA LIGADA
    */
    p_no cabeca = malloc(sizeof(struct no));
    cabeca->prox = NULL;
    return cabeca;
}

void imprime_lista(p_no cabeca) {
    /*
    IMPRIME UMA LISTA LIGADA
    */
    p_no elemento;
    for (elemento = cabeca->prox; elemento != NULL; elemento = elemento->prox) {
        if (elemento == cabeca->prox) {
            printf("%s", elemento->livro);
        } else {
            printf(", %s", elemento->livro);
        }
    }
    printf("\n");
    free(elemento);
}

void desfaz_lista(p_no cabeca) {
    /*
    DESALOCA A MEMORIA DE UMA LISTA LIGADA
    */
    if (cabeca != NULL) {
        desfaz_lista(cabeca->prox);
        free(cabeca);
    }
}

