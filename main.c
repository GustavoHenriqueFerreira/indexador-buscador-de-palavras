#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 
#include <ctype.h> 
#include <windows.h>

#define TAMANHO 1000

typedef struct {
	int numero_linha;
	char linha[TAMANHO];
}Ocorrencia;

typedef struct no_lista{
	char palavra[50];
	int totalOcorrencias;
	Ocorrencia* linhasOcorrencias;
	struct no_lista *proximo;
}No_Lista;

typedef struct{
	No_Lista* primeiro;
}Lista;

typedef struct no_arvore{
	char palavra[50];
	int totalOcorrencias;
	Ocorrencia* linhasOcorrencias;
	struct no_arvore *esquerda;
	struct no_arvore *direita;
}No_Arvore;

typedef struct{
	No_Arvore* raiz;
}Arvore;

Lista* cria_lista(){
	Lista* lista = (Lista*)malloc(sizeof(Lista));
	lista->primeiro = NULL;
	return lista;
}

Arvore* cria_arvore(){
	Arvore* arvore = (Arvore*)malloc(sizeof(Arvore));
	arvore->raiz = NULL;
	return arvore;
}

void inserir_indice_lista(Lista* lista, char* palavra, int linha, char* linha_completa) {
    No_Lista* aux = lista->primeiro;

    while (aux != NULL) {
        if (strcasecmp(aux->palavra, palavra) == 0) {
            aux->totalOcorrencias++;
            aux->linhasOcorrencias = (Ocorrencia*)realloc(aux->linhasOcorrencias, aux->totalOcorrencias * sizeof(Ocorrencia));

            aux->linhasOcorrencias[aux->totalOcorrencias - 1].numero_linha = linha;
            strcpy(aux->linhasOcorrencias[aux->totalOcorrencias - 1].linha, linha_completa);
            return;
        }
        aux = aux->proximo;
    }

    No_Lista* novo = (No_Lista*)malloc(sizeof(No_Lista));
    strcpy(novo->palavra, palavra);
    novo->totalOcorrencias = 1;
    novo->linhasOcorrencias = (Ocorrencia*)malloc(sizeof(Ocorrencia));
    novo->linhasOcorrencias[0].numero_linha = linha;
    strcpy(novo->linhasOcorrencias[0].linha, linha_completa);
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
}

No_Arvore* inserir_no_arvore(No_Arvore* raiz, char* palavra, int linha, char* linha_completa) {
    if (raiz == NULL) {
        No_Arvore* novo = (No_Arvore*)malloc(sizeof(No_Arvore));
        strcpy(novo->palavra, palavra);
        novo->totalOcorrencias = 1;
        novo->linhasOcorrencias = (Ocorrencia*)malloc(sizeof(Ocorrencia));
        novo->linhasOcorrencias[0].numero_linha = linha;
        strcpy(novo->linhasOcorrencias[0].linha, linha_completa);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }

    int comparacao = strcasecmp(raiz->palavra, palavra);

    if (comparacao == 0) {
        raiz->totalOcorrencias++;
        raiz->linhasOcorrencias = (Ocorrencia*)realloc(raiz->linhasOcorrencias, raiz->totalOcorrencias * sizeof(Ocorrencia));
        raiz->linhasOcorrencias[raiz->totalOcorrencias - 1].numero_linha = linha;
        strcpy(raiz->linhasOcorrencias[raiz->totalOcorrencias - 1].linha, linha_completa);
    } else if (comparacao < 0) {
        raiz->direita = inserir_no_arvore(raiz->direita, palavra, linha, linha_completa);
    } else {
        raiz->esquerda = inserir_no_arvore(raiz->esquerda, palavra, linha, linha_completa);
    }

    return raiz;
}

void inserir_indice_arvore(Arvore* arvore, char* palavra, int linha, char* linha_completa) {
    arvore->raiz = inserir_no_arvore(arvore->raiz, palavra, linha, linha_completa);
}

No_Lista* busca_indice_lista(Lista* lista, char* palavra){
	
	No_Lista* aux = lista->primeiro;
	while(aux!=NULL){ 
		if(strcasecmp(aux->palavra, palavra) == 0) return aux; 
		aux=aux->proximo;
	}
	return NULL;
}

No_Arvore* busca_indice_arvore(Arvore* arvore, char* palavra) {
    No_Arvore* aux = arvore->raiz;

    while (aux != NULL) {
        int comparacao = strcasecmp(palavra, aux->palavra);

        if (comparacao == 0) {
            return aux;
        } else if (comparacao < 0) {
            aux = aux->esquerda;
        } else {
            aux = aux->direita;
        }
    }

    return NULL;
}

void imprime_linhas_lista(Lista* lista, char* palavra) {
	char ultima_linha[TAMANHO]="";
    No_Lista* retorno = busca_indice_lista(lista, palavra);
    if (retorno) {
        int t = retorno->totalOcorrencias;
        int i;
        printf("Existe(m) %d ocorrência(s) da palavra '%s' na(s) seguinte(s) linha(s): \n", t, palavra);

        for (i = 0; i < t; i++) {
            if (strcasecmp(retorno->linhasOcorrencias[i].linha, ultima_linha) != 0) {
           		printf("%05d: %s", retorno->linhasOcorrencias[i].numero_linha + 1, retorno->linhasOcorrencias[i].linha);
				strcpy(ultima_linha, retorno->linhasOcorrencias[i].linha);
			}
        }
    } else {
        printf("Palavra '%s' nao encontrada.\n", palavra);
    }
}	

