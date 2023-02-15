#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "mpi_rma.h"

int main(void)
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Define that the MPI environment will return errors instead of aborting
    MPI_Comm_set_errhandler(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
    MPI_Win_set_errhandler(MPI_WIN_NULL,MPI_ERRORS_RETURN);

    // Check that MPI can get the number of processes and the rank of the current process
    int ierr = 0;
    int rank, size;
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (ierr != MPI_SUCCESS) {
        printf("Error: MPI_Comm_rank failed with error code %d\n", ierr);
        MPI_Abort(MPI_COMM_WORLD, ierr);
    }
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (ierr != MPI_SUCCESS) {
        printf("Error: MPI_Comm_size failed with error code %d\n", ierr);
        MPI_Abort(MPI_COMM_WORLD, ierr);
    }

    // Test window creation and destruction
    testWinOps();

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}