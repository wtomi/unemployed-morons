//
// Created by tommy on 10.06.17.
//

#ifndef UNEMPLOYED_MORRONS_MONITOR_H
#define UNEMPLOYED_MORRONS_MONITOR_H

#include <sstream>
#include <mpi.h>

class Monitor {
public:
    int rank;
    int size;
    MPI_Comm mpiComm;

    Monitor(int *argc, char ***argv, MPI_Comm mpiComm = MPI_COMM_WORLD);
    ~Monitor();

    void send(std::stringstream stringStreamMessage, int destination, int tag);
    std::stringstream receive(int source, int tag);
    int probeAndGetCount(int source, int tag);
    MPI_Status probe(int source, int tag);
    int getCount(MPI_Status &status);
};


#endif //UNEMPLOYED_MORRONS_MONITOR_H
