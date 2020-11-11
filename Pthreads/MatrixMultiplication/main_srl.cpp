#include<iostream>
#include<cstdio>
#include<chrono>

#include"Matrix.hpp"

int threadCount = 4;
int runningThreads;
bool* threadFinished;

void Srl_MatMul_double(Matrix<double> multA, Matrix<double> multB, Matrix<double> &OUT_result)
{
    for (size_t i = 0; i < multA.Lines(); i++)
    {
        for (size_t j = 0; j < multB.Columns(); j++)
        {
            OUT_result.data[i][j] = 0.0;
            for (size_t k = 0; k < multA.Columns(); ++k)
            {
                OUT_result.data[i][j] += multA.data[i][k] * multB.data[k][j];
            }
        }
        
    }

    /*for (size_t i = firstLine; i <= lastLine; i++)
    {
        result.data[i][0] = 0.0;
        //printf("Thread %d reporting: result.data[%d][0] equals %d BEFORE operation.\n", rank, i, result.data[i][0]);
        for (size_t j = 0; j < multA.Columns(); j++)
        {
            result.data[i][0] += multA.data[i][j] * multB.data[j][0];
        }
        //printf("Thread %d reporting: result.data[%d][0] equals %d AFTER operation.\n", rank, i, result.data[i][0]);
    }*/
}

bool isAllTrue(bool *val, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if(!val[i])
        {
            //std::cout << "Loop" << std::endl;
            return false;
        }
    }
    return true;
}

void Srl_MatMulDumb_double(Matrix<double> multA, Matrix<double> multB, Matrix<double> &OUT_result)
{
    srand(13);
    for (size_t i = 0; i < multA.Lines(); i++)
    {
        for (size_t j = 0; j < multB.Columns(); j++)
        {
            OUT_result.data[i][j] = 0.0;
            bool *wasSaved = new bool[OUT_result.Lines()];
            for (size_t temp = 0; temp < OUT_result.Lines(); temp++)
            {
                wasSaved[temp] = false;
            }
            
            while(!isAllTrue(wasSaved, OUT_result.Lines()))
            {
                int k = 0;
                do
                {
                    k = rand() % OUT_result.Lines();
                } while(wasSaved[k]);

                OUT_result.data[i][j] += multA.data[i][k] * multB.data[k][j];
                wasSaved[k] = true;
            }
        }
        
    }

    /*for (size_t i = firstLine; i <= lastLine; i++)
    {
        result.data[i][0] = 0.0;
        //printf("Thread %d reporting: result.data[%d][0] equals %d BEFORE operation.\n", rank, i, result.data[i][0]);
        for (size_t j = 0; j < multA.Columns(); j++)
        {
            result.data[i][0] += multA.data[i][j] * multB.data[j][0];
        }
        //printf("Thread %d reporting: result.data[%d][0] equals %d AFTER operation.\n", rank, i, result.data[i][0]);
    }*/
}

int main(int argc, char const *argv[])
{
    std::cout << std::fixed;

    const int problemSize = 4 * 80;

    Matrix<double> multA(problemSize, problemSize);
    Matrix<double> multB(problemSize, problemSize);

    Matrix<double> result;

    if(multA.Columns() != multB.Lines())
    {
        std::cout << "INVALID MATRIX SIZE! Make sure that multA's columns size equals multB's lines size." << std::endl;
        return 1;
    }

    result.Reset(multA.Lines(), multB.Columns());

    PopulateRandom(11, &multA, 2, 1);
    PopulateRandom(12, &multB, 2, 1);
    PopulateRandom(10, &result, 2, 1);
    
    //std::cout << "Current values in multA: \n" << multA.ToString() << std::endl;
    //std::cout << "Current values in multB: \n" << multB.ToString() << std::endl;

    std::cout << "Current values in result: \n" << result.ToString() << std::endl;

    auto startTime = std::chrono::system_clock::now();

    Srl_MatMulDumb_double(multA, multB, result);
    
    auto endTime = std::chrono::system_clock::now();

    std::chrono::duration<long double> processDuration = endTime - startTime;

    //std::cout << "Process duration: " << processDuration.count() << "\n";

    std::cout << "Finished multiplication. Current values in result: \n" << result.ToString() << std::endl;

    std::cout << "Finished multiplication. Duration: " << processDuration.count() << std::endl;

    return 0;
}
