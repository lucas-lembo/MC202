#include "circuito.h"

circuito le_dados_circuito(int id_circuito, int n_jogadores, int *jogadas) {
    /*
    ARMAZENA TODOS OS DADOS DE UM CIRCUITO
    */
    circuito c;
    c.id = id_circuito;
    c.n_jogadores = n_jogadores;
    c.jogadas = jogadas;
    return c;
}