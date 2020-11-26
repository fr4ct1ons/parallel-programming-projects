#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"HistogramParallel.hpp"
#include"Histogram.hpp"
#include<sstream>

#include"testingAux.h"

int main(int argc, char const *argv[])
{
    //std::cout << "Helo, world!" << std::endl;
    
    long dataSize = 20;
    bool isDebugEnabled = false;
    long coreAmount = 4;
    
    if(argc > 1)
    {
        coreAmount = atoi(argv[1]);
    }

    if(argc > 2)
    {
        dataSize = atoi(argv[2]);
    }

    if(argc > 3)
    {
        long temp = atoi(argv[3]);
        
        if(temp == 1)
            isDebugEnabled = true;
    }

    Histogram test;

    for (long i = 0; i < 256; i++)
    {
        test.AddRange((double)i);
    }
    
    std::vector<double> data;

    srand(500);
    
    const long formattedDataSize = dataSize * 4;

    for (size_t i = 0; i < formattedDataSize; i++)
    {
        data.push_back((double) (rand() % 256));
    }
    
    struct timespec startTime;
    struct timespec endTime;

    clock_gettime(CLOCK_MONOTONIC, &startTime);

    HistogramParallel::ParallelAnalyze(&test, data, coreAmount);

    clock_gettime(CLOCK_MONOTONIC, &endTime);

    double processDuration = endTime.tv_sec - startTime.tv_sec;
    processDuration += (endTime.tv_nsec - startTime.tv_nsec) / 1000000000.0;

    std::stringstream results;
    results << std::fixed << formattedDataSize << " , " << processDuration << " , " << "PARALLEL , " << coreAmount << std::endl;

    if(isDebugEnabled)
    {
        std::cout << *HistogramParallel::currentHistogram << '\n';
        std::cout << results.str() << std::endl;
    }

    TestingAux::WriteToResults(results);

    return 0;
}
