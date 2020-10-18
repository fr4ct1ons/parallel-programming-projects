#pragma once

namespace ArrayAux
{
	template<typename T> void PrintArrayValues(T *values, int valuesSize)
	{
        std::cout << "{ ";
        for (int j = 0; j < valuesSize; j++)
        {
            std::cout << values[j] << " ";
        }
        std::cout << "}" << std::endl;
	}
}