
#include "BitcoinExchange.hpp"



int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: " << av[0] << " <string>" << std::endl;
        return 0;
    }
    std::string str(av[1]);
    // opeing the file
    // parce the file
    // print the result
    BitcoinExchange bitcoinExchange;
    bitcoinExchange.parseFile(str);
    
    return 0;
}