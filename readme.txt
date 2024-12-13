1. Compilando o código
1. 1 No Windows
Abra o Prompt de Comando ou PowerShell.

Navegue até o diretório do projeto, caso não tenha feito isso anteriormente.

Compile o código usando o compilador gcc (caso tenha o MinGW ou outro compilador instalado):

gcc -o indexador indexador.c

1. 2 No Linux
Abra o Terminal.
Navegue até o diretório do projeto.
Compile o código usando o gcc:

gcc -o indexador indexador.c
Caso não tenha o GCC instalado, você pode instalá-lo executando:

Ubuntu/Debian:
sudo apt update
sudo apt install build-essential

Fedora:
sudo dnf groupinstall "Development Tools"

2. Rodando o Programa
No Windows e Linux: Depois de compilar o programa, você pode rodá-lo com o seguinte comando:

./indexador <arquivo> <tipo_indice>
<arquivo> é o nome do arquivo de texto a ser indexado.
<tipo_indice> //pode ser arvore para o tipo de índice binário ou lista para lista ligada.

Exemplo:
./indexador texto.txt arvore
Isso carregará o arquivo texto.txt, indexará as palavras e criará um índice utilizando uma árvore binária.
./indexador texto.txt arvore
Isso carregará o arquivo texto.txt, indexará as palavras e criará um índice utilizando uma lista ligada.

3. Interagindo com o programa
Após a execução do programa, você pode realizar as seguintes interações:

Busca por palavra: Digite o comando busca "palavra", onde "palavra" é a palavra que deseja procurar no arquivo. Exemplo de busca:
busca lorem
Finalizar o programa: Para encerrar o programa, digite o comando:

fim
