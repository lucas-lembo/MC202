typedef struct pilha* p_pilha;

struct pilha {
    char dado;
    p_pilha prox;
};

p_pilha cria_pilha();

void empilha_expressao(p_pilha topo);

void desempilha_dado(p_pilha topo);