# Índice de Palavras com Árvores Binárias

Este projeto implementa um índice de palavras utilizando uma árvore binária. O programa permite carregar um arquivo de texto, construir um índice de palavras e realizar buscas no arquivo, mostrando as ocorrências das palavras nas linhas. O índice é estruturado como uma árvore binária de busca (BST).

## Requisitos

- Um compilador C (GCC, Clang, MSVC, etc.)
- Sistema operacional: Windows ou Linux
- Arquivo de texto a ser indexado

## Como Rodar o Projeto

### Passos para Windows e Linux

- Siga os passos abaixo para rodar o projeto tanto em Windows quanto em Linux.

### 1. Clonando o Repositório

- Clone o repositório para a sua máquina local:
```bash
git clone https://github.com/GustavoHenriqueFerreira/indexador-buscador-de-palavras
cd indexador-buscador-de-palavras
```

### 2. Compilando o Código

#### 2.1 No Windows:
- Abra o Prompt de Comando ou PowerShell.
- Navegue até o diretório do projeto, caso não tenha feito isso anteriormente.

- Compile o código usando o compilador gcc (caso tenha o MinGW ou outro compilador instalado):
```bash
gcc -o indexador indexador.c
```

#### 2.2 No Linux:
- Abra o Terminal.
- Navegue até o diretório do projeto.

Compile o código usando o gcc:
```bash
gcc -o indexador indexador.c
```

Caso não tenha o GCC instalado, você pode instalá-lo executando:

Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential
```

Fedora:
```bash
sudo dnf groupinstall "Development Tools"
```

### 3. Rodando o Programa
No Windows e Linux:
Depois de compilar o programa, você pode rodá-lo com o seguinte comando:

```bash
./indexador <arquivo> <tipo_indice>
```

```bash 
<arquivo> é o nome do arquivo de texto a ser indexado.
``` 

```bash 
<tipo_indice> //pode ser arvore para o tipo de índice binário ou lista para lista ligada.
``` 
Exemplo:

```bash
./indexador texto.txt arvore
```

Isso carregará o arquivo texto.txt, indexará as palavras e criará um índice utilizando uma árvore binária.

```bash
./indexador texto.txt lista
```

Isso carregará o arquivo texto.txt, indexará as palavras e criará um índice utilizando uma lista ligada.

### 4. Interagindo com o Programa
Após a execução do programa, você pode realizar as seguintes interações:

- Busca por palavra: Digite o comando busca "palavra", onde "palavra" é a palavra que deseja procurar no arquivo.
Exemplo de busca:

```bash
busca lorem
```

Finalizar o programa: Para encerrar o programa, digite o comando:
```bash
fim
```

### 5. Estrutura do Código
O programa é estruturado da seguinte maneira:

- indexador.c: O arquivo principal, onde a lógica de carregamento do arquivo, construção do índice e interação com o usuário é implementada.
- Funções: O código usa funções para manipulação de palavras (remoção de pontuação, conversão para minúsculas), construção de árvores binárias e leitura do arquivo.
- Arquivo de texto: O arquivo de texto é lido linha por linha, e cada palavra é indexada na árvore binária.

### 6. Exemplo de Saída
Após rodar o programa, o índice é construído e você pode realizar buscas para encontrar as palavras no arquivo. A saída pode ser algo como:

```yaml
Arquivo: 'texto.txt'
Tipo de indice: 'arvore'
Numero de linhas no arquivo: 13
Total de palavras indexadas: XXXXX
Altura da arvore: XXXXX
Tempo de carga do arquivo e construcao do indice: XXXXX ms
> busca algorithm
Existem 4 ocorrências da palavra 'algorithm' na(s) seguinte(s) linha(s):
00001: Informally, an algorithm is any well-defined computational procedure that takes
00003: as output. An algorithm is thus a sequence of computational steps that transform
00006: We can also view an algorithm as a tool for solving a well-specified computational
00008: input/output relationship. The algorithm describes a specific computational
Tempo de busca: XXXXX ms
> busca set
Existem 2 ocorrências da palavra 'set' na(s) seguinte(s) linha(s):
00002: some value, or set of values, as input and produces some value, or set of values,
Tempo de busca: XXXXX ms
> busca quicksort
Palavra 'quicksort' nao encontrada.
Tempo de busca: XXXXX ms
> buska quicksort
Opcao invalida!
> fim
```

### 7. Considerações Finais
O programa é projetado para ser executado tanto no Windows quanto no Linux. A principal diferença é o uso do compilador e a forma como o sistema lida com quebras de linha (\r\n no Windows e \n no Linux).
O código pode ser facilmente modificado para adicionar mais funcionalidades, como suporte a mais tipos de índices ou melhorias na performance.