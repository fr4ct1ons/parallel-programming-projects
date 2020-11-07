#pragma once

#include<cstdlib>
#include<sstream>

template<typename T> class Matrix
{
private:
    size_t columns = 0, lines = 0;
public:
    T **data;

    Matrix(size_t newLines=1, size_t newColumns=1)
    {
        columns = newColumns;
        lines = newLines;
        data = new T*[lines];
        
        for (size_t i = 0; i < lines; i++)
        {
            data[i] = new T[columns];
        }
    }

    inline size_t Lines() {return lines;}

    inline size_t Columns() {return columns;}

    std::string ToString()
    {
        std::stringstream os;

        for (size_t i = 0; i < lines; i++)
        {
            os << "[ ";
            for (size_t j = 0; j < columns - 1; j++)
            {
                os << data[i][j] << ", ";
            }
            os << data[i][columns - 1] << " ] \n";
        }
        
        return os.str();
    }

    Matrix &operator=(Matrix &other)
    {
        lines = other.Lines();
        columns = other.Columns();

        data = new T*[lines];
        for (size_t i = 0; i < lines; i++)
        {
            data[i] = new T[columns];
        }

        return *this;
    }

    void Reset(size_t newLines, size_t newColumns)
    {
        for (size_t i = 0; i < lines; i++)
        {
            delete[] data[i];
        }

        delete[] data;

        columns = newColumns;
        lines = newLines;
        data = new T*[lines];
        
        for (size_t i = 0; i < lines; i++)
        {
            data[i] = new T[columns];
        }
    }

    static Matrix Srl_mat_mul(Matrix multA, Matrix multB)
    {
        Matrix result(multA.Lines, multB.Columns());

        for (size_t i = 0; i < multA.Lines(); i++)
        {
            for (size_t j = 0; j < multB.Columns(); j++)
            {
                result.data[i][j] = 0.0;
                for (size_t k = 0; k < multA.Columns(); ++k)
                {
                    result.data[i][j] += multA.data[i][k] * multB.data[k][j];
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
        return NULL;
    }
};

void PopulateRandom(unsigned int seed, Matrix<double> *populated, int min=1.0, int max=1000.0)
{
    srand(seed);

    for (size_t i = 0; i < populated->Lines(); i++)
    {
        for (size_t j = 0; j < populated->Columns(); j++)
        {
            populated->data[i][j] = (double) (min + rand() % max);
        }
    }
}
