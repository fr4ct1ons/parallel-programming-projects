#include<omp.h>
#include<cstdio>

int main(int argc, char const *argv[])
{
    int numThreads = 12;

    #pragma omp parallel num_threads(numThreads)
    {
        printf("Hello from process %d \n", omp_get_thread_num());
    }
    return 0;
}