#include "referencia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


p_ref criar_referencia(p_no cabeca) {
    /*
    CRIA UM PONTEIRO DA STRUCT P_REF, QUE ARMAZENA O INICIO, O FINAL E
    A ULTIMA MODIFICACAO EM UMA LISTA LIGADA
    */
    p_ref r = malloc(sizeof(struct referencia));
    r->inicio = cabeca;
    r->fim = cabeca;
    r->atual = cabeca;
    return r;
}


void arruma_string(char lista[MAX]) {
    /*
    SUBSTITUI O CARACTERE '\N' PELO CARACTERE '\0' EM UM VETOR DE CHAR,
    AFIM DE TRANSFORMÁ-LO NUMA STRING
    */
    int i;
    for (i = 0; lista[i] != '\n'; i++) {
    }
    lista[i] = '\0';
}

void adiciona_livro(p_no cabeca, p_ref referencia) {
    /*
    ADICIONA UM NOVO NÓ NA LISTA LIGADA, OU SEJA, ADICIONA UM NOVO LIVRO NA POSICAO
    SOLICITADA PELO OPERADOR DO PROGRAMA
    */
    p_no novo_no;
    novo_no = malloc(sizeof(struct no));
    fgets(novo_no->livro, MAX, stdin);
    arruma_string(novo_no->livro);
    if (referencia->atual == cabeca && referencia->fim == cabeca) { //add somente primeiro elemento
        cabeca->prox = novo_no;
        novo_no->prox = NULL;
        referencia->atual = novo_no;
        referencia->inicio = novo_no;
        referencia->fim = novo_no;
    } else if (referencia->atual == cabeca) { //add no inicio
        novo_no->prox = cabeca->prox;
        cabeca->prox = novo_no;
        referencia->atual = cabeca->prox;
        referencia->inicio = cabeca->prox;
    } else if (referencia->atual == referencia->fim) { //add no final
        novo_no->prox = NULL;
        referencia->atual->prox = novo_no;
        referencia->atual = referencia->atual->prox;
        referencia->fim = referencia->atual;
    } else { //add do segundo elemento em diante no inicio
        novo_no->prox = referencia->atual->prox;
        referencia->atual->prox = novo_no;
        referencia->atual = referencia->atual->prox;
    }
}

void transforma_inicio(p_no cabeca, p_ref referencia) {
    /*
    FAZ COM QUE A POSICAO DE INSERCAO DOS LIVROS NA LISTA LIGADA SEJA O INICIO DA LISTA
    */
    referencia->atual = cabeca;
}

void transforma_final(p_ref referencia) {
    /*
    FAZ COM QUE A POSICAO DE INSERCAO DOS LIVROS NA LISTA LIGADA SEJA O FINAL DA LISTA
    */
    referencia->atual = referencia->fim;
}

void remove_livro(p_no cabeca, p_ref referencia) {
    /*
    REMOVE DA LISTA LIGADA O NÓ QUE POSSUI O LIVRO SOLICITADO PELO OPERADOR
    DO PROGRAMA
    */
    char livro_a_remover[MAX];
    fgets(livro_a_remover, MAX, stdin);
    arruma_string(livro_a_remover);
    p_no busca_livro;
    for (busca_livro = cabeca; busca_livro->prox != NULL; busca_livro = busca_livro->prox) {
        if (strcmp(livro_a_remover, busca_livro->prox->livro) == 0) {
            p_no auxiliar;
            auxiliar = busca_livro->prox;
            if (referencia->atual == busca_livro->prox) {    
                referencia->atual = busca_livro;
            }
            if (busca_livro->prox == referencia->fim) {
                referencia->fim = busca_livro;
            }
            busca_livro->prox = busca_livro->prox->prox;
            free(auxiliar);
            break;
        }
    }
}

void verifica_comando(char comando[10], p_no cabeca, p_ref referencia) {
    /*
    DIRECIONA O PROGRAMA PARA A FUNCAO CORRESPONDENTE AO COMANDO DO USUARIO
    DO PROGRAMA
    */
    if (comando[0] == 'a') {
        adiciona_livro(cabeca, referencia);
    } else if (comando[1] == 'n') {
        transforma_inicio(cabeca, referencia);
    } else if (comando[0] == 'f') {
        transforma_final(referencia);
    } else if (comando[0] == 'r') {
        remove_livro(cabeca, referencia);
    } else if (comando[1] == 'm') {
        imprime_lista(cabeca);
    }
}

