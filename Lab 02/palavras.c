#include <stdio.h>
#define MAX 300

void monta_documento(char matriz[MAX][MAX], int linhas, int colunas){
    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            scanf(" %c", &matriz[i][j]);
        }
    }
}

int busca_e_verifica(char palavra[21], char matriz_documento[MAX][MAX],
                     int linhas_documento, int colunas_documento){
    int tamanho_palavra;
    for (int i = 0; palavra[i] != '\0'; i++){
        tamanho_palavra = i;
    }
    int confere;
    for (int letra = 0; letra <= tamanho_palavra; letra++){
        for (int i = 0; i < linhas_documento; i++){
            for (int j = 0; j < colunas_documento; j++){
                if (palavra[letra] == matriz_documento[i][j]){
                    if (j + tamanho_palavra < colunas_documento){
                        confere = 1;
                        for (int k = 1; k <= tamanho_palavra; k++){
                            if (palavra[letra + k] != matriz_documento[i][j + k]){
                                confere = 0;
                                break;
                            }
                        }
                        if (confere == 1){
                            return confere;
                        }
                    }
                    if (j - tamanho_palavra >= 0){
                        confere = 1;
                        for (int k = 1; k <= tamanho_palavra; k++){
                            if (palavra[letra + k] != matriz_documento[i][j - k]){
                                confere = 0;
                                break;
                            } 
                        }
                        if (confere == 1){
                            return confere;
                        }
                    }
                    if (i + tamanho_palavra < linhas_documento){
                        confere = 1;
                        for (int k = 1; k <= tamanho_palavra; k++){
                            if (palavra[letra + k] != matriz_documento[i + k][j]){
                                confere = 0;
                                break;
                            }
                        }
                        if (confere == 1){
                            return confere;
                        }
                    }
                    if (i - tamanho_palavra >= 0){
                        confere = 1;
                        for (int k = 1; k <= tamanho_palavra; k++){
                            if (palavra[letra + k] != matriz_documento[i - k][j]){
                                confere = 0;
                                break;
                            } 
                        }
                        if (confere == 1){
                            return confere;
                        }
                    }
                }
            }
        }
    confere = 0;
    }
    return confere;
    
}


int main(){
    // INPUT INTEIROS
    int n_linhas, caracts_linha, n_palavras;
    scanf("%d %d %d", &n_linhas, &caracts_linha, &n_palavras);

    // INPUT DOCUMENTO
    char documento[MAX][MAX];
    monta_documento(documento, n_linhas, caracts_linha);

    // BUSCA
    for (int i = 0; i < n_palavras; i++){
        char palavra[21];
        scanf("%s ", palavra);
        int match = busca_e_verifica(palavra, documento, n_linhas, caracts_linha);
        if (match == 1){
            printf("A palavra %s está no texto! \n", palavra);
        }else{
            printf("A palavra %s não está no texto! \n", palavra);
        }
    }

}