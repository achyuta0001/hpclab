#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("Please run with at least 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    // Blocking communication
    if (rank == 0) {
        int data = 42;
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data: %d\n", data);
    } else if (rank == 1) {
        int received_data;
        MPI_Recv(&received_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data: %d\n", received_data);
    }

    MPI_Barrier(MPI_COMM_WORLD); // Ensure all processes have reached this point

    // Nonblocking communication
    if (rank == 0) {
        int data = 99;
        MPI_Request request;
        MPI_Isend(&data, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        printf("Process 0 sent data (nonblocking): %d\n", data);
    } else if (rank == 1) {
        int received_data;
        MPI_Request request;
        MPI_Irecv(&received_data, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        printf("Process 1 received data (nonblocking): %d\n", received_data);
    }

    MPI_Finalize();
    return 0;
}
