#include"testingAux.h"

namespace TestingAux
{
	void WriteToResults(std::stringstream& os)
	{
        try
        {
            std::ofstream output("Results.csv", std::ofstream::app);

            output << std::fixed << os.str();
            output.close();
        }
        catch (const std::exception& exc)
        {
            std::cerr << exc.what() << std::endl;
        }
	}
}