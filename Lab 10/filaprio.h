#include <stdlib.h>
#include "sobreviventes.h"

typedef struct {
    p_sob* v;
    int n, tamanho;
} FP;

typedef FP* p_fp;

p_fp criar_filaprio(int tamanho);

void troca(p_sob sob_1, p_sob sob_2, p_fp fprio);

void sobe_no_heap(p_fp fprio, int k);

void inserir_na_fprio(p_fp fprio, p_sob sobrevivente);

void insere_na_lista(p_sob* lista, p_sob sobrevivente, int id);

void desce_no_heap(p_fp fprio, int k);

void printa_e_extrai_maximo(p_fp fprio);

void libera_memoria(p_fp fprio, int n_sobreviventes, p_sob* lista);