//
// Created by tommy on 10.06.17.
//

#include <bits/unique_ptr.h>
#include "Monitor.h"

Monitor::Monitor(int *argc, char ***argv, MPI_Comm mpiComm) {
    this->mpiComm = mpiComm;
    MPI_Init(argc, argv);
    MPI_Comm_rank(mpiComm, &this->rank);
    MPI_Comm_size(mpiComm, &this->size);
}

Monitor::~Monitor() {
    MPI_Finalize();
}

void Monitor::send(std::stringstream &stringStreamMessage, int destination, int tag) {
    //add 1 because after conversion to c_str null will be added
    int count = stringStreamMessage.str().length() + 1;
    MPI_Send(stringStreamMessage.str().c_str(), count, MPI_CHAR, destination, tag, mpiComm);
}

std::stringstream Monitor::receive(int source, int tag) {
    int count = probeAndGetCount(source, tag);
    std::unique_ptr<char> buffer(new char[count]);
    MPI_Status status;
    MPI_Recv(buffer.get(), count, MPI_CHAR, source, tag, mpiComm, &status);
    return std::stringstream(buffer.get());
}

int Monitor::probeAndGetCount(int source, int tag) {
    MPI_Status status = probe(source, tag);
    return getCount(status);
}

MPI_Status Monitor::probe(int source, int tag) {
    MPI_Status status;
    MPI_Probe(source, tag, mpiComm, &status);

    return status;
}

int Monitor::getCount(MPI_Status &status) {
    int count;
    MPI_Get_count(&status, MPI_CHAR, &count);

    return count;
}
