#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int dims[2] = {2, 2}; // 2x2 grid
    int coords[2];
    MPI_Comm cart_comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size != dims[0] * dims[1]) {
        printf("Please run with %d processes.\n", dims[0] * dims[1]);
        MPI_Finalize();
        return 0;
    }

    // Create a 2D Cartesian communicator
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, MPI_CART_PERIODIC, 0, &cart_comm);
    MPI_Cart_coords(cart_comm, rank, 2, coords);

    // Print information about each process
    printf("Process %d at coordinates (%d, %d) in the grid.\n", rank, coords[0], coords[1]);

    int left, right, up, down;
    MPI_Cart_shift(cart_comm, 0, 1, &up, &down);
    MPI_Cart_shift(cart_comm, 1, 1, &left, &right);

    // Send and receive messages to neighbors
    int send_data = rank;
    int recv_data;

    MPI_Sendrecv(&send_data, 1, MPI_INT, up, 0, &recv_data, 1, MPI_INT, down, 0, cart_comm, MPI_STATUS_IGNORE);
    printf("Process %d received from UP neighbor: %d\n", rank, recv_data);

    MPI_Sendrecv(&send_data, 1, MPI_INT, down, 1, &recv_data, 1, MPI_INT, up, 1, cart_comm, MPI_STATUS_IGNORE);
    printf("Process %d received from DOWN neighbor: %d\n", rank, recv_data);

    MPI_Sendrecv(&send_data, 1, MPI_INT, left, 2, &recv_data, 1, MPI_INT, right, 2, cart_comm, MPI_STATUS_IGNORE);
    printf("Process %d received from LEFT neighbor: %d\n", rank, recv_data);

    MPI_Sendrecv(&send_data, 1, MPI_INT, right, 3, &recv_data, 1, MPI_INT, left, 3, cart_comm, MPI_STATUS_IGNORE);
    printf("Process %d received from RIGHT neighbor: %d\n", rank, recv_data);

    MPI_Comm_free(&cart_comm);
    MPI_Finalize();
    return 0;
}
