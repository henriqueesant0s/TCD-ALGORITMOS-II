#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h> 

void carregar_arquivos(int **dados, int *tam) { //Função que lê números de cada arquivo e cria um vetor dinâmico

    char arquivo[200]; // Vetor char para armazenar o nome do arquivo.
    FILE *arq; // Ponteiro para manipular o arquivo.
    int total = 0; // Variavel de para contar quantos numeros existem no arquivo.
    int valor; // Variavel auxiliar para leitura temporaria.

    printf("Informe o nome do arquivo: ");
    scanf("%199s", arquivo); // Lê o nome digitado (limitado a 199 caracter).

    arq = fopen(arquivo, "r"); // Abre o arquivo em modo leitura.
    if (arq == NULL) { // Verifica se houve erro ao abrir
        printf("Nao foi possivel abrir o arquivo.\n"); 
        *tam = 0; // Define tamanho como 0.
        return; // Encerra a função.
    }

    
    while (fscanf(arq, "%d", &valor) != EOF) {  // Lê números até o fim do arquivo.
        total++; // Conta quantos números foram encontrados.
    }

    if (total == 0) { // Se não houver números no arquivo.
        printf("Arquivo vazio ou sem numeros validos.\n");
        fclose(arq); // Fecha o arquivo.
        *tam = 0; // Define tamanho como 0.
        return;
    }

    rewind(arq);  // volta para o início do arquivo

    *dados = malloc(total * sizeof(int)); // Aloca memória suficiente para todos os números.
    if (*dados == NULL) { //  Verifica se a alocação deu erro.
        printf("Erro ao alocar memoria.\n");
        fclose(arq); // Fecha arquivo.
        *tam = 0; // Define tamanho como 0.
        return;
    }

    int pos = 0; // Variável para percorrer o vetor.
    while (pos < total && fscanf(arq, "%d", &(*dados)[pos]) == 1) { // Lê novamente os números.
        pos++; // Avança para a próxima posição do vetor.
    }

    fclose(arq); // Fechar o arquivo após terminar a leitura.

    *tam = total; // Atualiza o tamanho real do vetor.

    printf("%d valores foram lidos do arquivo %s.\n", *tam, arquivo); // Monstra quantos numeros foram carregados.
}

int busca_linear(int vetor[], int tam, int alvo ) // "vetor[]" = onde sera feito a busca, "tam" = tamanho do vetor, "alvo" = valor que queremos encontrar.
{

    for(int i = 0; i < tam; i++) { // Percorre o vetor de indice 0 até o ultimo elemento.
        if(vetor[i] == alvo){ // Verifica se o valor da posição atual do vetor é igual ao valor procurado.
            return i; // Retorna o\ índice i na memsa hora que encerra a função.
        }
    }

    return -1; // Return -1 indicando que o elemento não esta no vetor.
}

int busca_binaria(int a[], int n, int chave) { // "a[]" = vetor onde será feito a busca, "n" = tamanho do vetor, "chave" = valor que queremos encontrar.
    int inicio = 0; // Define o início do vetor da primeira posição.
    int fim = n - 1; // Define o final do vetor da ultima posição.

    while(inicio <= fim) { // Enquanto o início não ultrapassar o final do vetor.
        int meio = inicio + (fim - inicio) / 2; // Calcula a posição do meio do vetor e evita possiveis problemas de overflow.

        if (a[meio] == chave) { // Verifica se o valor do meio é igual á chave procurada.
            return meio; // Se encontrou, retorna o índice onde está.
        
        } else if(a[meio] < chave) { // Se o valor do meio for menor que a chave.
            inicio = meio + 1; // Continua a busca na metade direita
        
        } else { // Caso contrario, a busca continua na metade direita do vetor.
            fim = meio -1; 
        }
    }
    return -1; // Se o laço terminar e não encontrar a chave, retorna -1
}

void insertSort(int *vet,int n)
{
    int i, j, chave;

    for(i = 1; i < n; i++)
    {
        chave = vet[i];//elemento atual
        j = i - 1;
        
        while(j >= 0 && vet[j]>chave)//move os maiores que a chave
        {
            vet[j + 1] = vet[j];  // desloca
            j--;
        }
        vet[j+1] = chave;//insere na posição correta
    }
}

void troca (int *vet, int i, int j)//inverte duas posições do vetor
{
    int temp = vet[i]; 
    vet[i] = vet[j];
    vet[j] = temp;
}

