#include<iostream>
#include"mpi.h"
#include<string>
#include<cmath>
#include<chrono>
#include<cstdio>
#include<fstream>

#include"arrayAux.h"

int main(int argc, char* argv[])
{
    std::cout << std::fixed;
    
    MPI_Init(NULL, NULL);
    int my_rank, comm_sz;

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int n = 0;
    int *generatedValues;

    if (argc <= 1)
    {
        if (my_rank == 0)
        {
            std::cout << "A problem size was not specified. Will set the size to 24. If you want to specify a problem size, rerun with the following parameters." << "\n";
            std::cout << argv[0] << " <size of problem>" << std::endl;
        }
        n = 24;

        generatedValues = new int[n];
    }
    else
    {
        n = std::stoi(argv[1]);
    }

    int localN = n / comm_sz;

    int* localValues = new int[localN];

    if (my_rank == 0)
    {
        for (int i = 0, val = n; i < n; i++)
        {
            generatedValues[i] = val;
            val--;
        }

        ArrayAux::PrintArrayValues<int>(generatedValues, n);

        //MPI_Scatter(generatedValues, n / comm_sz, MPI_INT, localValues, n / comm_sz, MPI_INT, 0, MPI_COMM_WORLD); //Send the values
    }
    else
    {
        //MPI_Scatter(generatedValues, n / comm_sz, MPI_INT, localValues, n / comm_sz, MPI_INT, 0, MPI_COMM_WORLD); //Receive the values
    }

    MPI_Scatter(generatedValues, localN, MPI_INT, localValues, localN, MPI_INT, 0, MPI_COMM_WORLD); //Send the values

    ArrayAux::PrintArrayValues<int>(localValues, localN);

    MPI_Finalize();
    return 0;
}