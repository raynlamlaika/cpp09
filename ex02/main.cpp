#include "PmergeMe.hpp"



int main(int ac, char **av)
{
    if (ac < 2) {std::cerr << "Usage: " << av[0] << " <numbers...>" << std::endl; return 0;}
    
    // first is to add the clock fom the first to the end
    clock_t start = clock();
    PmergeMe pmergeMe;
    try {pmergeMe.parseInput(ac, av);}
    catch(const std::exception& e) {return 1;}
    pmergeMe.mergeInsertSort(pmergeMe.getVector());
    pmergeMe.printResults();
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    std::cout << std::fixed << "Time taken: " << elapsed << " seconds" << std::endl;

    return 0;
}