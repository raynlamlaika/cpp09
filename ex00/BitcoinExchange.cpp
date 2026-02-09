#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) { *this = other; }
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {
        exchangeRates = other.exchangeRates;
    }
    return *this;
}
BitcoinExchange::~BitcoinExchange() {}


static std::map<std::string, double>parceinput(const std::string &line)
{
    std::map<std::string, double> result;
    int i = 0;
    while (!line.empty())
    {
        size_t pos = line.find('\n');
        if (pos == std::string::npos) {break;}
        std::string subline = line.substr(i, pos);
        std::cout << " this is the line that we are on :"<< subline << "\n";
        i = i + pos;
    }
    return result;
}

void BitcoinExchange::parseFile(const std::string &filename)
{
    std::ofstream outFile(filename.c_str());
    std::cout << "file is opened\n";

    if (outFile.is_open())
    {
        // Implementation for writing to the file
        std::string line;
        if (!std::getline(outFile, line)) {std::cout << "Error reading input\n";return;}
        while (std::getline(outFile, line))       
        {
            std::cout << line << std::endl;
            std::string subline = line.substr(0, line.find('\n'));
            if (!std::getline(std::cin, line)) {std::cout << "Error reading input\n";return;}
        }
        this->exchangeRates = parceinput(line);
        outFile.close();
    }
    else {std::cerr << "can't open the reserved file " << filename << "\n";return;}
}