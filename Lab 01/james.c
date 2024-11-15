#include <stdio.h>
#define MAX 10000

int contapix(int vetor[MAX], int tamanho_vetor, int busca) {
    int contagem = 0;
    for (int i = 0; i < tamanho_vetor; i++) {
            if (vetor[i] == busca) {
                contagem++;
            }
        }
        return contagem;
}

void contasequencia(int vetor[MAX], int seq_atual, int maior_seq, int pix_da_seq, int n, int retorno[2]) {
    for (int i = 1; i < n; i++) {
        if (vetor[i] == vetor[i - 1]) {
            seq_atual++;
            if (seq_atual > maior_seq) {
                maior_seq = seq_atual;
                pix_da_seq = vetor[i];
            }
        }
        else {
            seq_atual = 1;
        }
    }
    retorno[0] = maior_seq;
    retorno[1] = pix_da_seq;
}

int main() {
    int n;
    scanf("%d", &n);
    int listapix[MAX];
    for (int i = 0; i < n; i++) {
        scanf("%d ", &listapix[i]);
    }
    int pix5, pix7, pix10;
    pix5 = contapix(listapix, n, 5);
    pix7 = contapix(listapix, n, 7);
    pix10 = contapix(listapix, n, 10);
    printf("James vendeu %d saladas de 5 reais, %d de 7 reais e %d de 10 reais\n", pix5, pix7, pix10);
    int maior_seq = 1, seq_atual = 1, pix_da_seq = 0;
    int lista_contagem[2];
    contasequencia(listapix, seq_atual, maior_seq, pix_da_seq, n, lista_contagem);
    printf("James vendeu %d saladas de %d reais consecutivamente\n", lista_contagem[0], lista_contagem[1]);
    return 0;
}