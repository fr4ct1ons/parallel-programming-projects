#pragma once


namespace SortingAlgorithms 
{

	template<typename T> void OddEvenTranspositionSort(T* values, int size)
	{
        for (int phase = 0; phase < size; phase++)
        {
            if (phase % 2 == 0) // Even phase
            {
                for (int i = 1; i < size; i += 2)
                {
                    if (values[i - 1] > values[i])
                    {
                        std::swap(values[i - 1], values[i]);
                    }
                }
            }
            else // Odd phase
            {
                for (int i = 1; i < size - 1; i += 2)
                {
                    if (values[i] > values[i + 1])
                    {
                        std::swap(values[i], values[i + 1]);
                    }
                }
            }
        }
	}
}