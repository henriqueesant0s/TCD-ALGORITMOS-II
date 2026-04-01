//  ██████╗ ██████╗ ██████╗ ███████╗
// ██╔════╝██╔═══██╗██╔══██╗██╔════╝
// ██║     ██║   ██║██║  ██║█████╗
// ██║     ██║   ██║██║  ██║██╔══╝
// ╚██████╗╚██████╔╝██████╔╝███████╗
//  ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
void gravarDados(const char *arquivo, int *vetor, int quantidade) {
    FILE *fp; // Ponteiro para o arquivo
    int indice = 0; // Variável usada para percorrer o vetor

    fp = fopen(arquivo, "w"); // Abre o arquivo no modo escrita

    if (fp == NULL) { // Verifsica se houve erro ao abrir o arquivo
        printf("Erro ao criar o arquivo.\n");
        return; // Encerra a função
    }

    while (indice < quantidade) { // Percorre o vetor
        fprintf(fp, "%d\n", vetor[indice]); // Escreve o número no arquivo
        indice++; // Próxima posição
    }

    fclose(fp); // Fecha o arquivo
    printf("Dados gravados com sucesso no arquivo %s.\n", arquivo);
}

int main(void) {

 //DO TEMPO
        LARGE_INTEGER frequency;
        LARGE_INTEGER inicioBubble, fimBubble, inicioInsertion, fimInsertion, inicioSelection, fimSelection, inicioTonico, fimTonico;
        LARGE_INTEGER inicioMerge, fimMerge, inicioQuick, fimQuick, inicioBin,fimBin,inicioLin,fimLin, inicioExtra, fimExtra;
        QueryPerformanceFrequency(&frequency);
        
    printf("===========================================================\n");
    printf("=               TCD - ALGORITMOS II                       =\n");
    printf("=  Henrique E. | Carlos E. | Heitor V. | Vinicius R.      =\n");
    printf("===========================================================\n");

    int *dados = NULL; // vetor que guarda os dados do arquivo
    int tam = 0; // tamanho do vetor
    int arquivo_carregado = 0; // variavel para verificar se o arquivo foi carregado ou nao
    int executado = 0; //verifica se o arquivo foi ordenado ou se teve busca
    int ordenado = 0;
    int alvo=0; // numero que procura na busca
    int busca=0; //verifica se a achou algum numero na busca e caso ache guarda a posição que achou
    int salvar = 0; // salvar arquivo ordenado
    int opcao, opcao_busca, opcao_ordenacao; //menus para os switchs

    do {
        printf("====================================================================\n");
        printf("                          MENU PRINCIPAL                            \n");
        printf("====================================================================\n");
        printf("1. Carregar arquivo de dados\n");
        printf("2. Buscar elemento (linear ou binaria)\n");
        printf("3. Ordenar dados (Insert, Bubble, Selection, Merge, Quick, EXTRA)\n");
        printf("4. Gerar relatorio (Log)\n");
        printf("5. Sair\n");
        printf("====================================================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1: // carregar arquivo
                carregar_arquivos(&dados, &tam); //carrega um arquivo
                arquivo_carregado = 1; //afirma que o arquivo foi carregado
                break;

            case 2: // buscar elemento
                if (arquivo_carregado == 0) { //verifica se foi carregado algum arquivo
                    printf("Carregue um arquivo antes de continuar..\n"); 
                    break; 
                }
                printf("\n-- BUSCA DE ELEMENTO --\n");
                printf("1 - Busca Linear\n");
                printf("2 - Busca Binaria\n");
                printf("0 - Voltar\n");
                printf("\nEscolha uma opcao: ");
                scanf("%d", &opcao_busca);

                switch(opcao_busca) {

                    case 1: // busca linear
                        printf("Busca linear selecionada.\n");
                        printf("Digite o numero que quer encontrar: ");
                        scanf("%d", &alvo); //guarda o numero quer encontrar

                        QueryPerformanceCounter(&inicioLin);
                        busca = busca_linear(dados, tam, alvo); //busca o numero e guarda sua posição
                        
                        if (busca == -1){
                            printf("Nao encontrado\n");
                        } else{
                            printf("Encontrado na posicao %d\n", busca);
                        }
                        QueryPerformanceCounter(&fimLin);
                        printf("Tempo: %.9f ms\n",((fimLin.QuadPart - inicioLin.QuadPart) * 1000.0 / frequency.QuadPart)); // mostrar tempo da busca linear
                        executado = 1; //afirma que houve uma execução
                        break;

                    case 2: // busca binaria  
                        if(ordenado == 0){
                            printf("Ordene o vetor antes de usar busca binaria.\n");
                            break;
                        }
                        
                        printf("Busca binaria selecionada.\n");
                        printf("Digite o numero que quer encontrar: ");
                        scanf("%d", &alvo); //guarda o numero quer encontrar
                        
                        QueryPerformanceCounter(&inicioBin);
                        busca = busca_binaria(dados ,tam, alvo); //busca o numero e guarda sua posição
                        
                        if (busca == -1){
                            printf("Nao encontrado\n");
                        } else{
                            printf("Encontrado na posicao %d\n", busca);
                        }
                        QueryPerformanceCounter(&fimBin);
                        
                        printf("Tempo: %.9f ms\n", ((fimBin.QuadPart - inicioBin.QuadPart) * 1000.0 / frequency.QuadPart)); // mostrar tempo da busca binária
                        executado = 1; //afirma que houve uma execução
                        break;
                    case 0: //voltar
                        break;

                    default:
                        printf("Opcao invalida\n");
                        break;
                }
                break;

            case 3: // ordenar dados
                if (arquivo_carregado == 0) { //verifica se foi carregado algum arquivo
                    printf("Carregue um arquivo antes de continuar..\n"); 
                    break; 
                }

                printf("\n ORDENACAO DE DADOS \n"); //menu
                printf("1 - Insert\n");
                printf("2 - Bubble\n");
                printf("3 - Selection\n");
                printf("4 - Merge\n");  
                printf("5 - Quick\n");
                printf("6 - Tonico(EXTRA)\n");
                printf("0 - Voltar\n");
                printf("\nEscolha uma opcao: ");
                scanf("%d", &opcao_ordenacao);
                
                switch (opcao_ordenacao)
                {
                case 1: //Insert
                    QueryPerformanceCounter(&inicioInsertion);
                    insertSort(dados, tam);
                    QueryPerformanceCounter(&fimInsertion);
                    printf("Tempo: %.9f ms\n",((fimInsertion.QuadPart - inicioInsertion.QuadPart) * 1000.0 / frequency.QuadPart));
                    break;
                case 2: //Bubble
                    QueryPerformanceCounter(&inicioBubble);
                    bubbleSort(dados, tam);
                    QueryPerformanceCounter(&fimBubble);
                    printf("Tempo: %.9f ms\n",((fimBubble.QuadPart - inicioBubble.QuadPart) * 1000.0 / frequency.QuadPart));
                    break;
                case 3: //Selection
                    QueryPerformanceCounter(&inicioSelection);
                    selectionSort(dados, tam);
                    QueryPerformanceCounter(&fimSelection);
                    printf("Tempo: %.9f ms\n",((fimSelection.QuadPart - inicioSelection.QuadPart) * 1000.0 / frequency.QuadPart));
                    break;
                case 4: //Merge
                    QueryPerformanceCounter(&inicioMerge);
                    mergeSort(dados, 0, tam - 1);
                    QueryPerformanceCounter(&fimMerge);
                    printf("Tempo: %.9f ms\n",((fimMerge.QuadPart - inicioMerge.QuadPart) * 1000.0 / frequency.QuadPart));
                    break;
                case 5: //Quick
                    QueryPerformanceCounter(&inicioQuick);
                    quickSort(dados, 0, tam - 1);
                    QueryPerformanceCounter(&fimQuick);
                    printf("Tempo: %.9f ms\n",((fimQuick.QuadPart - inicioQuick.QuadPart) * 1000.0 / frequency.QuadPart));
                    break; 
                case 6: //Extra
                    QueryPerformanceCounter(&inicioTonico);
                    tonico(dados, 0, tam - 1);
                    QueryPerformanceCounter(&fimTonico);
                    printf("Tempo: %.9f ms\n",((fimTonico.QuadPart - inicioTonico.QuadPart) * 1000.0 / frequency.QuadPart));
                    break;
                case 0: //voltar
                    break;
                default: //opção invalida
                    printf("Opcao invalida.\n");
                    break;
                }

                executado = 1;
                ordenado = 1;

                printf("Deseja salvar vetor ordenado em arquivo? (1 - Sim, 0 - Nao): ");
                scanf("%d", &salvar);
                if(salvar == 1){
                    gravarDados("arquivo_ordenado.txt", dados, tam); //salva o arquivo
                } else if (salvar != 0) {
                    printf("Opcao invalida\n");
                }

                  break;

            case 4: // gerar relatorio
                if (arquivo_carregado == 0) { //verifica se foi carregado algum arquivo 
                    printf("Carregue um arquivo antes de continuar..\n"); 
                    break; 
                }
                if (executado == 0){ //verifica se houve executações
                    printf("Faca uma Busca ou Ordene um arquivo primeiro\n"); 
                    break;
                }
                printf("Gerando relatorio...........................................\n");
                gerarlog(dados, tam, alvo);
                printf("Relatorio pronto! :)\n");
                break;

            case 5: // sair
                printf("Encerrando o programa...\n");
                break;

            default: // opção invalida default:
                printf("Opcao invalida!\n");
                break;
        }

    } while(opcao != 5);
    
    free(dados);
    
    return 0;
}