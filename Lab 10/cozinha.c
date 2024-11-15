#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filaprio.h"

int main() {
    int n_panelas, n_sobreviventes;
    scanf("%d %d ", &n_panelas, &n_sobreviventes);
    p_fp fprio = criar_filaprio(n_sobreviventes);   // CRIA UMA FILA DE PRIORIDADE PARA SOBREVIVENTES
    p_sob* lista_sobreviventes = malloc(n_sobreviventes * sizeof(Sobreviventes));   // CRIA UMA LISTA DE SOBREVIVENTES
    for (int i = 0; i < n_sobreviventes; i++) {
        // CRIA E INSERE OS SOBREVIVENTES NA LISTA DE SOBREVIVENTES
        p_sob sobrevivente = cria_sobrevivente(i);
        insere_na_lista(lista_sobreviventes, sobrevivente, i);
    }
    int pedidos_rodada, pedidos_total = 0;
    int rodada = 1;
    int pedidos_entregues = 0;
    printf("---- rodada %d ----\n", rodada);
    scanf("%d ", &pedidos_rodada);
    pedidos_total += pedidos_rodada;
    int pula_entrada = 1;
    while (1) {
        // SE AINDA HOUVEREM PEDIDOS A SEREM FEITOS, EXECUTAR A ADICAO NA FILA DE PRIORIDADE
        if (pedidos_rodada != 0) {
            char operacao[40];
            fgets(operacao, 39, stdin); // ARMAZENA A LINHA DO INPUT
            char comando[7];
            sscanf(operacao, "%s ", comando);   //ARMAZENA QUAL É O COMANDO DESEJADO PELO OPERADOR
            if (strcmp(comando, "novo") == 0) { // SE O OPERADOR DESEJA REALIZAR UM NOVO PEDIDO PARA UM SOBREVIVENTE
                int id;
                sscanf(operacao, "%*s %d ", &id);
                atribui_pedido(lista_sobreviventes[id], operacao);
                inserir_na_fprio(fprio, lista_sobreviventes[id]);
            } else {    // SE O OPERADOR DESEJA ALTERAR A PRIORIDADE DE UM SOBREVIVENTE
                int id;
                sscanf(operacao, "%*s %d ", &id);
                int alteracao;
                sscanf(operacao, "%*s %*d %d ", &alteracao);
                altera_prioridade(lista_sobreviventes[id], operacao, alteracao);
                if (alteracao > 0) {    // SE A ALTERACAO FOR UM VALOR POSITIVO
                    sobe_no_heap(fprio, lista_sobreviventes[id]->id_heap);
                } else {    // SE A ALTERACAO FOR UM VALOR NEGATIVO
                    desce_no_heap(fprio, lista_sobreviventes[id]->id_heap);
                }
                pedidos_total--;
            }
        }
        if (pedidos_rodada != 0) {  // CONDICAO UTILIZADA PARA O NUMERO DE PEDIDOS NÃO SER NEGATIVO
            pedidos_rodada--;
        }
        if (pedidos_rodada == 0) {  // SE TODOS OS PEDIDOS DA RODADA FORAM ADICIONADOS NA FILA DE PRIORIDADE
            for (int i = 0; i < n_panelas; i++) {
                if (fprio->n != 0) {    // IMPRIME OS PEDIDOS QUE FORAM ENTREGUES
                    printa_e_extrai_maximo(fprio);
                    pedidos_entregues++;
                }
            }
            if (pula_entrada != 0) {    // CONDICAO E VARIAVEL CRIADOS PARA IGNORAR NOVOS PEDIDOS QUANDO O INPUT FOR 0
                scanf("%d ", &pedidos_rodada);
                if (pedidos_rodada == 0) {
                    pula_entrada = 0;
                }
            }
            pedidos_total += pedidos_rodada;
            rodada++;
            if (pedidos_entregues == pedidos_total) {   // SE TODOS OS PEDIDOS FOREM ENTREGUES
                break;
            }
            printf("---- rodada %d ----\n", rodada);
        }
    }
    libera_memoria(fprio, n_sobreviventes, lista_sobreviventes);
    return 0;
}