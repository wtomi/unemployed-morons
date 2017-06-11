//
// Created by tommy on 10.06.17.
//

#ifndef UNEMPLOYED_MORRONS_MONITOR_H
#define UNEMPLOYED_MORRONS_MONITOR_H

#include <sstream>
#include <mpi.h>
#include "Packet.h"

class Monitor {
public:
    static const int ANY_SOURCE = MPI_ANY_SOURCE;
    static const int ANY_TAG = MPI_ANY_TAG;
    int rank;
    int size;
    MPI_Comm mpiComm;

    Monitor(int *argc = nullptr, char ***argv = nullptr, MPI_Comm mpiComm = MPI_COMM_WORLD);
    ~Monitor();

    void send(Packet &package);
    void send(std::stringstream &stringStreamMessage, int source, int tag);
    Packet receive(int source = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG);
    int probeAndGetCount(int source = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG);
    MPI_Status probe(int source = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG);
    int getCount(MPI_Status &status);
};


#endif //UNEMPLOYED_MORRONS_MONITOR_H
