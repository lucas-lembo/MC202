#include "filaprio.h"
#include <stdio.h>

p_fp criar_filaprio(int tamanho) {
    /*
    CRIA UMA FILA DE PRIORIDADE
    */
    p_fp fprio = malloc(sizeof(FP));
    fprio->v = malloc(tamanho * sizeof(Sobreviventes));
    fprio->n = 0;
    fprio->tamanho = tamanho;
    return fprio;
}

void troca(p_sob sob_1, p_sob sob_2, p_fp fprio) {
    /*
    TROCA A POSICAO DE DOIS SOBREVIVENTES NA FILA DE PRIORIDADE
    */
    p_sob aux = fprio->v[sob_1->id_heap];
    fprio->v[sob_1->id_heap] = fprio->v[sob_2->id_heap];
    fprio->v[sob_2->id_heap] = aux;
    int id_1 = sob_1->id_heap;
    sob_1->id_heap = sob_2->id_heap;
    sob_2->id_heap = id_1;
}

#define PAI(i) ((i - 1) / 2)

void sobe_no_heap(p_fp fprio, int k) {
    /*
    UTILIZADA QUANDO UM SOBREVIVENTE TEM SUA PRIORIDADE AUMENTADA,
    FAZENDO COM QUE SUA POSIÇÃO NO HEAP SEJA ADIANTADA
    */
    if (k > 0 && fprio->v[PAI(k)]->prio_atual < fprio->v[k]->prio_atual) {
        troca(fprio->v[k], fprio->v[PAI(k)], fprio);
        sobe_no_heap(fprio, PAI(k));
    }
}

void inserir_na_fprio(p_fp fprio, p_sob sobrevivente) {
    /*
    INSERE UM ELEMENTO DA STRUCT SOBREVIVENTE NO VETOR DA FILA DE
    PRIORIDADE, COM A PROPRIEDADE DE QUE UM PAI SEMPRE TEM PRIORIDADE
    MAIOR QUE DE SEUS FILHOS
    */
   fprio->v[fprio->n] = sobrevivente;
   sobrevivente->id_heap = fprio->n;
   fprio->n++;
   sobe_no_heap(fprio, fprio->n - 1);
}

void insere_na_lista(p_sob* lista, p_sob sobrevivente, int id) {
    /*
    INSERE UM SOBREVIVENTE NA LISTA DE SOBREVIVENTES
    */
    lista[id] = sobrevivente;
}

#define F_ESQ(i) (2*i + 1)
#define F_DIR(i) (2*i + 2)

void desce_no_heap(p_fp fprio, int k) {
    /*
    UTILIZADA QUANDO UM SOBREVIVENTE TEM SUA PRIORIDADE DIMINUIDA,
    FAZENDO COM QUE SUA POSIÇÃO NO HEAP SEJA COLOCADA PARA DEPOIS
    */
    int maior_filho;
    if (F_ESQ(k) < fprio->n) {
        maior_filho = F_ESQ(k);
        if (F_DIR(k) < fprio->n && fprio->v[F_ESQ(k)]->prio_atual < fprio->v[F_DIR(k)]->prio_atual) {
                maior_filho = F_DIR(k);
        }
        if (fprio->v[k]->prio_atual < fprio->v[maior_filho]->prio_atual) {
            troca(fprio->v[k], fprio->v[maior_filho], fprio);
            desce_no_heap(fprio, maior_filho);
        }
    }
}

void printa_e_extrai_maximo(p_fp fprio) {
    /*
    IMPRIME O NOME, O SOBRENOME, O PEDIDO E A PRIORIDADE DO SOBREVIVENTE COM MAIOR
    PRIORIDADE NO HEAP, E DEPOIS O REMOVE DO HEAP
    */
    p_sob sobrevivente = fprio->v[0];
    printf("%s %s %s %d\n", sobrevivente->nome, sobrevivente->sobrenome, sobrevivente->pedido, sobrevivente->prio_atual);
    sobrevivente->prio_atual = sobrevivente->prio_original;
    troca(fprio->v[0], fprio->v[fprio->n - 1], fprio);
    fprio->n--;
    desce_no_heap(fprio, 0);
}

void libera_memoria(p_fp fprio, int n_sobreviventes, p_sob* lista) {
    /*
    LIBERA A MEMORIA ALOCADA PARA OS SOBREVIVENTES, PARA A LISTA DE SOBREVIVENTES E 
    PARA A FILA DE PRIORIDADE
    */
    for (int i = 0; i < n_sobreviventes; i ++) {
        free(lista[i]);
    }
    free(lista);
    free(fprio->v);
    free(fprio);
}
