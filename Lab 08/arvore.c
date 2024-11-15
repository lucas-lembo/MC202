#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"

int eh_operador(char caractere) {
    /*
    VERIFICA SE O CARACTERE DESEJADO É UM OPERADOR OU NÃO
    */
    if (caractere == '|' || caractere == '&' || caractere == '{' || caractere == '}'
    || caractere == '>' || caractere == '<' || caractere == '=' || caractere == '!') {
        return 1;
    }
    return 0;
}


p_no monta_arvore(p_pilha topo, p_no raiz) {
    /*
    MONTA UMA ARVORE DE ACORDO COM A ORDEM EM QUE
    CARACTERES SÃO DESEMPILHADOS DE UMA PILHA
    */
    raiz = malloc(sizeof(struct no));
    raiz->esq = NULL;
    raiz->dir = NULL;
    raiz->dado = topo->prox->dado;
    if (topo->prox == NULL) {
        free(raiz);
    }
    desempilha_dado(topo);
    if (eh_operador(raiz->dado)) {
        raiz->dir = monta_arvore(topo, raiz->dir);
        raiz->esq = monta_arvore(topo, raiz->esq);
    }
    return raiz;
}


int eh_variavel(p_no filho) {
    /*
    VERIFICA SE O CARACTERE É UMA VARIÁVEL OU NÃO
    */
    int id_filho = filho->dado;
    if (96 < id_filho && id_filho < 123) {
        return 1;
    }
    return 0;
}

int eh_inteiro(p_no filho) {
    /*
    VERIFICA SE O CARACTERE É UM INTEIRO OU NÃO
    */
    int id_filho = filho->dado;
    if (47 < id_filho && id_filho < 58) {
        return 1;
    }
    return 0;
}

void imprime_infixa(p_no raiz) {
    /*
    IMPRIME OS ELEMENTOS DE UMA ÁRVORE EM ORDEM INFIXA
    */
    if (raiz != NULL) {
        if (eh_operador(raiz->dado)) {
            printf("(");
        }
        imprime_infixa(raiz->esq);
        if (eh_variavel(raiz) == 0 && eh_inteiro(raiz) == 0 && raiz->dado != 'F' && raiz->dado != 'T') {
            printf(" %c ", raiz->dado);
        } else {
            printf("%c", raiz->dado);
        }
        imprime_infixa(raiz->dir);
        if (eh_operador(raiz->dado)) {
            printf(")");
        }
    }
}

void desaloca_arvore(p_no raiz) {
    /*
    DESALOCA O ESPAÇO OCUPAD0 PELA ARVORE NA MEMORIA
    */
    if (raiz == NULL) {
        return;
    }
    desaloca_arvore(raiz->esq);
    desaloca_arvore(raiz->dir);
    free(raiz);
}

