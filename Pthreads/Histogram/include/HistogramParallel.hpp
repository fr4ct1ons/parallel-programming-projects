#pragma once

#include<pthread.h>
#include<cstdio>
#include"Histogram.hpp"
#include<vector>

namespace HistogramParallel
{
    std::vector<pthread_mutex_t> mutexes;
    Histogram *currentHistogram;
    double *currentData;
    size_t dataSize;
    size_t fragmentedSize;

    void* ThreadAnalysis(void * vRank)
    {
        long rank = (long) vRank;
        //printf("Thread %d reporting. Histogram has %d ranges and data has %d size. \n" , rank, currentHistogram->GetRangeCount(), dataSize);

        long firstElement = rank * fragmentedSize;
        long lastElement = (rank + 1) * fragmentedSize;

        for (size_t i = firstElement; i < lastElement; i++)
        {
            double value = currentData[i];
            for (size_t j = 1; j < currentHistogram->GetRangeCount(); j++)
            {
                if(value >= currentHistogram->GetRangeByIndex(j - 1) && value < currentHistogram->GetRangeByIndex(j))
                {
                    pthread_mutex_lock(&mutexes[j - 1]);
                    currentHistogram->ForceIncrementRange(j - 1);
                    pthread_mutex_unlock(&mutexes[j - 1]);
                }
            }
            
        }
        
    }

    void ParallelAnalyze(Histogram* hist, std::vector<double> &data, size_t coreAmount)
    {
        pthread_mutex_t toAdd;
        mutexes.clear();
        mutexes.insert(mutexes.begin(), hist->GetRangeCount(), toAdd);
        pthread_t *pthreadHandles = new pthread_t[coreAmount];

        for (size_t i = 0; i < hist->GetRangeCount(); i++)
        {
            pthread_mutex_init(&mutexes[i], NULL);
        }

        currentHistogram = hist;
        currentData = &data[0];
        dataSize = data.size();

        fragmentedSize = (size_t)dataSize/coreAmount;

        for (long i = 0; i < coreAmount; i++)
        {
            pthread_create(&pthreadHandles[i], NULL, ThreadAnalysis, (void*) i);
        }

        for (long i = 0; i < coreAmount; i++)
        {
            pthread_join(pthreadHandles[i], NULL);
        }
    }
}