void bubbleSort(int *vet,int n)
{
    int trocou;

    for(int i = 0; i < n - 1; i++)//nova leitura do vetor
    {
        trocou = 0;

        for(int j = 0; j<(n - 1 - i); j++)//comparação de elementos
        {
            if(vet[j] > vet[j+1]) //Se o elemento atual for maior que o proximo
            {
                troca(vet , j , j+1); //Troca os valores
                trocou = 1;
            }
        }
        if(!trocou)//evita comparações se o vetor já está ordenado
        {
            break;
        }
    }
}

void selectionSort(int *vet, int n)
{
    int i, j, min;

    for(i = 0; i < n-1; i++) // Laço de repetiçao para percorrer o vetor
    {
        min = i; //Encontrar o menor elemento na parte nao ordenada

        for(j = i+1; j < n; j++) //Proccura o menor elemento restante do vetor
        {
            if(vet[j] < vet[min])
            {
                min = j; //Atualiza a posiçao do menor elemento do vetor
            }
        }
        if(min != i)
        {
            troca(vet , min, i); //Troca o menor elemento com a posiçao atual
        }
    }

}

void mergeSort(int vet[], int esquerda, int direita)
{
    int meio;

    if(esquerda < direita)
    {
        meio = (esquerda + direita) /2; //Calcular o meio do vetor
         
        mergeSort(vet, esquerda, meio);//Ordena a primeira metade do vetor
         
        mergeSort(vet, meio + 1, direita);//Ordena a segunda metade do vetor

        merge(vet, esquerda, meio, direita);//Junta as duas metades ordenadas
    }
}

//Funçao para juntar 2 partes ja ordenadas do vetor
void merge(int vet[], int esquerda, int meio, int direita)
{
    int i, j, k; //Variaveis para percorrer o vetor
    int n1, n2;

    n1 = meio - esquerda + 1; //Tamanho da primeira metade
    n2 = direita - meio; //Tamanho da segunda metade

    int *E = (int*) malloc(n1 * sizeof(int)); //Separar memoria para o vetor temporario E
    int *D = (int*) malloc(n2 * sizeof(int)); //Separar memoria para o vetor temporario D

    if(E == NULL || D == NULL) {
        printf("Erro de memoria\n");
        return;
    }

    for(i = 0; i < n1; i++) //Copia os elementos da primeira metade do vetor para o vetor temporario E = Esquerda 
    {
        E[i] = vet[esquerda + i];
    }
    for(j = 0; j < n2; j++)
    {
        D[j] = vet[meio + 1 + j]; //Copia os elementos da segunda metade do vetor para o vetor temporario D = Direita
    }
    i = 0; //Reinicia o indice do vetor E
    j = 0; //Reinicia o indice do vetor D
    k = esquerda; //Indice inicial para reorganizar o vetor original

    while (i < n1 && j < n2) //Compara os elementos de E e D e coloca o menor no vetor original
    {
        if (E[i] <= D[j]) //Se o elemento de E for menor ou igual coloca ele no vetor original
        {
            vet[k] = E[i];
            i++; //Avança o vetor E
        }else{
            vet[k] = D[j]; //Caso contrario, coloca o elemento de D
            j++; //Avança no vetor D
        }

        k++;
    }

    while (i < n1)//Copia os elementos restantes de E se ainda houver
    {
        vet[k] = E[i];
        i++;
        k++;
    }

    while (j < n2)//Copia os elementos restantes de D se ainda houver
    {
        vet[k] = D[j];
        j++;
        k++;
    }

     // Libera memória
    free(E);
    free(D);
    
}

//Recebe os endereços de 2 variaveis
void trocar(int *i, int *j)
{
    int temp;

    temp = *i;//Guarda o valor de a temporariamente
    *i = *j;//Coloca o valor de a em b
    *j = temp;//Coloca o valor guardado do antigo a em b
}

void quickSort(int vet[], int menor, int maior)
{
    int pivo;
    
    //p recebe posiçao onde o pivo foi colocado
    if(menor < maior){
        
        pivo = particao(vet, menor, maior);

        quickSort(vet, menor, pivo - 1);//Ordena os elemenetos antes do pivo

        quickSort(vet, pivo + 1, maior);//Ordena os elementos depois do pivo
    }
}