void acha_resultado(p_no raiz) {
    /*
    DETERMINA O RETORNO CORRETO PARA A OPERAÇÃO ENTRE UM NÓ E SEUS FILHOS
    */
    int id_esq = raiz->esq->dado;
    int id_dir = raiz->dir->dado;
    if (eh_inteiro(raiz->esq) && eh_inteiro(raiz->dir)) {
        if ((id_esq > id_dir && (raiz->dado == '>' || raiz->dado == '}')) || (id_esq < id_dir && (raiz->dado == '<' || raiz->dado == '{')) || (id_esq != id_dir && raiz->dado == '!') || 
            (id_esq == id_dir && (raiz->dado == '{' || raiz->dado == '}'))) {
            raiz->dado = 'T';
            desaloca_arvore(raiz->esq);
            raiz->esq = NULL;
            desaloca_arvore(raiz->dir);
            raiz->dir = NULL;
        } else {
            raiz->dado = 'F';
            desaloca_arvore(raiz->esq);
            raiz->esq = NULL;
            desaloca_arvore(raiz->dir);
            raiz->dir = NULL;
        }
    } else if ((eh_variavel(raiz->esq) && raiz->dado == '{' && raiz->dir->dado == '9') || // qualquer variavel <= 9 é T
        (eh_variavel(raiz->dir) && raiz->dado == '}' && raiz->esq->dado == '9')) {
        raiz->dado = 'T';
        desaloca_arvore(raiz->esq);
        raiz->esq = NULL;
        desaloca_arvore(raiz->dir);
        raiz->dir = NULL;
    } else if ((eh_variavel(raiz->esq) && raiz->dado == '}' && raiz->dir->dado == '0') || // qualquer variavel >= 0 é T
                (eh_variavel(raiz->dir) && raiz->dado == '{' && raiz->esq->dado == '0')) {
        raiz->dado = 'T';
        desaloca_arvore(raiz->esq);
        raiz->esq = NULL;
        desaloca_arvore(raiz->dir);
        raiz->dir = NULL;
    } else if ((eh_variavel(raiz->esq) && raiz->dado == '>' && raiz->dir->dado == '9') || // qualquer variavel > 9 é F
                (eh_variavel(raiz->dir) && raiz->dado == '<' && raiz->esq->dado == '9')) {
        raiz->dado = 'F';
        desaloca_arvore(raiz->esq);
        raiz->esq = NULL;
        desaloca_arvore(raiz->dir);
        raiz->dir = NULL;
    } else if ((eh_variavel(raiz->esq) && raiz->dado == '<' && raiz->dir->dado == '0') || // qualquer variavel < 0 é F
                (eh_variavel(raiz->dir) && raiz->dado == '>' && raiz->esq->dado == '0')) {
        raiz->dado = 'F';
        desaloca_arvore(raiz->esq);
        raiz->esq = NULL;
        desaloca_arvore(raiz->dir);
        raiz->dir = NULL;
    } else if (id_esq == id_dir && (eh_inteiro(raiz->dir) || eh_variavel(raiz->dir) || raiz->dir->dado == 'F' || raiz->dir->dado == 'T')) {
        if (raiz->dado == '=' || raiz->dado == '{' || raiz->dado == '}') { // x = x é T
            raiz->dado = 'T';
            desaloca_arvore(raiz->esq);
            raiz->esq = NULL;
            desaloca_arvore(raiz->dir);
            raiz->dir = NULL;
        } else if (raiz->dado == '!' || raiz->dado == '>' || raiz->dado == '<') { // x != x é F
            raiz->dado = 'F';
            desaloca_arvore(raiz->esq);
            raiz->esq = NULL;
            desaloca_arvore(raiz->dir);
            raiz->dir = NULL;
        } else if (raiz->dir->dado == 'F' && raiz->dado == '&') {
            raiz->dado = 'F';
            desaloca_arvore(raiz->esq);
            raiz->esq = NULL;
            desaloca_arvore(raiz->dir);
            raiz->dir = NULL;
        } else if (raiz->dir->dado == 'T' && raiz->dado == '|'){
            raiz->dado = 'T';
            desaloca_arvore(raiz->esq);
            raiz->esq = NULL;
            desaloca_arvore(raiz->dir);
            raiz->dir = NULL;
        }
    } else if ((raiz->esq->dado == 'T' || raiz->dir->dado == 'T') && raiz->dado == '|') { // T || qualquer coisa é T
        raiz->dado = 'T';
        desaloca_arvore(raiz->esq);
        raiz->esq = NULL;
        desaloca_arvore(raiz->dir);
        raiz->dir = NULL;
    } else if ((raiz->esq->dado == 'F' || raiz->dir->dado == 'F') && raiz->dado == '&') { // F && qualquer coisa é F
        raiz->dado = 'F';
        desaloca_arvore(raiz->esq);
        raiz->esq = NULL;
        desaloca_arvore(raiz->dir);
        raiz->dir = NULL;
    }
}

void imprime_resultado(p_no raiz) {
    /*
    IMPRIME O RESULTADO FINAL APÓS A REDUCAO DA EXPRESSAO (SE HOUVER)
    */
    imprime_infixa(raiz);
    if (raiz == NULL) {
        printf("%c", raiz->dado);
    }
}

void reduz_expressao(p_no raiz) {
    /*
    REALIZA A REDUÇÃO DA EXPRESSÃO (SE NECESSÁRIO), DE ACORDO
    COM O DADO DO NÓ E SEUS FILHOS
    */
    if (raiz->esq->esq != NULL && raiz->esq->dir != NULL && raiz->dir->esq != NULL && raiz->dir->dir != NULL) {
        reduz_expressao(raiz->esq);
        reduz_expressao(raiz->dir);
    }
    acha_resultado(raiz);
}
