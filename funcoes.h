#ifndef FUNCOES_H
#define FUNCOES_H

// Carregamento de arquivos
void carregar_arquivos(int **dados, int *tam);

// Buscas
int busca_linear(int vetor[], int tam, int alvo);
int busca_binaria(int a[], int n, int chave);

// Algoritmos de ordenação
void insertSort(int *vet, int n);
void bubbleSort(int *vet, int n);
void selectionSort(int *vet, int n);
void mergeSort(int vet[], int esquerda, int direita);  
void merge(int vet[], int esquerda, int meio, int direita);  
void quickSort(int vet[], int menor, int maior);
int particao(int vet[], int menor, int maior);
void tonico(int *a, int comeco, int fim);

// Funções auxiliares
void trocar(int *a, int *b);
void troca(int *vet, int i, int j);  

// Relatório
void gerarlog(int *dados, int tam, int alvo);

#endif