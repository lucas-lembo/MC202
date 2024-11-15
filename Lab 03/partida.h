#include "circuito.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double aluguel;
    int id;
    int jogadores;
    circuito *infos_circuitos;
}partida;

partida le_dados_partida(double aluguel, int id_partida, int n_jogadores,
                        circuito *infos_circuitos);
 
void imprime_relatorio(int id_partida, int n_jogadores, int n_circuitos, int n_equipamentos, partida var_partida, int *jogadas_somadas, int pior_circuito);

void soma_jogadas(partida var_partida, int *jogadas_somadas,int n_circuitos, int n_jogadores);

int acha_pior_circuito(partida var_partida, int *jogadas_somadas,int n_circuitos, int n_jogadores);