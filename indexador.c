#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINHA 1024

// Função para remover pontuação e converter para minúsculas
void removerPontuacao(char *palavra) {
    int i = 0, j = 0;
    while (palavra[i]) {
        if (isalpha(palavra[i]) || isdigit(palavra[i])) {
            palavra[j++] = tolower(palavra[i]);
        }
        i++;
    }
    palavra[j] = '\0';
}

// Estrutura para o nó da árvore
typedef struct NoArvore {
    char palavra[MAX_LINHA];
    int *linhas;
    int numLinhas;
    int altura;
    struct NoArvore *esq;
    struct NoArvore *dir;
} NoArvore;

// Estrutura para o índice
typedef struct IndiceArvore {
    NoArvore *raiz;
    int totalPalavras;
    int numLinhas;
    char (*conteudoLinhas)[MAX_LINHA]; // Armazena o conteúdo de cada linha
} IndiceArvore;

// Funções auxiliares para árvore AVL
NoArvore *criarNoArvore(const char *palavra, int linha) {
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (!no) {
        fprintf(stderr, "Erro ao alocar memória para nó.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(no->palavra, palavra);
    no->linhas = (int *)malloc(sizeof(int));
    if (!no->linhas) {
        fprintf(stderr, "Erro ao alocar memória para linhas.\n");
        exit(EXIT_FAILURE);
    }
    no->linhas[0] = linha;
    no->numLinhas = 1;
    no->altura = 1;
    no->esq = no->dir = NULL;
    return no;
}

int altura(NoArvore *no) {
    return no ? no->altura : 0;
}

int fatorBalanceamento(NoArvore *no) {
    return no ? altura(no->esq) - altura(no->dir) : 0;
}

NoArvore *rotacionarDireita(NoArvore *y) {
    NoArvore *x = y->esq;
    NoArvore *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = 1 + (altura(y->esq) > altura(y->dir) ? altura(y->esq) : altura(y->dir));
    x->altura = 1 + (altura(x->esq) > altura(x->dir) ? altura(x->esq) : altura(x->dir));

    return x;
}

NoArvore *rotacionarEsquerda(NoArvore *x) {
    NoArvore *y = x->dir;
    NoArvore *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = 1 + (altura(x->esq) > altura(x->dir) ? altura(x->esq) : altura(x->dir));
    y->altura = 1 + (altura(y->esq) > altura(y->dir) ? altura(y->esq) : altura(y->dir));

    return y;
}

NoArvore *inserirNoArvore(NoArvore *raiz, const char *palavra, int linha) {
    if (raiz == NULL) return criarNoArvore(palavra, linha);

    if (strcmp(palavra, raiz->palavra) < 0) {
        raiz->esq = inserirNoArvore(raiz->esq, palavra, linha);
    } else if (strcmp(palavra, raiz->palavra) > 0) {
        raiz->dir = inserirNoArvore(raiz->dir, palavra, linha);
    } else {
        raiz->linhas = realloc(raiz->linhas, (raiz->numLinhas + 1) * sizeof(int));
        if (!raiz->linhas) {
            fprintf(stderr, "Erro ao realocar memória para linhas.\n");
            exit(EXIT_FAILURE);
        }
        raiz->linhas[raiz->numLinhas++] = linha;
    }

    raiz->altura = 1 + (altura(raiz->esq) > altura(raiz->dir) ? altura(raiz->esq) : altura(raiz->dir));

    int balance = fatorBalanceamento(raiz);

    // Realizar as rotações conforme necessário
    if (balance > 1 && strcmp(palavra, raiz->esq->palavra) < 0) return rotacionarDireita(raiz);
    if (balance < -1 && strcmp(palavra, raiz->dir->palavra) > 0) return rotacionarEsquerda(raiz);
    if (balance > 1 && strcmp(palavra, raiz->esq->palavra) > 0) {
        raiz->esq = rotacionarEsquerda(raiz->esq);
        return rotacionarDireita(raiz);
    }
    if (balance < -1 && strcmp(palavra, raiz->dir->palavra) < 0) {
        raiz->dir = rotacionarDireita(raiz->dir);
        return rotacionarEsquerda(raiz);
    }

    return raiz;
}

// Função para buscar e exibir palavras
void buscarPalavraArvore(NoArvore *raiz, const char *palavra, char (*conteudoLinhas)[MAX_LINHA]) {
    clock_t inicio = clock();

    if (raiz == NULL) {
        printf("Palavra '%s' nao encontrada.\n", palavra);
        printf("Tempo de busca: %.2f ms\n", (double)(clock() - inicio) / CLOCKS_PER_SEC * 1000);
        return;
    }
    if (strcmp(palavra, raiz->palavra) == 0) {
        printf("Existem %d ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", raiz->numLinhas, palavra);
        for (int i = 0; i < raiz->numLinhas; i++) {
            printf("%05d: %s", raiz->linhas[i], conteudoLinhas[raiz->linhas[i] - 1]);
        }
        printf("\n");
    } else if (strcmp(palavra, raiz->palavra) < 0) {
        buscarPalavraArvore(raiz->esq, palavra, conteudoLinhas);
    } else {
        buscarPalavraArvore(raiz->dir, palavra, conteudoLinhas);
    }
}

// Função para interpretar comandos
void interpretarComando(const char *comando, IndiceArvore *indice) {
    if (strncmp(comando, "busca ", 6) == 0) {
        char palavra[MAX_LINHA];
        strcpy(palavra, comando + 6);
        removerPontuacao(palavra);
        buscarPalavraArvore(indice->raiz, palavra, indice->conteudoLinhas);
    } else if (strcmp(comando, "fim") == 0) {
        exit(0);
    } else {
        printf("Opcao invalida!\n");
    }
}

// Código principal omitido para economizar espaço...
// Função para carregar o arquivo e construir o índice
void carregarArquivoEConstruirIndice(const char *nomeArquivo, IndiceArvore *indice) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    indice->conteudoLinhas = malloc(MAX_LINHA * sizeof(char[MAX_LINHA]));
    if (!indice->conteudoLinhas) {
        fprintf(stderr, "Erro ao alocar memória para conteúdo das linhas.\n");
        exit(EXIT_FAILURE);
    }
    
    char linha[MAX_LINHA];
    int numeroLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(indice->conteudoLinhas[numeroLinha], linha);
        numeroLinha++;
        indice->numLinhas++;
        char *token = strtok(linha, " ");
        while (token != NULL) {
            removerPontuacao(token);
            if (strlen(token) > 0) {
                indice->raiz = inserirNoArvore(indice->raiz, token, numeroLinha);
                indice->totalPalavras++;
            }
            token = strtok(NULL, " ");
        }
    }

    fclose(arquivo);
}

