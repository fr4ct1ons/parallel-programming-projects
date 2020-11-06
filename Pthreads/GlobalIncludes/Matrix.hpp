#pragma once

#include<cstdlib>
#include<sstream>

template<typename T> class Matrix
{
private:
    size_t columns = 0, lines = 0;
public:
    T **data;

    Matrix(size_t newColumns, size_t newLines)
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
