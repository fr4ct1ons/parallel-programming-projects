#include<iostream>
#include"mpi.h"
#include<string>
#include<cmath>
#include<chrono>
#include<cstdio>
#include<fstream>

#include"arrayAux.h"
#include"sortingAlgorithms.h"
#include"testingAux.h"
/*#include <fstream>
#include <iostream>
#include <sstream>

namespace
{
    void WriteToResults(std::stringstream& os)
    {
        try
        {
            std::ofstream output("Results.csv", std::ofstream::app);

            output << std::fixed << os.str();
            output.close();
        }
        catch (const std::exception& exc)
        {
            std::cerr << exc.what() << std::endl;
        }
    }
}*/


int main(int argc, char* argv[])
{
    std::cout << std::fixed;
    
    MPI_Init(NULL, NULL);
    int my_rank, comm_sz;

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int n = 2;
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
    }
    else
    {
        n = std::stoi(argv[1]);
    }

    generatedValues = new int[n];

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

    for (int i = 0; i < comm_sz; i++)
    {
        //std::cout << "NEW PHASE - Current phase: " << i << " Current values for process " << my_rank << ": ";
        //ArrayAux::PrintArrayValues<int>(localValues, localN);
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
                //std::cout << "Joint values before sorting, for process " << my_rank << ": ";
                //ArrayAux::PrintArrayValues<int>(jointValues, localN * 2);

                SortingAlgorithms::OddEvenTranspositionSort(jointValues, localN * 2);

                //std::cout << "Joint values after sorting, for process " << my_rank << ": ";
                //ArrayAux::PrintArrayValues<int>(jointValues, localN * 2);

                //std::cout << "Values of process " << my_rank << " before copying: ";
                //ArrayAux::PrintArrayValues<int>(localValues, localN);
                std::memcpy(localValues, jointValues, sizeof(int) * localN);

                //std::cout << "Values of process " << my_rank << " after copying: ";
                //ArrayAux::PrintArrayValues<int>(localValues, localN);

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
                    //std::cout << "Joint values before sorting, for process " << my_rank << ": ";
                    //ArrayAux::PrintArrayValues<int>(jointValues, localN * 2);

                    SortingAlgorithms::OddEvenTranspositionSort(jointValues, localN * 2);

                    //std::cout << "Joint values after sorting, for process " << my_rank << ": ";
                    //ArrayAux::PrintArrayValues<int>(jointValues, localN * 2);

                    //std::cout << "Values of process " << my_rank << " before copying: ";
                    //ArrayAux::PrintArrayValues<int>(localValues, localN);
                    std::memcpy(localValues, jointValues, sizeof(int) * localN);

                    //std::cout << "Values of process " << my_rank << " after copying: ";
                    //ArrayAux::PrintArrayValues<int>(localValues, localN);

                    MPI_Send(jointValues + localN, localN, MPI_INT, my_rank + 1, 0, MPI_COMM_WORLD);
                }
            }
            else // is even process
            {
                if (comm_sz == 2)
                {
                    if (my_rank != 0)
                    {
                        MPI_Send(localValues, localN, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD);
                        MPI_Recv(localValues, localN, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    }
                }
                else
                {
                    MPI_Send(localValues, localN, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD);
                    MPI_Recv(localValues, localN, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                }
            }
        }
        //std::cout << "END OF PHASE " << i << " - Values for process " << my_rank << " are: ";
        //ArrayAux::PrintArrayValues(localValues, localN);
        MPI_Barrier(MPI_COMM_WORLD);
    }

    int* finalValues = new int[n];

    //std::cout << "Process of number " << my_rank << " will send: ";
    //ArrayAux::PrintArrayValues<int>(localValues, localN);

    MPI_Gather(localValues, localN, MPI_INT, finalValues, localN, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (my_rank == 0)
    {
        //ArrayAux::PrintArrayValues<int>(finalValues, n);
        auto endTime = std::chrono::system_clock::now();

        std::chrono::duration<long double> processDuration = endTime - startTime;

        std::cout << "Problem size: " << n << "\n";
        std::cout << "Process duration: " << processDuration.count() << "\n";
        ArrayAux::PrintArrayValues<int>(finalValues, n);

        /*std::stringstream output;

        output << n << " , " << processDuration.count() << " , " << "PARALLEL" << " , " << comm_sz << std::endl;

        TestingAux::WriteToResults(output);*/
    }
    //ArrayAux::PrintArrayValues<int>(localValues, localN);



    MPI_Finalize();
    return 0;
}