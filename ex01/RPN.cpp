#include "RPN.hpp"
#include <iostream>

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
            this->tokens++;
            numbers.push(c - '0');
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            this->operators++;
            if (numbers.size() < 2)
            {
                std::cerr << "Error: insufficient operands\n";
                return ;
            }
            int b = numbers.top();
            numbers.pop();
            int a = numbers.top();
            numbers.pop();
            if (c == '+')
                numbers.push(a + b);
            else if (c == '-')
                numbers.push(a - b);
            else if (c == '*')
                numbers.push(a * b);
            else if (c == '/')
                numbers.push(a / b);
        }
    }
    std::cout << numbers.top() << "\n";
    
}






