#include "RPN.hpp"
#include <iostream>
#include <iomanip>
RPN::RPN() {}
RPN::~RPN() {}

RPN& RPN::operator=(const RPN &other)
{
    if (this != &other)
        ;
    return *this;
}

RPN::RPN(const RPN &other) {*this= other;}

void RPN::calculate(const std::string &expression)
{
    int operators = 0;
    int tokens = 0;
    for(size_t i = 0; i < expression.length(); i++)
    {
        char c = expression[i];
        if (c != ' ' && c != '+' && c != '-' && c != '*' && c != '/' && (c < '0' || c > '9'))
        {
            std::cerr << "Error: invalid character '" << c << "'\n";
            return ;
        }
        if (c == ' ')
            continue;
        if (c >= '0' && c <= '9')
        {
            if (expression[i +1] != ' ' && expression[i +1] != '\0')
            {
                std::cerr << "Error: invalid expression\n";
                return ;
            }
            tokens++;
            this->tokens++;
            numbers.push(c - '0');
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            if (expression[i +1] != ' ' && expression[i +1] != '\0')
            {
                std::cerr << "Error: invalid expression\n";
                return ;
            }
            operators++;
            this->operators++;
            if (numbers.size() < 2)
            {
                std::cerr << "Error: insufficient operands\n";
                return ;
            }
            double b = numbers.top();
            numbers.pop();
            double a = numbers.top();
            numbers.pop();
            if (c == '+')
                numbers.push(a + b);
            else if (c == '-')
                numbers.push(a - b);
            else if (c == '*')
                numbers.push(a * b);
            else if (c == '/')
            {
                if (b == 0)
                {
                    std::cerr << "Error: division by zero\n";
                    numbers.pop();
                    return ;
                }
                numbers.push(a / b);
            }
        }
    }
    if (operators != tokens - 1)
    {
        std::cerr << "Error: invalid expression\n";
        return ;
    }

    std::cout <<  std::fixed  << std::setprecision(0) << numbers.top() << " " << "\n";
    numbers.pop();
}

