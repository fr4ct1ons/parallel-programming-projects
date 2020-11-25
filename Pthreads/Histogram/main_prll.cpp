#include<iostream>
#include<cstdio>
#include"HistogramParallel.hpp"
#include"Histogram.hpp"

int main(int argc, char const *argv[])
{
    std::cout << "Helo, world!" << std::endl;
    
    long dataSize = 20;
    bool isDebugEnabled = false;

    if(argc > 1)
    {
        dataSize = std::stoi(argv[1]);
    }

    if(argc > 2)
    {
        long temp = std::stoi(argv[2]);
        
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

    HistogramParallel::ParallelAnalyze(&test, data, 4);

    clock_gettime(CLOCK_MONOTONIC, &endTime);

    double processDuration = endTime.tv_sec - startTime.tv_sec;
    processDuration += (endTime.tv_nsec - startTime.tv_nsec) / 1000000000.0;

    if(isDebugEnabled)
    {
        std::cout << *HistogramParallel::currentHistogram << '\n';
        std::cout << "Duration: " << processDuration << std::endl;
    }
    return 0;
}
