//
// Created by tommy on 10.06.17.
//

#include "Monitor.h"
#include <mpi.h>

Monitor::Monitor(int *argc, char ***argv) {
    MPI_Init(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &this->rank);
    MPI_Comm_size(MPI_COMM_WORLD, &this->size);
}

Monitor::~Monitor() {
    MPI_Finalize();
}
