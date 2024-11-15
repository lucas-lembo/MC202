#include <stdlib.h>

typedef struct {
    char nome[32];
    char sobrenome[16];
    int prio_atual;
    int prio_original;
    int id_heap;
    char pedido[26];
} Sobreviventes;

typedef Sobreviventes* p_sob;

p_sob cria_sobrevivente();

void atribui_pedido(p_sob sobrevivente, char operacao[40]);

void altera_prioridade(p_sob sobrevivente, char operacao[40], int alteracao);