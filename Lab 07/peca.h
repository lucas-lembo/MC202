#ifndef PECA_H
#define PECA_H
typedef struct peca* p_peca;

struct peca {
    char tamanho[10];
    int tipo;
    int t_classificacao;
    int t_embalagem;
    p_peca prox;
};

p_peca cria_peca();

#endif