//Funçao que organiza os elementos em torno de um pivo
int particao(int vet[], int menor, int maior)
{
    int i, j, pivo;

    pivo = vet[maior];//Escolhe o ultimo do elemento do vetor como pivo
    i = (menor - 1);//Indice do menor elemento, começa antes do inicio 

    for( j = menor; j <= maior - 1; j++)
    {
        if(vet[j] <= pivo)//Se o elemento atual for menor ou igual ao pivo move o indice
        {
            i = i + 1;
        }
    }

    trocar(&vet[i + 1], &vet[maior]);//Coloca o pivo na posiçao correta do vetor
    

    return (i + 1);//Retorna a posiçao final do pivo
}

void tonico(int *vet, int menor, int maior) 
{ 
    
    int i, j, pivo, temp, chave; // variaveis auxiliares do algoritmo.

    if(menor - maior + 1 < 20)//Cai no Bubble Sort
    {
        for(i = menor + 1; i <= maior; i++)
        {
            chave = vet[i]; //elemento atual
            
            j = i - 1; //comprar a chave com os elementos a esquerda
        
            while(j >= menor && vet[j]>chave) //move os maiores que a chave
            {
                vet[j + 1] = vet[j];  //desloca a posição para a direita
               
                j--; //verifica os elementos anteriores
            }
            
            vet[j + 1] = chave;//insere na posição correta
       
        }
    }

    if (menor >= maior) // condição de parada de recursão.
    {
        return; //Vetor com 0 ou 1 elemento ja esta ordenado   
    }

    i = menor - 1;//Inicializa o i antes do subvetor
    j = maior + 1;//Inicializa o j depois do final do subvetor
    
    pivo = vet[(menor + maior) / 2]; //Escolhe o pivo como meio do subvetor

    while (1) // loop de particionamento.
    {
        do { 
            i++; // avança da esqueda para direita.
        } 
        while (vet[i] < pivo); //Move o i para a direita ate encontrar um elemento >= pivo
        do { 
            j--; // avaça da direita para esquerda
        } 
        while (vet[j] > pivo); //Move o j para a esquerda ate encontra um elemento <= pivo
       
        if (i >= j) //se i e j se encontrarem, a partiçao vai estar completa, sendo assim saira do loop
        
        break;
        
        //Troca vet[i] e vet[j] para colocar no lado certo do pivo
        troca(vet , i, j);

    }

    tonico(vet, menor, j); //Ordenar o vetor da Esquerda no caso o menor
    tonico(vet, j + 1, maior); //Ordenar o vetor da Direita no caso o maior
}

