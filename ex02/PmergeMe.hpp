#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>



class PmergeMe
{
    private:
        std::vector<int> vec;
        std::vector<int> sortedVec;

    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void parseInput(int ac, char **av);
        void printResults() const;
        void mergeInsertSort(const std::vector<int> &vec);
        std::vector<int> getVector() const;
};


#endif