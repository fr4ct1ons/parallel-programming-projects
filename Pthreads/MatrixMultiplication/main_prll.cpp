#include<iostream>
#include<cstdio>
#include<pthread.h>
#include"Matrix.hpp"

int threadCount = 4;
int runningThreads;
bool* threadFinished;

Matrix<double> multA(4, 4);
Matrix<double> multB(4, 4);

Matrix<double> result;

void *Hello(void* v_Rank)
{
    long rank = (long) v_Rank;
    printf("Hello from process %d \n", rank);
    return NULL;
}

void *Pth_mat_mul(void *v_Rank)
{
    long rank = (long) v_Rank;
    
    int localLines = multA.Lines() / threadCount;
    int firstLine = rank * localLines;
    int lastLine = (rank + 1) * localLines -1;

    for (size_t i = 0; i <= lastLine; i++)
    {
        for (size_t j = 0; j < multB.Columns(); j++)
        {
            result.data[i][j] = 0.0;
            for (size_t k = 0; k < multA.Columns(); ++k)
            {
                result.data[i][j] += multA.data[i][k] * multB.data[k][j];
            }
        }
        
    }

    /*for (size_t i = firstLine; i <= lastLine; i++)
    {
        result.data[i][0] = 0.0;
        //printf("Thread %d reporting: result.data[%d][0] equals %d BEFORE operation.\n", rank, i, result.data[i][0]);
        for (size_t j = 0; j < multA.Columns(); j++)
        {
            result.data[i][0] += multA.data[i][j] * multB.data[j][0];
        }
        //printf("Thread %d reporting: result.data[%d][0] equals %d AFTER operation.\n", rank, i, result.data[i][0]);
    }*/
    
    threadFinished[rank] = true;

    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t *threadHandles;

    if(multA.Columns() != multB.Lines())
    {
        std::cout << "INVALID MATRIX SIZE! Make sure that multA's columns size equals multB's lines size." << std::endl;
        return 1;
    }
    
    threadHandles = new pthread_t[threadCount];

    threadFinished = new bool[threadCount + 1];
    for (size_t i = 0; i < threadCount; i++)
    {
        threadFinished[i] = false;
    }

    result.Reset(multA.Lines(), multB.Columns());

    PopulateRandom(11, &multA, 2, 1);
    PopulateRandom(12, &multB, 2, 1);
    PopulateRandom(10, &result, 2, 1);
    
    std::cout << "Hello from the main thread!" << std::endl;
    std::cout << "Current values in multA: \n" << multA.ToString() << std::endl;
    std::cout << "Current values in multB: \n" << multB.ToString() << std::endl;

    std::cout << "Current values in result: \n" << result.ToString() << std::endl;

    for (int i = 0; i < threadCount; i++)
    {
        pthread_create(&threadHandles[i], NULL, Pth_mat_mul, (void*) i);
    }

    Matrix<double> test(4, 4);

    for (int i = 0; i < threadCount; i++)
    {
        pthread_join(threadHandles[i], NULL);
    }

    delete threadHandles;

    bool isFinished = false;
    while (!isFinished)  
    {
        isFinished = true;
        for (size_t i = 0; i < threadCount; i++)
        {
            if(!threadFinished[i])
            isFinished = false;
            break;
        }
    }
    
    std::cout << "Finished multiplication. Current values in result: \n" << result.ToString() << std::endl;

    return 0;
}