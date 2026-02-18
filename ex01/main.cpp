#include "RPN.hpp"
#include <iostream>


int main(int ac, char **av)
{
    if (ac != 2) {std::cerr << "Usage: " << av[0] << " <string>" << std::endl; return 0;}
    std::string str(av[1]);
    RPN rpn;
    rpn.calculate(str);
    
    return 0;
}