void imprime_linhas_arvore(Arvore* arvore, char* palavra){
	char ultima_linha[TAMANHO]="";
	No_Arvore* retorno = busca_indice_arvore(arvore, palavra);
	if(retorno){
		int t = retorno->totalOcorrencias;
		int i;
		printf("Existe(m) %d ocorrência(s) da palavra '%s' na(s) seguinte(s) linha(s): \n", t, palavra);
		for(i=0;i<t;i++){
           	if (strcasecmp(retorno->linhasOcorrencias[i].linha, ultima_linha) != 0) {
           		printf("%05d: %s", retorno->linhasOcorrencias[i].numero_linha + 1, retorno->linhasOcorrencias[i].linha);
				strcpy(ultima_linha, retorno->linhasOcorrencias[i].linha);
			}
		}
	}else{
		printf("Palavra '%s' nao encontrada.\n", palavra);
	}
}	

void liberar_ocorrencias(Ocorrencia* ocorrencias, int totalOcorrencias){
	free(ocorrencias);
}

void liberar_lista(No_Lista* no){
	if(no!=NULL){
		liberar_lista(no->proximo);
		liberar_ocorrencias(no->linhasOcorrencias, no->totalOcorrencias);
		free(no);
	}
}

void liberar_arvore(No_Arvore* raiz){
	if(raiz!=NULL){
		liberar_arvore(raiz->esquerda);
		liberar_arvore(raiz->direita);
		liberar_ocorrencias(raiz->linhasOcorrencias, raiz->totalOcorrencias);
		free(raiz);
	}
}

void removerPontuacao(char *str) {
    int i;
    for (i = 0; str[i]; i++) {
        if (ispunct(str[i]) || isdigit(str[i])) {
			str[i]=' ';
        }
    }
}

double mede_tempo(const clock_t* inicio, const clock_t* fim){
	return((double)(*fim - *inicio)*1000)/CLOCKS_PER_SEC;
}

int main(int argc, char ** argv){
	SetConsoleOutputCP(CP_UTF8);
	char delimitadores[] = "\t\n!#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ 0123456789";
	FILE * in;
	int contador_linha;
	char linha[TAMANHO];
	char comando[10];
	char palavra[50];
	char linha_copia[TAMANHO];	
	clock_t ini, fim;

	if(argc == 3) { 
		in = fopen(argv[1], "r");
		
		if(!in){
			printf("Erro ao abrir o arquivo %s\n", argv[1]);
			return 1;
    	}
		printf("Tipo de indice: '%s'\n",argv[2]);
		printf("Arquivo texto: '%s'\n",argv[1]);

		if(strcasecmp(argv[2],"lista")==0){
			Lista* lista = cria_lista();
			ini = clock();

			contador_linha = 0;
			
			while(fgets(linha,TAMANHO,in)!=NULL){ 
				strcpy(linha_copia,linha);	
				removerPontuacao(linha_copia);							
				char* token = strtok(linha_copia, delimitadores);
				while(token!=NULL){ 
					inserir_indice_lista(lista,token,contador_linha,linha); 
					token = strtok(NULL, delimitadores);
				}
				contador_linha++;
			}
			fim=clock();
			printf("Numero de linhas no arquivo: %d\n", contador_linha);
			printf("Tempo para carregar o arquivo e construir o indice: %.2f ms\n", mede_tempo(&ini, &fim));

			do{
				printf("> ");
				scanf("%s",comando);

				if(strcasecmp(comando, "busca")!=0 && strcasecmp(comando, "fim")!=0) 
					printf("Opcao invalida!\n");
				else if (strcasecmp(comando, "busca")==0) { 
					scanf(" %s",palavra);
					ini = clock();
					imprime_linhas_lista(lista, palavra);
					fim = clock();
					printf("Tempo de busca: %.2f ms\n", mede_tempo(&ini, &fim));
				}
				else if(strcasecmp(comando,"fim")==0){
					break;
				}
			}while(1);
			liberar_lista(lista->primeiro);

		}
		else if(strcasecmp(argv[2],"arvore")==0){
			Arvore* arvore = cria_arvore();
			ini = clock();

			contador_linha = 0;
			
			while(fgets(linha,TAMANHO,in)!=NULL){ 
				strcpy(linha_copia,linha);	
				removerPontuacao(linha_copia);							
				char* token = strtok(linha_copia, delimitadores);
				while(token!=NULL){ 
					inserir_indice_arvore(arvore,token,contador_linha,linha); 
					token = strtok(NULL, delimitadores);
				}
				contador_linha++;
			}
			fim=clock();
			printf("Numero de linhas no arquivo: %d\n", contador_linha);
			printf("Tempo para carregar o arquivo e construir o indice: %.2f ms\n", mede_tempo(&ini, &fim));

			do{
				printf("> ");
				scanf("%s",comando);

				if(strcasecmp(comando, "busca")!=0 && strcasecmp(comando, "fim")!=0) 
					printf("Opcao invalida!\n");
				else if (strcasecmp(comando, "busca")==0) { 
					scanf(" %s",palavra);
					ini = clock();
					imprime_linhas_arvore(arvore, palavra);
					fim = clock();
					printf("Tempo de busca: %.2f ms\n", mede_tempo(&ini, &fim));
				}
				else if(strcasecmp(comando,"fim")==0){
					break;
				}
			}while(1);
			liberar_arvore(arvore->raiz);

		}
	}
	fclose(in);
}
