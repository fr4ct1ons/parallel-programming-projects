#include<iostream>

#include"histogram.hpp"

int main(int argc, char const *argv[])
{
    std::cout << "Helo, world!" << std::endl;
    
    Histogram test;

    test.AddRange(0.0f);
    test.AddRange(3.0f);
    test.AddRange(6.0f);
    float values[5] = {1.0f, 1.3f, 2.5f, 4.4f, 4.0f};

    test.Analyze(values, 5);

    std::cout << test << std::endl;
    
    return 0;
}
