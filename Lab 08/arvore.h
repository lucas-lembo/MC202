#include "pilha.h"

typedef struct no* p_no;

struct no {
    char dado;
    p_no esq, dir;
};

int eh_operador(char caractere);

p_no monta_arvore(p_pilha topo, p_no raiz);

int eh_variavel(p_no filho);

int eh_inteiro(p_no filho);

void imprime_infixa(p_no raiz);

void acha_resultado(p_no raiz);

void imprime_resultado(p_no raiz);

void reduz_expressao(p_no raiz);

void desaloca_arvore(p_no raiz);