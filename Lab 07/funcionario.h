#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H
#include "esteira.h"

typedef struct funcionario* p_func;

struct funcionario {
    int t_a_trabalhar;
    p_peca segurando;
};

p_func cria_funcionario();

void classificador_pega(p_func classificador, p_est esteira);

void libera_funcionario(p_func funcionario);


#endif