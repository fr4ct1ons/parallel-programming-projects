#pragma once

#include<ostream>
#include<vector>

class Histogram
{
private:
    std::vector<float> ranges;
    std::vector<int> amountInRange;

    size_t rangeCount;
public:
    Histogram();
    ~Histogram();
    void AddRange(float);
    void Reset();
    void Analyze(float *, size_t);
    friend std::ostream& Histogram::operator<<(std::ostream &os, const Histogram &hist)
    {

        for (size_t i = 1; i < hist.rangeCount; i++)
        {
            os << hist.ranges[i - 1] << " - " << hist.ranges[i] << ": " << hist.amountInRange[i - 1] << '\n';
        }
        
        return os;
    }
};
