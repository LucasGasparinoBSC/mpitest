#include "mpi_rma.h"

void testWinOps()
{
    // Set the error handler to return errors
    int ierr;
    MPI_Comm_set_errhandler(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
    MPI_Win_set_errhandler(MPI_WIN_NULL,MPI_ERRORS_RETURN);

    // Testing MPI_Win_allocate
    int *a;
    int n=10;
    MPI_Win win;
    ierr = MPI_Win_allocate(n*sizeof(int),sizeof(int),MPI_INFO_NULL,MPI_COMM_WORLD,&a,&win);
    if (ierr != MPI_SUCCESS) {
        printf("MPI_Win_allocate failed with error code %d\n",ierr);
        MPI_Abort(MPI_COMM_WORLD,ierr);
    }
    for (int i=0; i<n; i++) a[i] = i;
    ierr = MPI_Win_free(&win);
    if (ierr != MPI_SUCCESS) {
        printf("MPI_Win_free failed with error code %d\n",ierr);
        MPI_Abort(MPI_COMM_WORLD,ierr);
    }

    // Testing MPI_Win_create
    a = (int *)malloc(n*sizeof(int));
    for (int i=0; i<n; i++) a[i] = i;
    ierr = MPI_Win_create(a,n*sizeof(int),sizeof(int),MPI_INFO_NULL,MPI_COMM_WORLD,&win);
    if (ierr != MPI_SUCCESS) {
        printf("MPI_Win_create failed with error code %d\n",ierr);
        MPI_Abort(MPI_COMM_WORLD,ierr);
    }
    ierr = MPI_Win_free(&win);
    if (ierr != MPI_SUCCESS) {
        printf("MPI_Win_free failed with error code %d\n",ierr);
        MPI_Abort(MPI_COMM_WORLD,ierr);
    }
    free(a);

    // Testing MPI_Win_create_dynamic
    ierr = MPI_Win_create_dynamic(MPI_INFO_NULL,MPI_COMM_WORLD,&win);
    if (ierr != MPI_SUCCESS) {
        printf("MPI_Win_create_dynamic failed with error code %d\n",ierr);
        MPI_Abort(MPI_COMM_WORLD,ierr);
    }
    a = (int *)malloc(n*sizeof(int));
    for (int i=0; i<n; i++) a[i] = i;
    ierr = MPI_Win_attach(win,a,n*sizeof(int));
    if (ierr != MPI_SUCCESS) {
        printf("MPI_Win_attach failed with error code %d\n",ierr);
        MPI_Abort(MPI_COMM_WORLD,ierr);
    }
    ierr = MPI_Win_detach(win,a);
    if (ierr != MPI_SUCCESS) {
        printf("MPI_Win_detach failed with error code %d\n",ierr);
        MPI_Abort(MPI_COMM_WORLD,ierr);
    }
    ierr = MPI_Win_free(&win);
    if (ierr != MPI_SUCCESS) {
        printf("MPI_Win_free failed with error code %d\n",ierr);
        MPI_Abort(MPI_COMM_WORLD,ierr);
    }
    free(a);

    // Testing MPI_Win_allocate_shared
    // TODO: implement this test

}