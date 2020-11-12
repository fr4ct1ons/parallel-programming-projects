#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
//#include<chrono>
#include<pthread.h>

#include"testingAux.h"
#include"Matrix.hpp"

int threadCount = 4;
int runningThreads;
bool* threadFinished;
bool isDebugEnabled = false;

Matrix<double> multA(4, 4);
Matrix<double> multB(4, 4);

Matrix<double> result(4, 4);

void *Pth_mat_mul(void *v_Rank)
{
    long rank = (long) v_Rank;
    
    int localLines = multA.Lines() / threadCount;
    int firstLine = rank * localLines;
    int lastLine = (rank + 1) * localLines -1;

    if(isDebugEnabled)
    {
        printf("-- RANK %d - Local lines: %d - First line: %d - Last line: %d \n", rank, localLines, firstLine, lastLine);
    }

    for (size_t i = firstLine; i <= lastLine; i++)
    {
        for (size_t j = 0; j < multB.Columns(); j++)
        {
            result.data[i][j] = 0.0;
            for (size_t k = 0; k < multA.Columns(); ++k)
            {
                //printf("--RANK %d - Result.data[%d][%d] equals %d before\n ", rank,i, j, result.data[i][j]);
                result.data[i][j] += multA.data[i][k] * multB.data[k][j];
                //printf("--RANK %d - Result.data[%d][%d] equals %d after\n ", rank,i, j, result.data[i][j]);
            }
        }
        
    }
    
    return NULL;
}

int main(int argc, char const *argv[])
{

    threadCount = std::atoi(argv[1]);

    int unformattedSize = std::atoi(argv[2]);

    const int problemSize = 4 * unformattedSize;


    if(argc > 3)
    {
        int thirdParam = std::atoi(argv[3]);
        if(thirdParam != 0)
        {
            std::cout << "Enabled debug." << std::endl;

            isDebugEnabled = true;
        }

    }

    if(multA.Columns() != multB.Lines())
    {
        std::cout << "INVALID MATRIX SIZE! Make sure that multA's columns size equals multB's lines size." << std::endl;
        return 1;
    }

    if(isDebugEnabled)
    {
        std::cout << "Problem size: " << problemSize << " - Thread count: " << threadCount << "Unformatted size: " << unformattedSize << "\n" << std::endl;
    }
    
    //std::cout << "Here1!" << std::endl;
    multA.Reset(problemSize, problemSize);
    multB.Reset(problemSize, problemSize);

    pthread_t *threadHandles;

    threadHandles = new pthread_t[threadCount];

    result.Reset(multA.Lines(), multB.Columns());

    PopulateRandom(11, &multA, 2, 1);
    PopulateRandom(12, &multB, 2, 1);
    PopulateRandom(10, &result, 2, 1);

    //std::cout << "Here2!" << std::endl;


    if(isDebugEnabled)
    {
        std::cout << "Current results: \n" << result.ToString() << std::endl;
        std::cout << "Current multA: \n" << multB.ToString() << std::endl;
        std::cout << "Current multB: \n" << multA.ToString() << std::endl;
    }


    struct timespec startTime;
    struct timespec endTime;

    //std::cout << "Here3!" << std::endl;

    clock_gettime(CLOCK_MONOTONIC, &startTime);

    for (int i = 0; i < threadCount; i++)
    {
        pthread_create(&threadHandles[i], NULL, Pth_mat_mul, (void*) i);
    }

    for (int i = 0; i < threadCount; i++)
    {
        pthread_join(threadHandles[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &endTime);

    //std::cout << "Here5!" << std::endl;

    delete threadHandles;

    double processDuration = endTime.tv_sec - startTime.tv_sec;

    processDuration += (endTime.tv_nsec - startTime.tv_nsec) / 1000000000.0;

    if(isDebugEnabled)
    {
        std::cout << "Finished multiplication. Results: \n" << result.ToString() << std::endl;    
    }

    std::stringstream results;
    results << std::fixed << problemSize << " , " << processDuration << " , " << "PARALLEL " << " , " << threadCount << std::endl;

    std::cout << results.str() << std::endl;
    TestingAux::WriteToResults(results);

    return 0;
}
