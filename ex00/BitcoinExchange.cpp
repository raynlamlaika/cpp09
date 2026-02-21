#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) { *this = other; }
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) 
    { // best parctice to check for self assignment, nothing going to happend
        this->Database = other.Database;
    }
    return *this;
}
BitcoinExchange::~BitcoinExchange() {}


void BitcoinExchange::parceinput(const std::string &line)
{
    std::string date;
    double value;

    // first split the line by |
    size_t pos = line.find('|');
    if (pos == std::string::npos) {std::cout << "Error: invalid format\n"; return;}
    date = line.substr(0, pos);
    // parce the date and check if it's valid
    date.erase(0, date.find_first_not_of(" \t"));
    date.erase(date.find_last_not_of(" \t") + 1);
    if (date.empty()) {std::cout << "Error: empty date\n"; return;}
    // check if the date is in the format YYYY-MM-DD
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {std::cout << "Error: invalid date format\n"; return;}

    // std::cout << "date: " << date << "\n";
    // parce the value and check if it's valid
    std::string valueStr = line.substr(pos + 1);
    valueStr.erase(0, valueStr.find_first_not_of(" \t"));
    valueStr.erase(valueStr.find_last_not_of(" \t") + 1);
    if (valueStr.empty()) {std::cout << "Error: empty value\n"; return;}
    try 
    {
        value = std::strtod(valueStr.c_str(), NULL);
        if (value < 0 || value > 1000) {std::cout << "Error: value out of range\n"; return ;}
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: invalid value\n";
        return;
    }
    // std::cout << "value: " << std::fixed << value << "\n";
    // back to andel the error message like the example in the subject
    std::map<std::string, double>::iterator it = Database.lower_bound(date);
    if (it == Database.end()) {std::cout << "Error: date not found\n"; return;}
    if (it->first != date && it != Database.begin()) {it--;} // if the date is not found, we use the closest previous date
    std::cout << date << " => " << value << " = " << value * it->second << "\n";
    return;
}
std::map<std::string, double> DatabaseLoader()
{
    std::map<std::string, double> Database;
    std::ifstream inFile("data.csv");
    if (inFile.is_open())
    {
        std::string line;
        while (std::getline(inFile, line))
        {
            size_t pos = line.find(',');
            if (pos == std::string::npos) {std::cerr << "Error: invalid format in data.csv\n"; continue;}
            std::string date = line.substr(0, pos);
            double value = std::strtod(line.substr(pos + 1).c_str(), NULL);
            Database[date] = value;
        }
    }
    else {std::cerr << "Error: can't open data.csv\n";}
    return Database;
}

void BitcoinExchange::parseFile(const std::string &filename)
{
    this->Database = DatabaseLoader();
    // std::map<std::string, double>::iterator it = Database.begin();
    // while (it != Database.end())
    // {
    //     std::cout << "date: " << it->first << " value: " << it->second << "\n";
    //     it++;
    // }
    std::ifstream inFile(filename.c_str());
    if (inFile.is_open())
    {
        std::cout << "file is opened\n";
        // readds the file line by line and parce it
        std::string line;
        while (std::getline(inFile, line))
        {
            // std::cout << " this is the line that we are on :"<< line << "\n";
            parceinput(line);
        }
    }
    else {std::cerr << "can't open the reserved file " << filename << "\n";return;}
}