#include <stdio.h>
#include <stdlib.h>

void monta_quadra(int** quadra_vazia, int ordem) {
    for (int i = 0; i < ordem; i++) {
        quadra_vazia[i] = malloc(ordem * sizeof(int));
        for (int j = 0; j < ordem; j++) {
            scanf("%d ", &quadra_vazia[i][j]);
        }
    }
}

void desaloca_quadra(int** quadra, int ordem) {
    for (int i = 0; i < ordem; i++) {
        free(quadra[i]);
    }
    free(quadra);
}

void printa_quadra(int** quadra, int ordem) {
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            printf("%d\t", quadra[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int acha_maior_submatriz(int** quadra, int ordem) {
    int maior_soma = -1000000000;
    int maior_submatriz;
    for (int k = 0; k <= 1; k ++) {
        for (int l = 0; l <= 1; l++) {
            int soma_matriz = 0;
            for (int i = 0; i < ordem - 1; i++) {
                for (int j = 0; j < ordem - 1; j++) {
                    soma_matriz += quadra[i + k][j + l];
                }
            }
            if (soma_matriz > maior_soma) {
                maior_soma = soma_matriz;
                if (k == 0 && l == 0) {
                    maior_submatriz = 1;
                } else if (k == 0 && l == 1) {
                    maior_submatriz = 2;
                } else if (k == 1 && l == 0) {
                    maior_submatriz = 3;
                } else {
                    maior_submatriz = 4;
                }
            }
        }
    }
    return maior_submatriz;
}

int** reduz_quadra(int** quadra, int ordem, int maior_submatriz) {
    int k;
    int l;
    if (maior_submatriz == 1) {
        k = 0;
        l = 0;
    } else if (maior_submatriz == 2) {
        k = 0;
        l = 1;
    } else if (maior_submatriz == 3) {
        k = 1;
        l = 0;
    } else {
        k = 1;
        l = 1;
    }
    int** quadra_reduzida = malloc((ordem - 1) * sizeof (int*));
    for (int i = 0; i < ordem - 1; i++) {
        quadra_reduzida[i] = malloc((ordem - 1) * sizeof(int));
        for (int j = 0; j < ordem - 1; j++) {
             quadra_reduzida[i][j] = quadra[i + k][j + l];
        }
    }
    desaloca_quadra(quadra, ordem);
    return quadra_reduzida;
}

void substitui_elemento(int** quadra) {
    int i_mod, j_mod, novo_elemento;
    scanf("%d %d %d", &i_mod, &j_mod, &novo_elemento);
    quadra[i_mod][j_mod] = novo_elemento;
}

int main() {
    int lc;
    scanf("%d", &lc);
    int** quadra = malloc(lc * sizeof(int *));
    monta_quadra(quadra, lc);
    printf("Quadras:\n");
    printa_quadra(quadra, lc);
    int alt;
    do {
        int maior_submariz = acha_maior_submatriz(quadra, lc);
        quadra = reduz_quadra(quadra, lc, maior_submariz);
        lc -= 1;
        printf("Conjuntos que precisam de atenção:\n");
        printa_quadra(quadra, lc);
        alt = 0;
        scanf("%d", &alt);
        if (alt == 1) {
            substitui_elemento(quadra);
        }
    } while (lc != 0 && alt == 1);
    desaloca_quadra(quadra, lc);
    return 0;
}