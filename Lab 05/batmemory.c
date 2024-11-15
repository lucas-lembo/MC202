#include <stdio.h>
#include <stdlib.h>

typedef struct vetor *p_vetor;
 
struct vetor {
    int* dados;
    int* suporte;
    int n_utilizado;
    int n_alocado;
};

int nao_tem_espaco(p_vetor vetor, int n) {
    /*
    VERIFICA SE HÁ ESPAÇO NA MEMORIA PARA ARMAZENAR O VETOR
    SOLICITADO PELO USUÁRIO
    */
    int conta_zeros = 0;
    for (int i = 0; i < vetor->n_alocado; i++) {
        if (vetor->suporte[i] == 0) {
            conta_zeros += 1;
            if (conta_zeros == n + 1) {
                return 0;
            }
        } else {
            conta_zeros = 0;
            i += vetor->suporte[i];
        }
    }
    return 1;
}

void reduz_memoria(p_vetor vetor) {
    /*
    REDUZ O TAMANHO DA MEMORIA ALOCADA SE NAO HOUVER NENHUM ELEMENTO
    OCUPANDO O VETOR A PARTIR DO PRIMEIRO QUARTO DO VETOR ALOCADO
    */
    int *auxiliar_dados;
    int *auxiliar_suporte;
    auxiliar_dados = vetor->dados;
    auxiliar_suporte = vetor->suporte;
    vetor->n_alocado /= 2;
    vetor->dados = malloc(vetor->n_alocado * sizeof(int));
    vetor->suporte = calloc(vetor->n_alocado, sizeof(int));
    for (int i = 0; i < vetor->n_utilizado; i++) {
        vetor->dados[i] = auxiliar_dados[i];
        if (auxiliar_suporte != 0) {
            vetor->suporte[i] = auxiliar_suporte[i];
        }
    }
    free(auxiliar_dados);
    free(auxiliar_suporte);
}

void bat_free(p_vetor vetor) {
    /*
    LIBERA ESPAÇO DO VETOR DE ACORDO COM O ENDEREÇO SOLICITADO
    */
    int endereco;
    scanf("%d ", &endereco);
    vetor->n_utilizado -= (vetor->suporte[endereco] + 1);
    vetor->suporte[endereco] = 0;
    int desaloca = 1;
    for (int i = vetor->n_alocado / 4; i < vetor->n_alocado; i++) {
        if (vetor->suporte[i] != 0 || vetor->dados[i] != 0) {
            desaloca = 0;
            break;
        }
    }
    if (desaloca) {
        reduz_memoria(vetor);
    }
}

void dobra_memoria(p_vetor vetor) {
    /*
    DOBRA O TAMANHO DO VETOR ALOCADO QUANDO NÃO SE TEM ESPAÇO O 
    SUFICIENTE PARA ARMAZENR O VETOR SOLICITADO PELO USUARIO
    */
    int *auxiliar_dados;
    int *auxiliar_suporte;
    auxiliar_dados = vetor->dados;
    auxiliar_suporte = vetor->suporte;
    vetor->dados = calloc(vetor->n_alocado*2, sizeof(int));
    vetor->suporte = calloc(vetor->n_alocado*2, sizeof(int));
    for (int i = 0; i < vetor->n_alocado; i++) {
        vetor->dados[i] = auxiliar_dados[i];
        if (auxiliar_suporte[i] != 0) {
            vetor->suporte[i] = auxiliar_suporte[i];
        }
    }
    vetor->n_alocado *= 2;
    free(auxiliar_dados);
    free(auxiliar_suporte);
}

p_vetor cria_vetor() {
    /*
    RETORNA UM VETOR DO TIPO P_VETOR
    */
    p_vetor v = malloc(sizeof(struct vetor));
    v->n_alocado = 8;
    v->n_utilizado = 0;
    v->dados = malloc(8 * sizeof(int));
    v->suporte = calloc(8, sizeof(int));
    return v;
}

void bat_alloc(p_vetor vetor) {
    /*
    ALOCA UM VETOR SOLICITADO PELO USUÁRIO NA MEMÓRIA
    */
    int n;
    scanf("%d", &n);
    int* lista = malloc((n + 1) * sizeof(int));
    if (nao_tem_espaco(vetor, n)){
        dobra_memoria(vetor);
    }
    lista[0] = n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &lista[i]);
    
    }
    for (int i = 0; i < vetor->n_alocado; i++) {
        int alocavel = 1;
        for (int j = 0; j <= n; j++) {
            if (vetor->suporte[i + j] != 0) {
                alocavel = 0;
                i += j + vetor->suporte[i + j];
                break;
            }
        }
        if (alocavel) {
            vetor->suporte[i] = lista[0];
            vetor->n_utilizado += 1;
            for (int j = 1; j <= n; j++) {
                vetor->dados[i + j] = lista[j];
                vetor->n_utilizado += 1;
            }
            //vetor->n_utilizado += (n + 1);
            printf("%d\n", i);
            break;
        }
    }
    free(lista);
}

void bat_print(p_vetor vetor) {
    /*
    PRINTA O VETOR QUE DE ACORDO COM O ENDEREÇO SOLLICITADO PELO USUÁRIO
    */
    int endereco;
    scanf("%d", &endereco);
    int tamanho_lista = vetor->suporte[endereco];
    for (int i = 1; i <= tamanho_lista; i++) {

            printf("%d ", vetor->dados[endereco + i]);
        
    }
    printf("\n");
}

void bat_uso(p_vetor vetor) {
    /*
    INFORMA O QUANTO DA MEMÓRIA ESTÁ SENDO UTILIZADO
    */
    printf("%d de %d\n", vetor->n_utilizado, vetor->n_alocado);
}

void verifica_operacao(p_vetor vetor, char* operacao) {
    /*
    VERIFICA QUAL FUNCAO ESTÁ SENDO SOLICITADA PELO USUARIO
    */
    if (operacao[4] == 'a') {
        bat_alloc(vetor);
    }else if (operacao[4] == 'f') {
        bat_free(vetor);
    }else if(operacao[4] == 'p') {
        bat_print(vetor);
    }else{
        bat_uso(vetor);
    }
}

void destroi_vetor(p_vetor vetor) {
    free(vetor->dados);
    free(vetor->suporte);
    free(vetor);
}

int main() {
    p_vetor vetor = cria_vetor();
    int n_instrucoes;
    scanf("%d", &n_instrucoes);
    for (int i = 0; i < n_instrucoes; i++) {
        char operacao[10];
        scanf("%s ", operacao);
        verifica_operacao(vetor, operacao);
    }
    destroi_vetor(vetor);
    return 0;
}