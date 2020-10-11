#include<stdio.h>
#include"mpi.h"
#include<math.h>
#include<time.h>

float Function(float x)
{
    return 2.0f;
    //return sin(x) + 2.5f;
}

float TrapezeArea(float bottomBase, float topBase, float height)
{
    return ((topBase + bottomBase) * height)/2;
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

//float b = 2500000000.0f;//Function end -- Serial worst case.
//int n = 1680000000;// Number of trapezes (resolution) -- Serial worst case.

//float a = 0.0f; //Function start -- Square.
//float b = 20.0f; //Function end
//float n = 20; // Number of trapezes (resolution)

int main()
{
    int isParallel = 0;

    float a = 0.0f; //Function start
    float b = 20000000000.0f; //Function end
    int n =   20; // Number of trapezes (resolution)
               
    float h = (b - a); // Height of the original trapeze

    float x_i = 0.0f;

    float totalArea = (Function(a) + Function(b))/ 2.0f;

    int my_rank, comm_sz;
    char message[500];

    clock_t startTime;

    if (isParallel)
    {
        startTime = clock();

        MPI_Init(NULL, NULL);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        int localN = n/comm_sz;

        /*if (my_rank == comm_sz - 1)
        {
            float divRemain = fmod((float)n, comm_sz);
            std::cout << "Division remain: " << divRemain << "\n";
            localN += (int)divRemain;
        }*/

        float localH = h / (float)comm_sz; //Height of each process' trapeze
        float individualH = (h/n);
        
        float localA = a + my_rank * localN * h;

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

        float localIntegral = 0.0f;
        float bottomBase = 0.0f, topBase = 0.0f;
        float x_i = 0.0f;
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

        printf("LocalIntegral: %f \n", localIntegral);
        printf("------ \n");

        if (my_rank != 0) // Is not master
        {
            MPI_Send(&localIntegral, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
        }
        else // Is master
        {
            float totalIntegral = localIntegral;
            float newIntegral = 0.0f;
            for (int proc = 1; proc < comm_sz; proc++)
            {
                MPI_Recv(&newIntegral, 1, MPI_FLOAT, proc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                std::cout << "New integral for process " << proc << " is: " << newIntegral << std::endl;
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
