#include"Histogram.hpp"

Histogram::Histogram()
{
    rangeCount = 0;
}

Histogram::~Histogram()
{
}

void Histogram::AddRange(float range)
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

void Histogram::Analyze(float *values, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        float value = values[i];
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

/*std::ostream& Histogram::operator<<(std::ostream &os, const Histogram &hist)
{

    for (size_t i = 1; i < hist.rangeCount; i++)
    {
        os << hist.ranges[i - 1] << " - " << hist.ranges[i] << ": " << hist.amountInRange[i - 1] << '\n';
    }
    
    return os;
}*/