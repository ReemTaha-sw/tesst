#include "BitcoinExchange.hpp"

int main(int argc, char** argv)
{
    if (argc != 2)
	{
        std::cerr << "Error: Wrong argc." << std::endl;
        return 1;
    }
	BitcoinExchange exchange;
	if(!exchange.parseDataFile("data.csv"))
        return 1;
	if(!exchange.getRates(argv[1]))
        return 1;
    return 0;
}
