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

    template<typename T> T* JoinArrays(T* arrayLeft, T* arrayRight, int arrayLeftSize, int arrayRightSize)
    {
        T* toReturn = new T[arrayLeftSize + arrayRightSize];
        std::memcpy(toReturn, arrayLeft, sizeof(T) * arrayLeftSize);
        std::memcpy(toReturn + arrayLeftSize, arrayRight, sizeof(T) * arrayRightSize);

        return toReturn;
    }
}