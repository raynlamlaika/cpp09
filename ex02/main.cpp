#include "PmergeMe.hpp"



#include <iomanip>

#include <cmath>

extern int total;

int F(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

int main(int ac, char **av)
{
    total = 0;
    if (ac < 2) {std::cerr << "Usage: " << av[0] << " <numbers...>" << std::endl; return 0;}

    PmergeMe pmergeMe;
    try {pmergeMe.parseInputVec(ac, av);}
    catch(const std::exception& e) {return 1;}
    clock_t start = clock();
    pmergeMe.sortVector(pmergeMe.getVector());
    // std::cout << " greed:"<<  F(pmergeMe.getVector().size()) << std::endl;
    // std::cout << " total:"<<  total << std::endl;
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    pmergeMe.printResults(0);
    
    try {pmergeMe.parseInputDQ(ac, av);}
    catch(const std::exception& e) {return 1;}
    clock_t start2 = clock();
    pmergeMe.sortDeque(pmergeMe.getDeque());
    clock_t end2 = clock();
    double elapsed2 = double(end2 - start2) / CLOCKS_PER_SEC;
    std::cout << std::fixed << "Time taken Vec: " << elapsed << " seconds" << std::endl;
    std::cout << std::fixed << "Time taken DQ: " << elapsed2 << " seconds" << std::endl;
    pmergeMe.printResults(1);

    return 0;
}