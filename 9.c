#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int dims[] = {2, 2}, coords[2];
    MPI_Comm cart_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, (int[]){1, 0}, 1, &cart_comm);
    MPI_Cart_coords(cart_comm, rank, 2, coords);

    printf("Rank %d: Coordinates (%d, %d)\n", rank, coords[0], coords[1]);

    int left, right, up, down;
    MPI_Cart_shift(cart_comm, 0, 1, &up, &down);
    MPI_Cart_shift(cart_comm, 1, 1, &left, &right);

    printf("Rank %d: Up: %d, Down: %d, Left: %d, Right: %d\n", rank, up, down, left, right);

    MPI_Comm_free(&cart_comm);
    MPI_Finalize();

    return 0;
}
