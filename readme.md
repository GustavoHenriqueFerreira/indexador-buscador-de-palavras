# Índice de Palavras com Árvores Binárias

Este projeto implementa um índice de palavras utilizando uma árvore binária. O programa permite carregar um arquivo de texto, construir um índice de palavras e realizar buscas no arquivo, mostrando as ocorrências das palavras nas linhas. O índice é estruturado como uma árvore binária de busca (BST).

## Requisitos

- Um compilador C (GCC, Clang, MSVC, etc.)
- Sistema operacional: Windows ou Linux
- Arquivo de texto a ser indexado

## Como Rodar o Projeto

### Passos para Windows e Linux

Siga os passos abaixo para rodar o projeto tanto em Windows quanto em Linux.

### 1. Clonando o Repositório

Clone o repositório para a sua máquina local:
```bash
git clone https://github.com/GustavoHenriqueFerreira/indexador-buscador-de-palavras
cd indexador-buscador-de-palavras
```

### 2. Compilando o Código

#### 2.1 No Windows:
Abra o Prompt de Comando ou PowerShell.
Navegue até o diretório do projeto, caso não tenha feito isso anteriormente.

Compile o código usando o compilador gcc (caso tenha o MinGW ou outro compilador instalado):
```bash
gcc -o indexador indexador.c
```

#### 2.2 No Linux:
Abra o Terminal.
Navegue até o diretório do projeto.

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
Copiar código
./indexador <arquivo> <tipo_indice>
```

Onde:
<arquivo> é o nome do arquivo de texto a ser indexado.
<tipo_indice> pode ser arvore para o tipo de índice binário.
Exemplo:

```bash
./indexador texto.txt arvore
```

Isso carregará o arquivo texto.txt, indexará as palavras e criará um índice utilizando uma árvore binária.

### 4. Interagindo com o Programa
Após a execução do programa, você pode realizar as seguintes interações:

Busca por palavra: Digite o comando busca <palavra>, onde <palavra> é a palavra que deseja procurar no arquivo.
Exemplo de busca:

```bash
busca palavra
```

Finalizar o programa: Para encerrar o programa, digite o comando:
```bash
fim
```

### 5. Estrutura do Código
O programa é estruturado da seguinte maneira:

indexador.c: O arquivo principal, onde a lógica de carregamento do arquivo, construção do índice e interação com o usuário é implementada.
Funções: O código usa funções para manipulação de palavras (remoção de pontuação, conversão para minúsculas), construção de árvores binárias e leitura do arquivo.
Arquivo de texto: O arquivo de texto é lido linha por linha, e cada palavra é indexada na árvore binária.

### 6. Exemplo de Saída
Após rodar o programa, o índice é construído e você pode realizar buscas para encontrar as palavras no arquivo. A saída pode ser algo como:

```yaml
Arquivo: 'texto.txt'
Tipo de índice: 'arvore'
Número de linhas no arquivo: 13
Total de palavras indexadas: 100
Altura da árvore: 5
Tempo de carga do arquivo e construção do índice: 15.30 ms

> busca palavra
Existem 3 ocorrências da palavra 'palavra' na(s) seguinte(s) linha(s):
0002: Esta é a linha que contém a palavra.
0045: Outra linha com a palavra mencionada.
0078: Palavra novamente encontrada aqui.

Tempo de busca: 0.15 ms

> fim
```

### 7. Considerações Finais
O programa é projetado para ser executado tanto no Windows quanto no Linux. A principal diferença é o uso do compilador e a forma como o sistema lida com quebras de linha (\r\n no Windows e \n no Linux).
O código pode ser facilmente modificado para adicionar mais funcionalidades, como suporte a mais tipos de índices ou melhorias na performance.