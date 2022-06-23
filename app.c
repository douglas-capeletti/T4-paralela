#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef	FALSE
#define	FALSE	(0)
#endif

#ifndef	TRUE
#define	TRUE	(!FALSE)
#endif

#define SIZE 300

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

int main(int argc, char **argv)
{

    MPI_Init(&argc, &argv);

    int my_rank, proc_n, tag = 99;
    MPI_Comm_size(MPI_COMM_WORLD, &proc_n);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int vetor_size = SIZE / proc_n; // gero parte local do vetor (1/np avos do vetor global)
    int vetor[vetor_size];
    for (int i = 0; i < vetor_size; i++)
        vetor[i] = vetor_size - i; //Inicializa na ordem reversa

    int buffer_size = vetor_size / 10;
    int buffer[buffer_size];

    int status[proc_n];

    int pronto = FALSE;
    while (!pronto)
    {

        // ordeno vetor local
        int status[my_rank] = FALSE;
        bubbleSort(vetor, vetor_size);

        // verifico condição de parada

        // se não for np-1, mando o meu maior elemento para a direita
        if (my_rank < proc_n)
        {
            //envia elemento da direita
        }

        // se não for 0, recebo o maior elemento da esquerda
        if (proc_n != 0)
        {
            //recebo o maior da esquerda
        }

        // comparo se o meu menor elemento é maior do que o maior elemento recebido (se sim, estou ordenado em relação ao meu vizinho)
        if (vetor[0] > buffer[buffer_size - 1])
        {
            status[my_rank] = TRUE;
        }

        // compartilho o meu estado com todos os processos, fazendo um BCAST com cada processo como origem (NP vezes)

        for (int i = 0; i < proc_n; i++)
        {
            //enviar o status na posicao proc_n
            MPI_Bcast(&status, 1, MPI_INT, 0, MPI_COMM_WORLD);
        }

        // se todos estiverem ordenados com seus vizinhos, a ordenação do vetor global está pronta ( pronto = TRUE, break)

        // senão continuo

        // troco valores para convergir

        // se não for o 0, mando os menores valores do meu vetor para a esquerda

        // se não for np-1, recebo os menores valores da direita

        // ordeno estes valores com a parte mais alta do meu vetor local

        // devolvo os valores que recebi para a direita

        // se não for o 0, recebo de volta os maiores valores da esquerda
    }

    MPI_Finalize();
}
