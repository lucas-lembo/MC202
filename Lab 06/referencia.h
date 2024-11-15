#include "no.h"

typedef struct referencia *p_ref;

struct referencia {
    p_no inicio;
    p_no fim;
    p_no atual;
};

p_ref criar_referencia(p_no cabeca);

void arruma_string(char lista[MAX]);

void adiciona_livro(p_no cabeca, p_ref referencia);

void transforma_inicio(p_no cabeca, p_ref referencia);

void transforma_final(p_ref referencia);

void remove_livro(p_no cabeca, p_ref referencia);

void verifica_comando(char comando[10], p_no cabeca, p_ref referencia);