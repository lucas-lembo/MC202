#define MAX 56

typedef struct no *p_no;

struct no {
    char livro[MAX];
    p_no prox;
};

p_no criar_lista();

void imprime_lista(p_no cabeca);

void desfaz_lista(p_no cabeca);