// Função principal
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <arquivo> <tipo de indice>\n", argv[0]);
        return 1;
    }

    const char *nomeArquivo = argv[1];
    const char *tipoIndice = argv[2];

    IndiceArvore *indice = (IndiceArvore *)malloc(sizeof(IndiceArvore));
    if (!indice) {
        fprintf(stderr, "Erro ao alocar memória para índice.\n");
        exit(EXIT_FAILURE);
    }
    indice->raiz = NULL;
    indice->totalPalavras = 0;
    indice->numLinhas = 0;

    clock_t inicio = clock();
    carregarArquivoEConstruirIndice(nomeArquivo, indice);
    clock_t fim = clock();
    double tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;

    printf("Arquivo: '%s'\n", nomeArquivo);
    printf("Tipo de indice: '%s'\n", tipoIndice);
    printf("Numero de linhas no arquivo: %d\n", indice->numLinhas);
    printf("Total de palavras indexadas: %d\n", indice->totalPalavras);
    if (strcmp(tipoIndice, "arvore") == 0) {
        printf("Altura da arvore: %d\n", altura(indice->raiz));
    }
    printf("Tempo de carga do arquivo e construcao do indice: %.2f ms\n", tempoExecucao);

    char comando[MAX_LINHA];
    while (1) {
        printf("> ");
        fgets(comando, sizeof(comando), stdin);
        comando[strcspn(comando, "\n")] = 0;

        interpretarComando(comando, indice);  
    }

    return 0;
}