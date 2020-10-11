#include<iostream>
#include"mpi.h"
#include<string>
#include<cmath>
#include<chrono>
#include<cstdio>

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

//long double b = 2500000000.0f;//Function end -- Serial worst case.
//int n = 1680000000;// Number of trapezes (resolution) -- Serial worst case.

//long double a = 0.0f; //Function start -- Square.
//long double b = 20.0f; //Function end
//long double n = 20; // Number of trapezes (resolution)

int main()
{
    std::cout << std::fixed;

    long double a = 0.0f; //Function start
    long double b = 200000000.0f; //Function end
    int n = 1400000000; // Number of trapezes (resolution)
               
    long double h = (b - a); // Height of the original trapeze

    long double totalArea = (Function(a) + Function(b))/ 2.0f;

    int my_rank, comm_sz;
    char message[500];

    std::chrono::system_clock::time_point startTime;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank != 0) // Is not master
    {
        startTime = std::chrono::system_clock::now();
    }

    int localN = n/comm_sz;

    /*if (my_rank == comm_sz - 1)
    {
        long double divRemain = fmod((long double)n, comm_sz);
        std::cout << "Division remain: " << divRemain << "\n";
        localN += (int)divRemain;
    }*/

    long double localH = h / (long double)comm_sz; //Height of each process' trapeze
    long double individualH = (h/n);
        
    long double localA = a + my_rank * localN * h;

    /*
    std::cout << "------" << "\n";
    std::cout << "Comm_SZ: " << comm_sz << "\n";
    std::cout << "My_Rank: " << my_rank << "\n";
    std::cout << "A: " << a << "\n";
    std::cout << "B: " << b << "\n";
    std::cout << "N: " << n << "\n";
    std::cout << "H: " << h << "\n";
    std::cout << "LocalN: " << localN << "\n";
    std::cout << "LocalA: " << localA << "\n";
    std::cout << "LocalH: " << localH << "\n";
    std::cout << "IndividualH: " << individualH << "\n";
    //*/

    long double localIntegral = 0.0f;
    long double x_i = 0.0f;
    for (int i = 0; i < localN; i++)
    {
        x_i = localA + i * individualH;
        localIntegral += Function(x_i + individualH / 2) * individualH;

        /*
        bottomBase = Function(localA + (i * individualH));
        topBase = Function(localA + ((i + 1) * individualH));

        localIntegral += ((topBase + bottomBase) * individualH) / 2; // TrapezeArea(bottomBase, topBase, individualH);
        std::cout << localIntegral / 2 << "\n";*/ //std::cout << localIntegral << "\n";
    }

    //std::cout << "LocalIntegral: " << localIntegral << "\n";
    //std::cout << "------" << std::endl;

    if (my_rank != 0) // Is not master
    {
        MPI_Send(&localIntegral, 1, MPI_LONG_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    else // Is master
    {
        long double totalIntegral = localIntegral;
        long double newIntegral = 0.0f;
        for (int proc = 1; proc < comm_sz; proc++)
        {
            MPI_Recv(&newIntegral, 1, MPI_LONG_DOUBLE, proc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            //std::cout << "New integral for process " << proc << " is: " << newIntegral << std::endl;
            totalIntegral += newIntegral;
        }

        auto endTime = std::chrono::system_clock::now();

        std::chrono::duration<long double> processDuration = endTime - startTime;

        std::cout << "Process duration: " << processDuration.count() << "\n";

        std::cout << "Area: " << std::fixed << totalIntegral << std::endl;
    }
    MPI_Finalize();
    return 0;
    

    return 0;
}

/*if (my_rank != 0)
{

    std::cout << "Greetings! I am number " + std::to_string(my_rank) + ".";

    strcpy(message, "Process something here.");

    if (my_rank == 1)
    {
        strcpy(message, "PROCESS 2 REPORTING FOR DUTY!");
    }
    else if (my_rank == 2)
    {
        strcpy(message, "Process 3 here.");
    }
    std::cout << "Sending." << std::endl;
    MPI_Send(message, 500, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    std::cout << "Sent" << std::endl;
}
else
{
    int size;
    MPI_Status status;

    strcpy(message, "Greetings! I am number 0.");
    std::cout << message << std::endl;

    for (int procNum = 1; procNum < comm_sz ; procNum++)
    {
        MPI_Recv(message, 500, MPI_CHAR, procNum, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << message << std::endl;
    }
}*/
