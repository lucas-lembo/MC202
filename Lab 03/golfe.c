#include "partida.h"

int main() {
    int n_partidas;
    scanf("%d ", &n_partidas); 
    for (int i = 1; i <= n_partidas; i++) {
        // ARMAZENA DADOS PARTIDA
        partida var_partida;
        int n_jogadores, n_circuitos, n_equipamentos;
        scanf("%d %d %d", &n_jogadores, &n_circuitos, &n_equipamentos);
        double aluguel = 10 * n_circuitos + 17.50 * n_equipamentos;
        circuito *infos_circuitos = malloc(n_circuitos * sizeof(circuito));
        var_partida = le_dados_partida(aluguel, i, n_jogadores, infos_circuitos);
        for (int j = 0; j < n_circuitos; j++) {
            // ARMAZENA DADOS DE CADA CIRCUITO DA PARTIDA
            circuito var_circuito;
            int id_circuito, *jogadas = malloc(n_jogadores * sizeof(int));
            scanf("%d", &id_circuito);
            for (int k = 0; k < n_jogadores; k++) {
                scanf("%d", &jogadas[k]);
            }
            var_circuito = le_dados_circuito(id_circuito, n_jogadores, jogadas);
            infos_circuitos[j] = var_circuito;
        }
        // CALCULOS DOS DADOS DA PARTIDA PARA O PRINT
        int *jogadas_somadas = malloc(n_jogadores * sizeof(int));
        soma_jogadas(var_partida, jogadas_somadas,n_circuitos, n_jogadores);
        int pior_circuito = acha_pior_circuito(var_partida, jogadas_somadas, n_circuitos, n_jogadores);
        imprime_relatorio(var_partida.id, n_jogadores, n_circuitos, n_equipamentos, var_partida, jogadas_somadas, pior_circuito);
        for (int j = 0; j < n_circuitos; j++) {
            free(var_partida.infos_circuitos[j].jogadas);
        }
        free(var_partida.infos_circuitos);
        free(jogadas_somadas);
    }
    return 0;
}