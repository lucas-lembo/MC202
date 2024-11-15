#include "peca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

p_peca cria_peca() {
    /*
    ALOCA MEMORIA PARA UMA VARIAVEL DO TIPO STRUCT E ATRIBUI SUAS CARACTERISTICAS
    DE ACORDO COM O QUE O OPERADOR DO PROGRAMA OFERECE
    */
    p_peca peca = malloc(sizeof(struct peca));
    peca->prox = NULL;
    scanf("%s ", peca->tamanho);
    scanf("%d", &peca->tipo);
    if (strcmp(peca->tamanho, "pequena") == 0) {
        peca->t_classificacao = 1;
        if (peca->tipo == 1) {
            peca->t_embalagem = 1;
        } else {
            peca->t_embalagem = 2;
        }
    } else if (strcmp(peca->tamanho, "media") == 0) {
        peca->t_classificacao = 2;
        if (peca->tipo == 1) {
            peca->t_embalagem = 2;
        } else {
            peca->t_embalagem = 3;
        }
    } else {
        peca->t_classificacao = 3;
        if (peca->tipo == 1) {
            peca->t_embalagem = 2;
        } else {
            peca->t_embalagem = 3;
        }
    }
    return peca;
}