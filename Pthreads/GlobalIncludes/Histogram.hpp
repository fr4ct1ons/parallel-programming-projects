#pragma once

#include<ostream>
#include<vector>

class Histogram
{
private:
    std::vector<double> ranges;
    std::vector<long> amountInRange;
    
    size_t rangeCount;
public:
    Histogram();
    ~Histogram();
    void AddRange(double);
    void Reset();
    void Analyze(double *, size_t);
    size_t GetRangeCount();
    double GetRangeByIndex(long);
    void ForceIncrementRange(long);

    friend std::ostream& operator<<(std::ostream &os, const Histogram &hist);
};
