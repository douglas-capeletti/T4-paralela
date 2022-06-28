#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef FALSE
#define FALSE (0)
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif

#define VET_SIZE 1000000 // UM MILIAAAAAAAO ZINIO

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int n, int *arr)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

int main(int argc, char **argv)
{
    // GENERAL VARIABLES
    int my_rank, proc_count;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_count);

    double initial_time = (my_rank == 0) ? MPI_Wtime() : 0;

    // VECTOR VARIABLES
    int local_vec_size = VET_SIZE / proc_count;
    int last = (proc_count - 1);
    int left = (my_rank != 0) ? my_rank - 1 : 0;
    int right = (my_rank < last) ? my_rank + 1 : last;

    // SWAP VARIABLES
    int swap;
    int swap_size = local_vec_size / 10;

    // FILL MAIN VEC
    int *vector = (int *)malloc((swap_size + local_vec_size) * sizeof(int));
    for (int i = 0; i < local_vec_size; i++)
        vector[i] = (proc_count - my_rank) * local_vec_size - i;

    // CONTROL VARIABLES
    int ready_neighbor_count, all_ready = FALSE;
    int ctrl_vec[proc_count];
    memset(ctrl_vec, 0, sizeof(ctrl_vec));

    while (!all_ready)
    {
        bubbleSort(local_vec_size, vector);

        // SEND -> RIGHT
        if (my_rank != last)
        {
            MPI_Send(&vector[local_vec_size - 1], 1, MPI_INT, right, 0, MPI_COMM_WORLD);
        }

        // RECEIVE -> LEFT
        if (my_rank != 0)
        {
            MPI_Recv(&swap, 1, MPI_INT, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            ctrl_vec[my_rank] = swap < vector[0] ? 1 : 0;
        }

        // EXCEPTION CASE SEND
        if (my_rank == 1)
        {
            MPI_Send(vector, 1, MPI_INT, left, 0, MPI_COMM_WORLD);
        }

        // EXCEPTION CASE RECEIVE
        if (my_rank == 0)
        {
            MPI_Recv(&swap, 1, MPI_INT, right, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            ctrl_vec[my_rank] = swap > vector[local_vec_size - 1] ? 1 : 0;
        }

        // BROADCAST STATUS
        for (int i = 0; i < proc_count; i++)
        {
            MPI_Bcast(&ctrl_vec[i], 1, MPI_UNSIGNED_CHAR, i, MPI_COMM_WORLD);
        }

        // VERIFY STATUS
        ready_neighbor_count = 0;
        for (int i = 0; i < (proc_count * 2) - 2; i++)
        {
            if (ctrl_vec[i] == 1)
            {
                ready_neighbor_count++;
            }
        }
        if (ready_neighbor_count == proc_count)
        {
            all_ready = TRUE;
            break;
        }

        if (my_rank != 0)
        {
            // SEND -> LEFT
            MPI_Send(vector, swap_size, MPI_INT, left, 0, MPI_COMM_WORLD);
        }

        if (my_rank != last)
        {
            // RECEIVE -> RIGHT
            MPI_Recv(&vector[local_vec_size], swap_size, MPI_INT, right, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // SORT
            bubbleSort(local_vec_size, vector + swap_size);
            // SEND -> RIGHT
            MPI_Send(&vector[local_vec_size], swap_size, MPI_INT, right, 0, MPI_COMM_WORLD);
        }
        if (my_rank != 0)
        {
            // RECEIVE -> LEFT
            MPI_Recv(vector, swap_size, MPI_INT, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

    } 

    if (my_rank == 0)
    {
        double final_time = (my_rank == 0) ? MPI_Wtime() : 0;
        printf("Tempo de execucao: %.4f s\n", final_time - initial_time);
    }

    free(vector);
    MPI_Finalize();
    return 0;
}
