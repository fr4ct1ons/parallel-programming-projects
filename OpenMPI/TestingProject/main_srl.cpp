#include<iostream>
#include"mpi.h"
#include<string>
#include<cmath>
#include<chrono>
#include<cstdio>
#include<fstream>

long double Function(long double x)
{
    //return 2.0f;
    return sin(x) + 2.5f;
}

long double TrapezeArea(long double bottomBase, long double topBase, long double height)
{
    return ((topBase + bottomBase) * height)/2;
}

long double TrapezeAreaPerProcess(long double bottomBase, long double topBase, int n)
{
    long double totalArea = (Function(bottomBase) + Function(topBase))/2.0f;
    
    //long double a = 1.0f; //Function start
    //long double b = 2500000000.0f; //Function end
    //long double n = 2000000000; // Number of trapezes (resolution)

    long double h = (topBase - bottomBase) / n; // Height of the original trapeze

    long double x_i = 0.0f;

    for (int i = 1; i < n; i++)
    {
        x_i = bottomBase + i * h;
        totalArea += Function(x_i);
    }

    /*for (int i = 1; i < n; i++)
        {
            x_i = a + i * h;
            totalArea += Function(x_i);
        }
        //*/

    totalArea *= h;

    totalArea *= h;

    return totalArea;
}

//int n = 1400000000;// Number of trapezes (resolution) -- Serial worst case.
//int n = 720000000; //Number of trapezes (resolution) -- Serial smallest case.

int main(int argc, char* argv[])
{
    std::cout << std::fixed;

    if (argc <= 1)
    {
        std::cout << "You must specify a problem size! Like so:" << "\n";
        std::cout << argv[0] << " <size of problem>" << std::endl;
        return 0;
    }

    long double a = 0.0f; //Function start
    long double b = 200000000.0f; //Function end
    int n = std::stoi(argv[1]); // Number of trapezes (resolution)
               
    long double h = (b - a); // Height of the original trapeze

    long double totalArea = (Function(a) + Function(b))/ 2.0f;

    int my_rank, comm_sz;
    char message[500];

    std::chrono::system_clock::time_point startTime;

    startTime = std::chrono::system_clock::now();

    long double localIntegral = 0.0f;
    long double x_i = 0.0f;
    long double individualH = (h / n);
    for (int i = 0; i < n; i++)
    {
        x_i = a + i * individualH;
        localIntegral += Function(x_i + individualH / 2) * individualH;
    }

    auto endTime = std::chrono::system_clock::now();

    std::chrono::duration<long double> processDuration = endTime - startTime;

    std::cout << "Process duration: " << processDuration.count() << "\n";

    std::cout << "Area: " << std::fixed << localIntegral << "\n";
    std::cout << "Number of trapezes: " << n << std::endl;

    try
    {
        std::ofstream output("Results.csv", std::ofstream::app);

        output << std::fixed << n << " , " << localIntegral << " , " << processDuration.count() << " , " << "SERIAL , 1"  << std::endl;
        output.close();
    }
    catch (const std::exception& exc)
    {
        std::cerr << exc.what() << std::endl;
    }
    

    return 0;
}