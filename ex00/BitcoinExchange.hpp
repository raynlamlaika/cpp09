#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <iostream>
#include <fstream>
#include <stdlib.h>

class BitcoinExchange
{
    private:
        std::map<std::string, double> Database;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void parseFile(const std::string &filename);
        void printResults() const;
        void parceinput(const std::string &line);
};

#endif