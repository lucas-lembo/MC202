#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvore.h"

int eh_vermelho(p_no no) {
    /*
    VERIFICA SE A COR DO NÓ DE UMA ARVORE É VERMELHO
    */
    if (no == NULL) {
        return 0;
    }
    return no->cor == VERMELHO;
}

int eh_preto(p_no no) {
    /*
    VERIFICA SE A COR DO NÓ DE UMA ARVORE É PRETO
    */
    if (no == NULL) {
        return 1;
    }
    return no->cor == PRETO;
}

p_no rotaciona_esquerda(p_no raiz) {
    /*
    REALIZA A ROTAÇÃO DOS NÓS DE UMA ARVORE PARA A ESQUERDA
    */
    p_no no = raiz->dir;
    raiz->dir = no->esq;
    no->esq = raiz;
    no->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return no;
}

p_no rotaciona_direita(p_no raiz) {
    /*
    REALIZA A RTAÇÃO DOS NÓS DE UMA ARVORE PARA A DIREITA
    */
    p_no no = raiz->esq;
    raiz->esq = no->dir;
    no->dir = raiz;
    no->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return no;
}

void sobe_vermelho(p_no raiz) {
    /*
    FAZ COM QUE A COR VERMELHA VÁ PARA O PAI, PARA MANTER AS
    PROPRIEDADES DA ARVORE RUBRO NEGRA
    */
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

p_no cria_no (char linha[MAX]) {
    /*
    CRIA UM NÓ DE UMA ARVORE RUBRO NEGRA
    */
    p_no novo = malloc(sizeof(struct no));
    sscanf(linha, "%s", novo->tipo);
    sscanf(linha, "%*s %s", novo->nome);
    int tamanho = strlen(novo->nome);
    if (novo->nome[tamanho - 1] == ';') {
        novo->nome[tamanho - 1] = '\000';
    }
    novo->esq = novo->dir = NULL;
    novo->cor = VERMELHO;
    return novo;
}

p_no adiciona_no(char linha[MAX], p_no raiz) {
    /*
    ADICIONA UM NÓ EM UMA ARVORE NO LOCAL ADEQUADO
    */
    char nome[MAX];
    sscanf(linha, "%*s %s", nome);
    int tamanho = strlen(nome);
    if (nome[tamanho - 1] == ';') {
        nome[tamanho - 1] = '\000';
    }
    if (strcmp(nome, raiz->nome) < 0) {
        if (raiz->esq != NULL) {
            raiz->esq = adiciona_no(linha, raiz->esq);
        } else {
            raiz->esq = cria_no(linha);
        }
    } else {
        if (raiz->dir != NULL) {
            raiz->dir = adiciona_no(linha, raiz->dir);
        } else {
            raiz->dir = cria_no(linha);
        }
    }
    if (eh_vermelho(raiz->dir) && eh_preto(raiz->esq)) {
        raiz = rotaciona_esquerda(raiz);
    }
    if (eh_vermelho(raiz->esq) && eh_vermelho(raiz->esq->esq)) {
        raiz = rotaciona_direita(raiz);
    }
    if (eh_vermelho(raiz->esq) && eh_vermelho(raiz->dir)) {
        sobe_vermelho(raiz);
    }
    return raiz;
}

int ta_na_arvore(char simbolo[MAX], p_no raiz) {
    /*
    VERIFICA SE UM SIMBOLO ESTÁ ARMAZENADO EM UM NÓ DA ARVORE RUBRO NEGRA
    */
    if (strcmp(simbolo, raiz->nome) == 0) {
        return 1;
    } else if (strcmp(simbolo, raiz->nome) < 0 && raiz->esq != NULL) {
        return ta_na_arvore(simbolo, raiz->esq);
    } else if (strcmp(simbolo, raiz->nome) > 0 && raiz->dir != NULL) {
        return ta_na_arvore(simbolo, raiz->dir);
    }
    return 0;
}

p_no acha_tipo(char simbolo[MAX], p_no raiz) {
    /*
    RETORNA UM PONTEIRO QUE APONTA PARA UM DETERMINADO NÓ, PARA QUE SEU TIPO
    POSSA SER USADO EM OUTRA FUNCAO
    */
    p_no p = NULL;
    if (strcmp(simbolo, raiz->nome) == 0) {
        p = raiz;
        return p;
    } else if (strcmp(simbolo, raiz->nome) < 0 && raiz->esq != NULL) {
        return acha_tipo(simbolo, raiz->esq);
    } else if (strcmp(simbolo, raiz->nome) > 0 && raiz->dir != NULL) {
        return acha_tipo(simbolo, raiz->dir);
    }
    return p;
}

int verifica_erros(char linha[MAX], p_no raiz, int n, int erros) {
    /*
    VERIFICA SE HA ERROS NA EXPRESSAO DADA
    */
    char simb1[MAX];
    sscanf(linha, "%s", simb1);
    int tamanho1 = strlen(simb1);
    if (simb1[tamanho1 - 1] == ';') {
        simb1[tamanho1 - 1] = '\000';
    }
    char simb2[MAX];
    sscanf(linha, "%*s %*s %s", simb2);
    int tamanho2 = strlen(simb2);
    if (simb2[tamanho2 - 1] == ';') {
        simb2[tamanho2 - 1] = '\000';
    }
    char simb3[MAX];
    sscanf(linha, "%*s %*s %*s %*s %s", simb3);
    int tamanho3 = strlen(simb3);
    if (simb3[tamanho3 - 1] == ';') {
        simb3[tamanho3 - 1] = '\000';
    }
    char operador;
    sscanf(linha, "%*s %*s %*s %c", &operador);

    // 1o ver se esta definido (buscar na arvore)
    if (raiz == NULL) {
        printf("Linha %d: o símbolo %s não foi definido.\n", n, simb1);
        erros++;
        return erros;
    } else if (ta_na_arvore(simb1, raiz)) {
        if (ta_na_arvore(simb2, raiz)) {
            if (ta_na_arvore(simb3, raiz) == 0) {
                printf("Linha %d: o símbolo %s não foi definido.\n", n, simb3);
                erros++;
                return erros;
            }
        } else {
            printf("Linha %d: o símbolo %s não foi definido.\n", n, simb2);
            erros++;
            return erros;
        }

    } else {
        printf("Linha %d: o símbolo %s não foi definido.\n", n, simb1);
        erros++;
        return erros;
    }
    
    // 2o ver se o tipo do simb2 e simb3 sao iguais
    p_no p1 = acha_tipo(simb1, raiz);
    p_no p2 = acha_tipo(simb2, raiz);
    p_no p3 = acha_tipo(simb3, raiz);
    if (strcmp(p2->tipo, p3->tipo) != 0) {
        printf("Linha %d: tipos incompatíveis: %s (%s) %c %s (%s).\n", n, simb2, p2->tipo, operador, simb3, p3->tipo);
        erros++;
        return erros;
    }
    // 3o ver se o resultado da expressao tem o mesmo tipo do simb1 
    if (strcmp(p1->tipo, p2->tipo) != 0) {
        printf("Linha %d: tipos incompatíveis: o símbolo %s espera %s, obteve %s.\n", n, simb1, p1->tipo, p2->tipo);
        erros++;
        return erros;
    }
    return erros;
}

void imprime_variaveis(p_no raiz) {
    /*
    IMPRIME TODAS AS VARIAVEIS QUE FORAM DECLARADAS EM ORDEM ALFABETICA
    */
    if (raiz->esq != NULL) {
        imprime_variaveis(raiz->esq);
    }
    printf("%s %s\n", raiz->nome, raiz->tipo);
    if (raiz->dir != NULL) {
        imprime_variaveis(raiz->dir);
    }
}

void desaloca_arvore(p_no raiz) {
    /*
    DESALOCA O ESPAÇO DA MEMORIA OCUPADO PELA ARVORE
    */
    if (raiz == NULL) {
        return;
    }
    desaloca_arvore(raiz->esq);
    desaloca_arvore(raiz->dir);
    free(raiz);
}