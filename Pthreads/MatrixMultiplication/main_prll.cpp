#include<iostream>
#include<cstdio>
#include<pthread.h>
#include"Matrix.hpp"

int threadCount = 4;
int runningThreads;
bool* threadFinished;

Matrix<double> multA(4, 4);
Matrix<double> multB(4, 1);

Matrix<double> result(4, 1);

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

    for (size_t i = firstLine; i < lastLine; i++)
    {
        result.data[i][0] = 0.0;
        for (size_t j = 0; j < multA.Columns(); j++)
        {
            result.data[i][0] += multA.data[i][j] * multB.data[j][0];
        }
    }
    
    threadFinished[rank] = true;
}

int main(int argc, char const *argv[])
{
    pthread_t *threadHandles;
    
    threadHandles = new pthread_t[threadCount];

    threadFinished = new bool[threadCount + 1];
    for (size_t i = 0; i < threadCount; i++)
    {
        threadFinished[i] = false;
    }

    PopulateRandom(11, &multA);
    PopulateRandom(12, &multB);
    PopulateRandom(10, &result);
    
    std::cout << "Hello from the main thread!" << std::endl;
    std::cout << "Current values in multA: " << multA.ToString() << std::endl;
    std::cout << "Current values in multB: " << multB.ToString() << std::endl;

    std::cout << "Current values in result: " << result.ToString() << std::endl;

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
    
    std::cout << "Current values in result: " << result.ToString() << std::endl;

    return 0;
}
