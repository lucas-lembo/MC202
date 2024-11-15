#define MAX 201
enum cor {VERMELHO, PRETO};

typedef struct no* p_no;

struct no {
    enum cor cor;
    char nome[MAX];
    char tipo[7];
    p_no esq;
    p_no dir;
};

int eh_vermelho(p_no no);

int eh_preto(p_no no);

p_no rotaciona_esquerda(p_no raiz);

p_no rotaciona_direita(p_no raiz);

void sobe_vermelho(p_no raiz);

p_no cria_no (char linha[MAX]);

p_no adiciona_no(char linha[MAX], p_no raiz);

int ta_na_arvore(char simbolo[MAX], p_no raiz);

p_no acha_tipo(char simbolo[MAX], p_no raiz);

int verifica_erros(char linha[MAX], p_no raiz, int n, int erros);

void imprime_variaveis(p_no raiz);

void desaloca_arvore(p_no raiz);