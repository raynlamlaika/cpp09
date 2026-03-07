#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) { *this = other; }
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {this->Database = other.Database;}
    return *this;
}
BitcoinExchange::~BitcoinExchange() {}


bool BitcoinExchange::parceinput(const std::string &line, int i)
{
    std::string date;
    double value;
    // first split the line by |
    size_t pos = line.find('|');
    if (pos == std::string::npos) {std::cout << "Error: invalid format\n"; return false;}
    date = line.substr(0, pos);
    if (i == 0 && date != "date") 
    {
        std::string valueStr = line.substr(pos + 1);
        valueStr.erase(0, valueStr.find_first_not_of(" \t"));
        valueStr.erase(valueStr.find_last_not_of(" \t") + 1);
        if (valueStr != "value") {std::cout << "Error: invalid header\n"; return false;}
        return true;
    }
    else if (i == 0 && date != "date") {std::cout << "Error: invalid header\n"; return false;}
    // parce the date and check if it's valid
    date.erase(0, date.find_first_not_of(" \t"));
    date.erase(date.find_last_not_of(" \t") + 1);
    if (date.empty()) {std::cout << "Error: empty date\n"; return false;}
    // check if the date is in the format YYYY-MM-DD
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {std::cout<< "Error: invalid date format\n"; return false;}
    // check range of year, month and day
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    if (year < 2009 || year > 2024) {std::cout << "Error: year out of range\n"; return false;}
    if (month < 1 || month > 12) {std::cout << "Error: month out of range\n";       return false;}  
    if (day < 1 || day > 31) {std::cout << "Error: day out of range\n"; return false;}

    std::string valueStr = line.substr(pos + 1);
    valueStr.erase(0, valueStr.find_first_not_of(" \t"));
    valueStr.erase(valueStr.find_last_not_of(" \t") + 1);
    for (size_t i = 0; i < valueStr.size(); i++)
    {
        char  c = valueStr[i];
        if (!std::isdigit(c) && c != '.' && c != '-') {std::cout << "Error: invalid value\n"; return false;}
    }

    if (valueStr.empty()) {std::cout << "Error: empty value\n"; return false;}
    try 
    {
        value = std::strtod(valueStr.c_str(), NULL);
        if (value < 0 || value > 1000) {std::cout << "Error: value out of range\n"; return false;}
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: invalid value\n";
        return false;
    }
    std::map<std::string, double>::iterator it = Database.lower_bound(date);
    if (it == Database.end()) {std::cout << "Error: date not found\n"; return false;}
    if (it->first != date && it != Database.begin()) {it--;} // if the date is not found, we use the closest previous date
    std::cout << date << " => " << value << " = " << value * it->second << "\n";
    return true;
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
    std::ifstream inFile(filename.c_str());
    if (inFile.is_open())
    {
        std::string line;
        int i = 0;
        while (std::getline(inFile, line))
        {
            if (!parceinput(line, i)) {;}
            i++;
        }
    }
    else {std::cerr << "can't open the reserved file " << filename << "\n";return;}
}