#include "partida.h"

partida le_dados_partida(double aluguel, int id_partida, int n_jogadores,
                        circuito *infos_circuitos) {
    /*
    ARMAZENA TODOS OS DADOS DE UMA PARTIDA
    */
    partida p;
    p.aluguel = aluguel;
    p.id = id_partida;
    p.jogadores = n_jogadores;
    p.infos_circuitos = infos_circuitos;
    return p;
}
 
void imprime_relatorio(int id_partida, int n_jogadores, int n_circuitos,
                       int n_equipamentos, partida var_partida, int *jogadas_somadas, int pior_circuito) {
    /*
    IMPRIME TODAS AS INFORMAÇOES QUE COMPOEM O RELATORIO DA PARTIDA
    */
    printf("Partida %d\n", id_partida);
    printf("Num. de Jogadores: %d - Num. de Circuitos: %d - Num. de Equipamentos: %d\n", n_jogadores, n_circuitos, n_equipamentos);
    printf("Valor do Aluguel: R$ %.2f\n", var_partida.aluguel);
    for (int i = 1; i <= n_jogadores; i++) {
        printf("Jogador %d: %d\n", i, jogadas_somadas[i - 1]);
    }
    printf("Circuito mais dificil: %d\n", pior_circuito);
    printf("##########\n");
}

void soma_jogadas(partida var_partida, int *jogadas_somadas,int n_circuitos, int n_jogadores) {
    /*
    SOMA TODAS AS JOGADAS QUE CADA JOGADOR REALIZOU EM TODOS OS CIRCUITOS
    E ARMAZENA EM UM VETOR, EM QUE CADA POSICAO DO VETOR REPRESENTA UM JOGADOR
    */
    for (int i = 0; i < n_circuitos; i++) {
        for (int j = 0; j < n_jogadores; j++) {
            if (i == 0) {
                jogadas_somadas[j] = var_partida.infos_circuitos[i].jogadas[j];
            } else {
                jogadas_somadas[j] += var_partida.infos_circuitos[i].jogadas[j];
            }
        }
    }
}

int acha_pior_circuito(partida var_partida, int *jogadas_somadas, int n_circuitos, int n_jogadores) {
    /*
    RETORNA A IDENTIFICACAO DO CIRCUITO EM QUE HOUVE O MAIOR NUMERO DE JOGADAS
    */
    int maior_soma = 0;
    int pior_circuito;
    for (int i = 0; i < n_circuitos; i++) {
        int soma_circuito = 0;
        for (int j = 0; j < n_jogadores; j++) {
            soma_circuito += var_partida.infos_circuitos[i].jogadas[j];
            if (soma_circuito > maior_soma) {
            maior_soma = soma_circuito;
            pior_circuito = var_partida.infos_circuitos[i].id;
            }
        }
    }
    return pior_circuito;
}