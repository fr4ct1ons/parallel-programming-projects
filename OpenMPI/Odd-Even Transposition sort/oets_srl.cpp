#include<iostream>
#include<string>
#include<cmath>
#include<chrono>
#include<cstdio>
#include<fstream>
#include"sortingAlgorithms.h"

int main(int argc, char* argv[])
{
    std::cout << std::fixed;

    int n = 0;
    if (argc <= 1)
    {
        std::cout << "A problem size was not specified. Will set the size to 24. If you want to specify a problem size, rerun with the following parameters." << "\n";
        std::cout << argv[0] << " <size of problem>" << std::endl;
        n = 24;
    }
    else
    {
        n = std::stoi(argv[1]);
    }

    int* values = new int[n];

    {
        for (int i = 0, val = n; i < n; i++)
        {
            values[i] = val;
            val--;
        }
    }

    std::cout << "{ ";
    for (int j = 0; j < n; j++)
    {
        std::cout << values[j] << " ";
    }
    std::cout << " }" << std::endl;

    std::chrono::system_clock::time_point startTime;

    startTime = std::chrono::system_clock::now();

    SortingAlgorithms::OddEvenTranspositionSort<int>(values, n); // Sorting values

    auto endTime = std::chrono::system_clock::now();

    std::chrono::duration<long double> processDuration = endTime - startTime;

    std::cout << "Process duration: " << processDuration.count() << "\n";

    std::cout << "{ ";
    for (int j = 0; j < n; j++)
    {
        std::cout << values[j] << " ";
    }
    std::cout << "}" << std::endl;

    return 0;
}