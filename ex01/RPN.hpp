#ifndef RPN_HPP
# define RPN_HPP    
#include <string>
#include <stack>


class RPN 
{
private:
    int operators;
    int tokens;
    std::stack<int> numbers;
public:
    RPN();
    ~RPN();
    RPN& operator=(const RPN &other);
    RPN(const RPN &other);

    void calculate(const std::string &expression);
};


#endif