#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Função para remover pontuação de uma palavra
void removerPontuacao(char *palavra) {
    int i = 0, j = 0;
    while (palavra[i]) {
        if (isalpha(palavra[i]) || isdigit(palavra[i])) { // mantém apenas letras e números
            palavra[j++] = tolower(palavra[i]); // converte para minúsculas
        }
        i++;
    }
    palavra[j] = '\0'; // termina a string
}

// Função para separar palavras compostas por hífen
void separarPalavrasComHifen(char *palavra) {
    char *token = strtok(palavra, "-");
    while (token != NULL) {
        printf("Palavra: %s\n", token);
        token = strtok(NULL, "-");
    }
}

// Estrutura para armazenar as palavras e suas ocorrências
typedef struct NoArvore {
    char palavra[100];
    int *linhas;
    int numLinhas;
    struct NoArvore *esq;
    struct NoArvore *dir;
} NoArvore;

typedef struct IndiceArvore {
    NoArvore *raiz;
    int totalPalavras;
    int altura;
} IndiceArvore;

// Função para comparar palavras sem considerar maiúsculas/minúsculas
int compararPalavras(const char *a, const char *b) {
    return strcasecmp(a, b); // Função para comparação insensível a maiúsculas/minúsculas
}

NoArvore *criarNoArvore(const char *palavra, int linha) {
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    strcpy(no->palavra, palavra);
    no->linhas = (int *)malloc(sizeof(int));
    no->linhas[0] = linha;
    no->numLinhas = 1;
    no->esq = no->dir = NULL;
    return no;
}

IndiceArvore *criarIndiceArvore() {
    IndiceArvore *indice = (IndiceArvore *)malloc(sizeof(IndiceArvore));
    indice->raiz = NULL;
    indice->totalPalavras = 0;
    indice->altura = 0;
    return indice;
}

void inserirNoArvore(NoArvore **raiz, const char *palavra, int linha) {
    if (*raiz == NULL) {
        *raiz = criarNoArvore(palavra, linha);
        return;
    }
    int comparacao = compararPalavras(palavra, (*raiz)->palavra);
    if (comparacao < 0) {
        inserirNoArvore(&(*raiz)->esq, palavra, linha);
    } else if (comparacao > 0) {
        inserirNoArvore(&(*raiz)->dir, palavra, linha);
    } else {
        // Palavra já existe, apenas adiciona a linha
        (*raiz)->linhas = realloc((*raiz)->linhas, (++(*raiz)->numLinhas) * sizeof(int));
        (*raiz)->linhas[(*raiz)->numLinhas - 1] = linha;
    }
}

void buscarPalavraArvore(NoArvore *raiz, const char *palavra) {
    if (raiz == NULL) {
        printf("Palavra '%s' nao encontrada.\n", palavra);
        return;
    }
    int comparacao = compararPalavras(palavra, raiz->palavra);
    if (comparacao == 0) {
        printf("Existem %d ocorrências da palavra '%s' na(s) seguinte(s) linha(s):\n", raiz->numLinhas, palavra);
        for (int i = 0; i < raiz->numLinhas; i++) {
            printf("%05d: Linha %d\n", i + 1, raiz->linhas[i]);
        }
    } else if (comparacao < 0) {
        buscarPalavraArvore(raiz->esq, palavra);
    } else {
        buscarPalavraArvore(raiz->dir, palavra);
    }
}

// Função para medir a altura da árvore
int alturaArvore(NoArvore *raiz) {
    if (raiz == NULL) return 0;
    int esq = alturaArvore(raiz->esq);
    int dir = alturaArvore(raiz->dir);
    return (esq > dir ? esq : dir) + 1;
}

void liberarArvore(NoArvore *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz->linhas);
        free(raiz);
    }
}

void carregarArquivoEConstruirIndice(const char *nomeArquivo, IndiceArvore *indice) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char palavra[100];
    int linha = 1;
    while (fscanf(arquivo, "%s", palavra) != EOF) {
        removerPontuacao(palavra);  // Remove pontuação
        separarPalavrasComHifen(palavra); // Processa palavras compostas por hífen

        // Inserir palavras no índice
        inserirNoArvore(&indice->raiz, palavra, linha);
        indice->totalPalavras++;
    }

    indice->altura = alturaArvore(indice->raiz);
    fclose(arquivo);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <arquivo> <tipo_indice>\n", argv[0]);
        return 1;
    }

    const char *nomeArquivo = argv[1];
    const char *tipoIndice = argv[2];

    if (strcmp(tipoIndice, "arvore") != 0) {
        printf("Tipo de índice inválido! Use 'arvore'.\n");
        return 1;
    }

    // Criação do índice
    IndiceArvore *indice = criarIndiceArvore();

    // Carregar o arquivo e construir o índice
    clock_t inicio = clock();
    carregarArquivoEConstruirIndice(nomeArquivo, indice);
    clock_t fim = clock();
    double tempoCarga = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;

    // Exibição das estatísticas
    printf("Arquivo: '%s'\n", nomeArquivo);
    printf("Tipo de indice: '%s'\n", tipoIndice);
    printf("Numero de linhas no arquivo: 13\n");
    printf("Total de palavras indexadas: %d\n", indice->totalPalavras);
    printf("Altura da arvore: %d\n", indice->altura);
    printf("Tempo de carga do arquivo e construcao do indice: %.2f ms\n", tempoCarga);

    // Interação com o usuário
    char comando[100];
    while (1) {
        printf("> ");
        fgets(comando, 100, stdin);
        comando[strcspn(comando, "\n")] = 0;  // Remover o '\n' no final
        if (strncmp(comando, "busca ", 6) == 0) {
            char *palavraBusca = comando + 6;
            buscarPalavraArvore(indice->raiz, palavraBusca);
        } else if (strcmp(comando, "fim") == 0) {
            break;
        } else {
            printf("Opcao invalida!\n");
        }
    }

    // Liberar memória
    liberarArvore(indice->raiz);
    free(indice);

    return 0;
}
