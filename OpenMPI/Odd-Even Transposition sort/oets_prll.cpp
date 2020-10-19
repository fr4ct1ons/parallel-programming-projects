#include<iostream>
#include"mpi.h"
#include<string>
#include<cmath>
#include<chrono>
#include<cstdio>
#include<fstream>

#include"arrayAux.h"
#include"sortingAlgorithms.h"

int main(int argc, char* argv[])
{
    std::cout << std::fixed;
    
    MPI_Init(NULL, NULL);
    int my_rank, comm_sz;

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int n = 0;
    int *generatedValues;
    std::chrono::system_clock::time_point startTime;

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

    if (my_rank == 0)
    {
        startTime = std::chrono::system_clock::now();
    }

    MPI_Scatter(generatedValues, localN, MPI_INT, localValues, localN, MPI_INT, 0, MPI_COMM_WORLD); //Send the values

    SortingAlgorithms::OddEvenTranspositionSort<int>(localValues, localN);

    for (int i = 0; i < localN; i++)
    {
        if (i % 2 == 0) // Is even phase
        {
            //std::cout << "EVEN PHASE " << std::endl;
            if (my_rank % 2 != 0) //Is odd process
            {
                MPI_Send(localValues, localN, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD);
                MPI_Recv(localValues, localN, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            else// is even process
            {
                int* tempValues = new int[localN];

                MPI_Recv(tempValues, localN, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                int* jointValues = ArrayAux::JoinArrays<int>(localValues, tempValues, localN, localN);
                std::cout << "Joint values before sorting, for process " << my_rank << ": ";
                ArrayAux::PrintArrayValues<int>(jointValues, localN * 2);

                SortingAlgorithms::OddEvenTranspositionSort(jointValues, localN * 2);

                std::cout << "Joint values after sorting, for process " << my_rank << ": ";
                ArrayAux::PrintArrayValues<int>(jointValues, localN * 2);

                MPI_Send(jointValues + localN, localN, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD);
            }
        }
        else
        {
            //std::cout << "ODD PHASE " << std::endl;
            if (my_rank % 2 != 0) //Is odd process
            {
                if (my_rank != comm_sz - 1)
                {
                    int* tempValues = new int[localN];

                    MPI_Recv(tempValues, localN, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                    int* jointValues = ArrayAux::JoinArrays<int>(localValues, tempValues, localN, localN);
                    std::cout << "Joint values before sorting, for process " << my_rank << ": ";
                    ArrayAux::PrintArrayValues<int>(jointValues, localN * 2);

                    SortingAlgorithms::OddEvenTranspositionSort(jointValues, localN * 2);

                    std::cout << "Joint values after sorting, for process " << my_rank << ": ";
                    ArrayAux::PrintArrayValues<int>(jointValues, localN * 2);

                    MPI_Send(jointValues + localN, localN, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD);
                }
            }
            else// is even process
            {
                MPI_Send(localValues, localN, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD);
                MPI_Recv(localValues, localN, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

        MPI_Barrier(MPI_COMM_WORLD);
    }

    int* finalValues = new int[n];

    std::cout << "Process of number " << my_rank << " will send: ";
    ArrayAux::PrintArrayValues<int>(localValues, localN);

    MPI_Gather(localValues, localN, MPI_INT, finalValues, localN, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (my_rank == 0)
    {
        ArrayAux::PrintArrayValues<int>(finalValues, n);
    }
    //ArrayAux::PrintArrayValues<int>(localValues, localN);

    MPI_Finalize();
    return 0;
}