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

void Monitor::send(Packet::SharedPtr package) {
    send(package->stringstreamMessage, package->rank, package->tag);
}

void Monitor::send(std::stringstream &stringStreamMessage, int source, int tag) {
    //add 1 because after conversion to c_str null will be added
    int count = static_cast<int>(stringStreamMessage.str().length());
    MPI_Send(stringStreamMessage.str().c_str(), count, MPI_CHAR, source, tag, mpiComm);
}

Packet::SharedPtr Monitor::receive(int source, int tag) {
    int count = probeAndGetCount(source, tag);
    std::unique_ptr<char> buffer(new char[count]);
    MPI_Status status;
    MPI_Recv(buffer.get(), count, MPI_CHAR, source, tag, mpiComm, &status);
    std::stringstream stringstream(std::string(buffer.get(), static_cast<unsigned long>(count)));
    return Packet::Create(stringstream, status.MPI_SOURCE, status.MPI_TAG);
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
