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
                        Swap<T>(&values[i - 1], &values[i]);
                    }
                }
            }
            else // Odd phase
            {
                for (int i = 1; i < size - 1; i += 2)
                {
                    if (values[i] > values[i + 1])
                    {
                        Swap<T>(&values[i], &values[i + 1]);
                    }
                }
            }
        }
	}

    template<typename T> void Swap(T* a, T* b)
    {
        /*T temp = *b;
        *b = *a;
        *a = temp;*/
        std::swap(*a, *b);
    }
}