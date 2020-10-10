#include<iostream>
#include"mpi.h"
#include<string>
#include<cmath>
#include<chrono>
#include<cstdio>

float Function(float x)
{
    return sin(x) + 2.5f;
}

float TrapezeArea(float bottomBase, float topBase, float height)
{
    return (topBase + bottomBase) * height/2;
}

float TrapezeAreaPerProcess(float bottomBase, float topBase, int n)
{
    float totalArea = (Function(bottomBase) + Function(topBase))/2.0f;
    
    //float a = 1.0f; //Function start
    //float b = 2500000000.0f; //Function end
    //float n = 2000000000; // Number of trapezes (resolution)

    float h = (topBase - bottomBase) / n; // Height of the original trapeze

    float x_i = 0.0f;

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

//float b = 2500000000.0f; //Function end -- Serial worst case.
//float n = 2000000000; // Number of trapezes (resolution) -- Serial worst case.

int main()
{
    std::cout << std::fixed;
    bool isParallel = !false;

    //std::cout << "Is parallel: " << isParallel << std::endl;

    float a = 1.0f; //Function start
    float b = 280000000.0f; //Function end
    float n = (16666661 * 12); // Number of trapezes (resolution)
    //std::cout << "LocalN: " << std::fixed << n << std::endl;

    float h = (b - a) / n; // Height of the original trapeze
    //std::cout << std::fixed <<"H: " << h << std::endl;

    float x_i = 0.0f;

    float totalArea = (Function(a) + Function(b))/ 2.0f;

    int my_rank, comm_sz;
    char message[500];

    std::chrono::system_clock::time_point startTime;

    if (isParallel)
    {
        startTime = std::chrono::system_clock::now();

        MPI_Init(NULL, NULL);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        //std::cout << "Number of processes: " << comm_sz << std::endl;

        int localN = n/ static_cast<float>(comm_sz);
        float localA = static_cast<float>(a + static_cast<float>(my_rank) * static_cast<float>(localN) * static_cast<float>(h));
        float localB = static_cast<float>(localA + static_cast<float>(localN) * static_cast<float>(h));

        /*
        std::cout << "------" << "\n";
        std::cout << "Comm_SZ: " << comm_sz << "\n";
        std::cout << "My_Rank: " << my_rank << "\n";
        std::cout << "A: " << a << "\n";
        std::cout << "H: " << h << "\n";
        std::cout << "LocalN: " << localN << "\n";
        std::cout << "LocalA: " << std::fixed << localA << "\n";
        std::cout << "LocalB: " << std::fixed << localB << "\n";
        std::cout << "------" << std::endl;
        //f(localA);*/

        float localIntegral = (Function(localA) + Function(localB)) / 2.0f;

        for (int i = 1; i < localN; i++)
        {
            x_i = localA + i * h;
            localIntegral += Function(x_i);
        }
        localIntegral *= h;

        if (my_rank != 0) // Is not master
        {
            MPI_Send(&localIntegral, sizeof(float), MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
        }
        else // Is master
        {
            float totalIntegral = localIntegral;
            float newIntegral = 0.0f;
            for (int proc = 1; proc < comm_sz; proc++)
            {
                MPI_Recv(&newIntegral, sizeof(float), MPI_FLOAT, proc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                totalIntegral += newIntegral;
            }

            auto endTime = std::chrono::system_clock::now();

            std::chrono::duration<float> processDuration = endTime - startTime;

            std::cout << "Process duration: " << processDuration.count() << "\n";

            std::cout << "Area: " << std::fixed << totalIntegral << std::endl;
        }
        MPI_Finalize();
        return 0;
    }
    else
    {
        startTime = std::chrono::system_clock::now();

        for (int i = 1; i < n; i++)
        {
            x_i = a + i * h;
            totalArea += Function(x_i);
        }
        //*/

        totalArea *= h;

        auto endTime = std::chrono::system_clock::now();

        std::chrono::duration<float> processDuration = endTime - startTime;

        std::cout << "Process duration: " << std::fixed << processDuration.count() << "\n";

        std::cout << "Area: " << totalArea << std::endl;
    }

    

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
