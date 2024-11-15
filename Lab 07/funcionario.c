#include <stdio.h>
#include <stdlib.h>
#include "funcionario.h"
#ifndef PILHAH
#define PILHAH

p_func cria_funcionario() {
    /*
    ALOCA MEMORIA PARA UMA VARIAVEL DO TIPO STRUCT FUNCIONARIO
    */
    p_func funcionario = malloc(sizeof(struct funcionario));
    funcionario->segurando = NULL;
    funcionario->t_a_trabalhar = 0;
    return funcionario;
}

void classificador_pega(p_func classificador, p_est esteira) {
    /*
    FAZ COM QUE O CLASSIFICADOR RETIRE UMA PECA DA ESTEIRA E PASSE A SEGURÁ-LA
    */
    classificador->segurando = esteira->vetor[esteira->ini];
    classificador->t_a_trabalhar = esteira->vetor[esteira->ini]->t_classificacao - 1;
}

void libera_funcionario(p_func funcionario) {
    /*
    LIBERA A MEMORIA ALOCADA PARA UMA STRUCT FUNCIONADO
    */
    free(funcionario);
}

#endif