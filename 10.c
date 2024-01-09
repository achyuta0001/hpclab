#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_msg = rank;
    int recv_msg;

    // Blocking communication using MPI_Send and MPI_Recv
    MPI_Send(&send_msg, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    MPI_Recv(&recv_msg, 1, MPI_INT, (rank - 1 + size) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Rank %d received a message using blocking communication: %d\n", rank, recv_msg);

    // Non-blocking communication using MPI_Isend and MPI_Irecv
    MPI_Request request;
    MPI_Isend(&send_msg, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD, &request);

    // Perform some computation while waiting for the message
    printf("Rank %d performing computation...\n", rank);

    MPI_Irecv(&recv_msg, 1, MPI_INT, (rank - 1 + size) % size, 1, MPI_COMM_WORLD, &request);

    // Wait for both the send and receive operations to complete
    MPI_Wait(&request, MPI_STATUS_IGNORE);

    printf("Rank %d received a message using non-blocking communication: %d\n", rank, recv_msg);

    MPI_Finalize();

    return 0;
}
