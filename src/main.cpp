#include <iostream>
#include <mpi/mpi.h>

int main(int argc, char **argv) {

    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}