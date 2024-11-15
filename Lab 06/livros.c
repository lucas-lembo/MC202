#include <stdio.h>
#include <stdlib.h>
#include "referencia.h"


int main() {
    char comando[10];
    p_no cabeca = criar_lista(); // CRIA A LISTA
    p_ref ref = criar_referencia(cabeca); // CRIA OS PONTEIROS DE REFERENCIA
    while (scanf("%s ", comando) != EOF) {
        verifica_comando(comando, cabeca, ref);
    }
    desfaz_lista(cabeca);
    free(ref);
    return 0;
}