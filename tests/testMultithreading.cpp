//
// Created by tommy on 18.06.17.
//

#include <catch/catch.hpp>
#include <mpi.h>

TEST_CASE("Test multithreading support", "[thread]") {
    int provided;
    MPI_Init_thread(nullptr, nullptr, MPI_THREAD_SERIALIZED, &provided);
    if (provided < MPI_THREAD_SERIALIZED)
    {
        printf("ERROR: The MPI library does not have full thread support\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    MPI_Finalize();
}
