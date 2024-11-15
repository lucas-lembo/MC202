#include <stdio.h>
#include <stdlib.h>
#include "funcionario.h"
#include "esteira.h"
#include "pilha.h"
#include "peca.h"

void imprime_minuto(int tempo, int in_clas, int out_clas, int in_emb, int out_emb) {
    printf("Min. %d: Classificação (+%d,-%d) | Embalagem (+%d,-%d).\n", tempo, in_clas, out_clas, in_emb, out_emb);
}

int main() {
    // INPUT
    int tam_esteira, tam_pilha, n_entradas;
    scanf("%d %d", &tam_esteira, &tam_pilha);
    scanf("%d", &n_entradas);
    // MONTAGEM DE VARIAVEIS
    p_est esteira = monta_esteira(tam_esteira);
    p_pilha pilha = monta_pilha(tam_pilha);
    p_func classificador = cria_funcionario();
    p_func embalador = cria_funcionario();
    int entrada = 0;
    int atraso = 0;
    int tempo = 1;
    int pecas_prontas = 0;
    do {
        int entrada_classificacao = 0;
        int saida_classificacao = 0;
        int entrada_embalagem = 0;
        int saida_embalagem = 0;
        if (embalador->t_a_trabalhar == 0) { //  EMBALADOR NAO ESTA TRABALHANDO
            if (embalador->segurando != NULL) { //  EMBALADOR NAO ESTA SEGURANDO UMA PECA
                free(embalador->segurando);
                embalador->segurando = NULL;
                saida_embalagem ++;
                pecas_prontas ++;
            }
            if (pilha->uso != 0) { // PILHA NAO ESTA VAZIA
                embalador_segura(pilha, embalador);
                retira_da_pilha(pilha);
            }
        } else {
            embalador->t_a_trabalhar --;
        }
        if (pilha->uso != pilha->capacidade) { // PILHA NAO ESTA CHEIA
            if (classificador->t_a_trabalhar == 0 && classificador->segurando != NULL) { // CLASSIFICADOR TERMINOU DE CLASSIFICAR UMA PECA
                coloca_na_pilha(pilha, classificador);
                entrada_embalagem ++;
                saida_classificacao ++;
            }
        }
        if (classificador->t_a_trabalhar == 0) { // CLASSIFICADOR NAO ESTA TRABALHANDO
            if (esteira->uso != 0) { // ESTEIRA NAO ESTA VAZIA
                if (classificador->segurando == NULL) { // CLASSIFICADOR NAO ESTA SEGURANDO NENHUMA PECA
                    classificador_pega(classificador, esteira);
                    retira_da_esteira(esteira);
                }
            }
        } else {
            classificador->t_a_trabalhar --;
        }
        if (esteira->uso != esteira->capacidade) { // ESTEIRA NAO ESTA CHEIA
            if (entrada < n_entradas) {
                coloca_na_esteira(esteira);
                entrada_classificacao ++;
                entrada++;
            }
        } else if (esteira->uso == esteira->capacidade && entrada < n_entradas) { // ESTEIRA ESTA CHEIA E AINDA NÃO FORAM COLOCADAS TODAS AS PECAS NA ESTEIRA
            atraso ++;
        }
        if (entrada == 1) {
            printf("##### Simulação\n");
        }
        imprime_minuto(tempo, entrada_classificacao, saida_classificacao, entrada_embalagem, saida_embalagem);
        tempo ++;
    } while (pecas_prontas < n_entradas); // ENQUANTO TODAS AS PECAS NAO ESTAO PRONTAS
    printf("Tempo atraso: %d.\n", atraso);
    libera_esteira(esteira);
    libera_pilha(pilha);
    libera_funcionario(classificador);
    libera_funcionario(embalador);
    return 0;
}