//GERAR RELATORIO ==================================================================================
void gerarlog(int *dados, int tam, int alvo)
{
    //DECLARANDO    
        //DO TEMPO
            LARGE_INTEGER frequency;//variavel para armazenar a frequencia do contador de alta resolução
            LARGE_INTEGER inicioBubble, fimBubble, inicioInsertion, fimInsertion, inicioSelection, fimSelection;//variaveis para armazenar o tempo de inicio e fim de cada algoritmo
            LARGE_INTEGER inicioMerge, fimMerge, inicioQuick, fimQuick, inicioBin,fimBin,inicioLin,fimLin, inicioTonico, fimTonico;//variaveis para armazenar o tempo de inicio e fim de cada algoritmo
            QueryPerformanceFrequency(&frequency);//função para obter a frequencia do contador de alta resolução
        FILE *log;  //ponteiro para arquivo
        char logName[15] = "log.txt";   //vetor para lidar com o nome do arquivo
        double mBubble=0, mQuick=0, mInsertion=0, mSelection=0, mMerge=0, mExtra=0,mBin=0, mLin=0, mTonico=0;//variaveis para cada media do algoritmos
        int *copia = malloc(tam*sizeof(int));//alocação dinâmica do vetor copia
            if(copia == NULL) {//verificação de erro na alocação
                printf("Erro ao alocar memoria\n");//mensagem de erro
                return;//encerra a função se a alocação falhar
            }

    //ABRINDO
        log = fopen((logName),"w");//função que abre o arquivo para escrever

        //VERIFICANDO
            if(log==NULL)//verificação de erro ao abrir o arquivo
            {
                printf("Escrita de arquivo falhou\n");//mensagem de erro
                return;//encerra a função se o arquivo não for aberto
            }
    //MEDINDO 
    //BUSCA LINEAR
        for (int i = 0; i < 100; i++)//realiza 100 execuções para obter uma média precisa
        {
            memcpy(copia, dados, tam*sizeof(int));//cria copia do vetor: memcpy(destino, origem, tamanho_em_bytes)
            
            QueryPerformanceCounter(&inicioLin);//inicio da contagem de tempo 
            busca_linear(copia, tam, alvo);//chama a função de busca linear
            QueryPerformanceCounter(&fimLin);//fim da contagem de tempo
            mLin += (fimLin.QuadPart - inicioLin.QuadPart);//a variavel de média acumula a contagem de tempo a cada execução
        }
        mLin = ((mLin) * 1000.0 / frequency.QuadPart)/100;//mede o tempo total e converte para milissegundos, depois divide por 100 para obter a média de tempo

    //BUSCA BINARIA
        for (int i = 0; i < 100; i++)//realiza 100 execuções para obter uma média precisa
        {
            memcpy(copia, dados, tam    *sizeof(int));//cria copia do vetor           
            quickSort(copia, 0, tam - 1);//chama uma função de ordenação, para que a busca binária funcione corretamente
            QueryPerformanceCounter(&inicioBin);//inicio da contagem de tempo
            busca_binaria(copia, tam, alvo);//chama a função de busca binária
            QueryPerformanceCounter(&fimBin);//fim da contagem de tempo
            mBin += (fimBin.QuadPart - inicioBin.QuadPart);//a variavel de média acumula a contagem de tempo a cada execução
        }
        mBin =((mBin) * 1000.0 / frequency.QuadPart)/100;//mede o tempo total e converte para milissegundos, depois divide por 100 para obter a média de tempo

    //BUBBLE SORT
        for (int i = 0; i < 100; i++)//realiza 100 execuções para obter uma média precisa
        {
            memcpy(copia, dados, tam    *sizeof(int));//cria copia do vetor
            QueryPerformanceCounter(&inicioBubble);//inicio da contagem de tempo
            bubbleSort(copia, tam);//chama a função de bubble sort
            QueryPerformanceCounter(&fimBubble);//fim da contagem de tempo
            mBubble += (fimBubble.QuadPart - inicioBubble.QuadPart);//a variavel de média acumula a contagem de tempo a cada execução
        }
        mBubble=((mBubble) * 1000.0 / frequency.QuadPart)/100;//mede o tempo total e converte para milissegundos, depois divide por 100 para obter a média de tempo

    //INSERT SORT
        for (int i = 0; i < 100; i++)//realiza 100 execuções para obter uma média precisa
        {
            memcpy(copia, dados, tam    *sizeof(int));//cria copia do vetor
            QueryPerformanceCounter(&inicioInsertion);//inicio da contagem de tempo
            insertSort(copia, tam);//chama a função de insertion sort
            QueryPerformanceCounter(&fimInsertion);//fim da contagem de tempo
            mInsertion += (fimInsertion.QuadPart - inicioInsertion.QuadPart);//a variavel de média acumula a contagem de tempo a cada execução
        }
        mInsertion=((mInsertion) * 1000.0 / frequency.QuadPart)/100;//mede o tempo total e converte para milissegundos, depois divide por 100 para obter a média de tempo

    //SELECTION SORT
        for (int i = 0; i < 100; i++)//realiza 100 execuções para obter uma média precisa
        {
            memcpy(copia, dados, tam    *sizeof(int));//cria copia do vetor
            QueryPerformanceCounter(&inicioSelection);//inicio da contagem de tempo
            selectionSort(copia, tam);//chama a função de selection sort
            QueryPerformanceCounter(&fimSelection);//fim da contagem de tempo
            mSelection += (fimSelection.QuadPart - inicioSelection.QuadPart);//a variavel de média acumula a contagem de tempo a cada execução
        }
        mSelection=((mSelection) * 1000.0 / frequency.QuadPart)/100;//mede o tempo total e converte para milissegundos, depois divide por 100 para obter a média de tempo

    //MERGE SORT
        for (int i = 0; i < 100; i++)//realiza 100 execuções para obter uma média precisa
        {
            memcpy(copia, dados, tam    *sizeof(int));//cria copia do vetor
            QueryPerformanceCounter(&inicioMerge);//inicio da contagem de tempo
            mergeSort(copia, 0, tam-1);//chama a função de merge sort
            QueryPerformanceCounter(&fimMerge);//fim da contagem de tempo
            mMerge += (fimMerge.QuadPart - inicioMerge.QuadPart);//a variavel de média acumula a contagem de tempo a cada execução
        }
        mMerge=((mMerge) * 1000.0 / frequency.QuadPart)/100;//mede o tempo total e converte para milissegundos, depois divide por 100 para obter a média de tempo

    //QUICK SORT
        for (int i = 0; i < 100; i++)//realiza 100 execuções para obter uma média precisa
        {
            memcpy(copia, dados, tam    *sizeof(int));//cria copia do vetor
            QueryPerformanceCounter(&inicioQuick);//inicio da contagem de tempo
            quickSort(copia, 0, tam -1);//chama a função de quick sort
            QueryPerformanceCounter(&fimQuick);//fim da contagem de tempo
            mQuick += (fimQuick.QuadPart - inicioQuick.QuadPart);//a variavel de média acumula a contagem de tempo a cada execução
        }
        mQuick=((mQuick) * 1000.0 / frequency.QuadPart)/100;//mede o tempo total e converte para milissegundos, depois divide por 100 para obter a média de tempo

     //TONICO SORT
        for (int i = 0; i < 100; i++)//
        {
            memcpy(copia, dados, tam    *sizeof(int));//cria copia do vetor
            QueryPerformanceCounter(&inicioTonico);//inicio da contagem de tempo
            tonico(copia, 0, tam -1);//chama a função de ordenção Tonico
            QueryPerformanceCounter(&fimTonico);//fim da contagem de tempo
            mTonico += (fimTonico.QuadPart - inicioTonico.QuadPart);//a variavel de média acumula a contagem de tempo a cada execução
        }
        mTonico=((mQuick) * 1000.0 / frequency.QuadPart)/100;//mede o tempo total e converte para milissegundos, depois divide por 100 para obter a média de tempo

    //EXTRA
    
    // ESCREVENDO
        //Escreve no arquivo aberto os resultados das médias de medição de tempo com 9 casas de precisão,
        //Usando a variáveis de média de cada um
        fprintf(log, "\n");
        fprintf(log, "== TEMPO DAS BUSCAS EM MILISSEGUNDOS ==\n");
        fprintf(log, "=======================================\n");
        fprintf(log," Busca Linear: %.9f ms\n", mLin);
        fprintf(log," Busca Binaria: %.9f ms\n\n", mBin);
        fprintf(log,"== TEMPO DAS ORDENACOES EM MILISSEGUNDOS ==\n");
        fprintf(log,"===========================================\n");
        fprintf(log," Bubble Sort: %.9f ms\n", mBubble);
        fprintf(log," Insertion Sort: %.9f ms\n", mInsertion);
        fprintf(log," Selection Sort: %.9f ms\n", mSelection);
        fprintf(log," Merge Sort: %.9f ms\n", mMerge);
        fprintf(log," Quick Sort: %.9f ms\n", mQuick);
        fprintf(log," Tonico(EXTRA): %.9f ms\n", mTonico);
        
        //Justificativa do uso do algoritmo extra
       //Justificativa do uso do algoritmo extra 
        fprintf(log, "\nJustificativa do algoritmo extra:\n");
        fprintf(log, "Nosso algoritmo foi nomeado tendo como inspiração o nome da\n");
        fprintf(log, "dupla sertaneja Tonico e Tinoco em referencia ao nosso professor Tinoco.\n");
        fprintf(log, "O algoritmo que decidimos usar foi baseado principalmente no Particionamento Hoare\n");
        fprintf(log, "para o Quick Sort, apresentado por Charles Antony Richard Hoare\n");
        fprintf(log, "na década de 60. Essa variacao usa algumas melhorias conhecidas,\n");
        fprintf(log, "como a particao de Hoare, que faz menos trocas; sendo uma forma de economizar memória\n");
        fprintf(log, "e processamento, otimizando assim o algoritmo.\n");
        fprintf(log, "Além disso, utilizamos tambem o Insertion Sort para auxiliar em partes menores\n");
        fprintf(log, "do conjunto de dados, pois ele possui uma implementacao simples e eficiente\n");
        fprintf(log, "quando aplicado a pequenos conjuntos de elementos ou dados quase ordenados.\n");
        fprintf(log, "Dessa forma, a combinacao entre Quick Sort e Insertion Sort permite\n");
        fprintf(log, "aproveitar as vantagens de cada algoritmo, onde o Quick Sort apresenta\n");
        fprintf(log, "alto desempenho em grandes conjuntos de dados, enquanto o Insertion Sort\n");
        fprintf(log, "atua de forma rapida em subconjuntos menores.\n");
        fprintf(log, "O Quick Sort possui custo medio de O(n log n) e pior caso de O(n^2),\n");
        fprintf(log, "sendo amplamente utilizado por sua eficiencia pratica e baixo uso de memoria.\n");

    // FECHANDO
            fclose(log);//fecha o arquivo de log que foi aberto
            free(copia);//limpa da memória do vetor de copia
    
            return;//encerra a função
}