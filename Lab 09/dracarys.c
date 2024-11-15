#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"



int tem_parenteses(char linha[MAX]) {
    /*
    VERIFICA SE HÁ PARENTESES NA LINHA
    */ 
    int tem = 0;
    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == '(') {
            tem = 1;
            break;
        }
    }
    return tem;
}

int nao_inicia_letra(char linha[MAX]) {
    /*
    VERIFICA SE A LINHA INICIA POR UMA LETRA SEM CONTAR
    ESPAÇOS DE IDENTAÇÃO
    */
    int nao_inicia = 1;
    char palavra[MAX];
    if (sscanf(linha, "%s", palavra) == 1) {
        int caract1 = palavra[0];
        if ((caract1 > 64 && caract1 < 91) || (caract1 > 96 && caract1 < 123)) {
            nao_inicia = 0;
        }
    }
    return nao_inicia;
}

int inicia_por_tipo(char linha[MAX]) {
    /*
    VERIFICA SE A LINHA COMECA POR UM TIPO
    */ 
    char palavra[MAX];
    if (sscanf(linha, "%s", palavra) == 1) {
        if (strcmp(palavra, "int") == 0 || strcmp(palavra, "char") == 0 || strcmp(palavra, "double") == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int id = 1;
    int n_erros = 0;
    p_no raiz = NULL;
    do {
        char linha[MAX];
        if (feof(stdin)) { // SE NAO HA MAIS ENTRADAS, PARAR O PROGRAMA
            if (n_erros == 0) { // SE NAO HOUVER ERROS, PRINTAR
                printf("Não há erros de tipo.\n");
            }
            imprime_variaveis(raiz);
            break;
        }
        fgets(linha, MAX, stdin); // ARMAZENA A LINHA DO PROGRAMA
        char var_return[MAX];
        sscanf(linha, "%s", var_return); // CASO ESPECIAL DA LINHA INICIAR POR RETURN
        if (tem_parenteses(linha) || nao_inicia_letra(linha)) {
            id++;
            continue;
        } else if (inicia_por_tipo(linha)) {
            if (raiz == NULL) {
                raiz = cria_no(linha);
                raiz->cor = PRETO;
            } else {
                raiz = adiciona_no(linha, raiz);
            }
        } else if (strcmp(var_return, "return") != 0) { // SE A LINHA FOR UMA EXPRESSAO
            n_erros = verifica_erros(linha, raiz, id, n_erros);
        }
        id++;
    } while (1);
    desaloca_arvore(raiz);
    return 0;
}