#include <stdio.h>
#include <stdlib.h>


int particiona(int * vet, int inicio, int fim){
    // PASSO 1: Selecionando um Pivo pela mediana (inicio + fim + meio / 3)
    int pivo = (vet[inicio] + vet[fim] + vet[(inicio + fim) /2]) / 3;
    while (inicio < fim)
    {
        // PASSO 2: Vai da esquerda para a direita buscando um elemento maior
        while(inicio < fim && vet[inicio] <= pivo)
            inicio++;
        
        // PASSO 3: Vai da direita para a esquerda buscando um elemento menor
        while(inicio < fim && vet[fim] >= pivo)
            fim--;

        // PASSO 4: Trocar os valores encontrados
        int aux = vet[inicio];
        vet[inicio] = vet[fim];
        vet[fim] = aux;
    }
    return inicio; 
}

void quick_sort(int * v, int inicio , int fim) {
    if (inicio < fim) {
        int pos = particiona(v, inicio , fim);
        quick_sort(v, inicio, pos - 1); // Mandar a metade que contem os menores
        quick_sort(v, pos, fim); // Mandar a metade que contem os maiores
    }
}

void imprimir(int * v, int tam) {
    int i;
    for(i = 0; i <= tam; i++)
        printf("%d, ", v[i]);
    printf("\n");
}



void merge_sort(int * v, int inicio, int fim){
    int meio, i, j, k, aux[9];
    if(inicio <  fim) {
        meio = (inicio + fim) / 2;
        merge_sort(v, inicio, meio);
        merge_sort(v, meio + 1, fim);

        // Faz o merge ordenando os elementos
        i = inicio;
        j = meio + 1;
        k = inicio;

        while(i <= meio && j <= fim) {
            if(v[i] < v[j]) {
                aux[k] = v[i];
                i++;
            }
            else {
                aux[k] = v[j];
                j++;
            }
            k++;
        }

        while (i <= meio) {
            aux[k] = v[i];
            i++;
            k++;
        }

        while (j <= fim) {
            aux[k] = v[j];
            j++;
            k++;
        }

        // Copiando o vetor auxiliar para o vetor original
        for(i = inicio; i <= fim; i++) {
            v[i] = aux[i];
        }
    }

}
 


int main() {

    // QUICK SORT 
    // int vet[] = {47, 35, 12, 49, 56, 25, 71, 83, 5, 3, 1, 70, 99, 10, 61}; // Tamanho = 15

    // imprimir(vet, 14);
    // quick_sort(vet, 0, 14);
    // imprimir(vet, 14);


    // MERGE SORT
    int vet[] = {5, 7, 9, 1, 3, 2, 4, 8, 6};
    imprimir(vet, 8);
    merge_sort(vet, 0, 8);
    imprimir(vet, 8);



    return 0;
}