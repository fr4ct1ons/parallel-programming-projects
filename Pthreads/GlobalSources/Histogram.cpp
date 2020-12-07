#include"Histogram.hpp"

Histogram::Histogram()
{
    rangeCount = 0;
}

Histogram::~Histogram()
{
}

void Histogram::AddRange(double range)
{
    ranges.push_back(range);
    amountInRange.push_back(0);
    rangeCount++;
}

void Histogram::Reset()
{
    ranges.clear();
    amountInRange.clear();
    rangeCount = 0;
}

void Histogram::Analyze(double *values, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        double value = values[i];
        for (size_t j = 1; j < rangeCount; j++)
        {
            if(value >= ranges[j - 1] && value < ranges[j])
            {
                amountInRange[j - 1]++;
                continue;
            }
        }
        
    }
}

size_t Histogram::GetRangeCount()
{
    return rangeCount;
}

double Histogram::GetRangeByIndex(long index)
{
    return ranges[index];
}

void Histogram::ForceIncrementRange(long index)
{
    amountInRange[index]++;
}

std::ostream& operator<<(std::ostream &os, const Histogram &hist)
{

    for (size_t i = 1; i < hist.rangeCount; i++)
    {
        if(hist.amountInRange[i - 1] != 0)
        {
            os << hist.ranges[i - 1] << " - " << hist.ranges[i] << ": " << hist.amountInRange[i - 1] << '\n';
        }
    }
    
    return os;
}