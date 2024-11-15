#include <stdio.h>
#include <string.h>
#include "sobreviventes.h"

p_sob cria_sobrevivente() {
    /*
    CRIA E ATRIBUI DADOS A UM ELEMENTO DA STRUCT "SOBREVIVENTE"
    */
    p_sob s = malloc(sizeof(Sobreviventes));
    char linha[34];
    fgets(linha, 34, stdin);
    sscanf(linha, "%s", s->nome);
    sscanf(linha, "%*s %s", s->sobrenome);
    sscanf(linha, "%*s %*s %d ", &s->prio_original);
    s->prio_atual = s->prio_original;
    return s;    
}

void atribui_pedido(p_sob sobrevivente, char operacao[40]) {
    /*
    INSERE O PEDIDO FEITO POR UM SOBREVIVENTE NO CAMPO "PEDIDO"
    DA STRUCT
    */
    char pedido[26];
    sscanf(operacao, "%*s %*d %39[^\n]", pedido);
    strcpy(sobrevivente->pedido, pedido);
}

void altera_prioridade(p_sob sobrevivente, char operacao[40], int alteracao) {
    /*
    SOMA UM VALOR FORNECIDO AO CAMPO DE PRIORIDADE DE UM SOBREVIVENTE, FAZENDO COM
    QUE A SUA PRIORIDADE SEJA ALTERADA
    */
    sobrevivente->prio_atual += alteracao;
}
