#include<iostream>
#include"mpi.h"

int main()
{
    //printf("Hello, world!\n");

    int my_rank, comm_sz;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    std::cout << "Processor " << my_rank + 1 << " of " << comm_sz << " says hello!"<< std::endl;

    MPI_Finalize();
    return 0;
}
