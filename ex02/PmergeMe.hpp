#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <deque>

class PmergeMe
{
    private:
        std::vector<int> vec;
        std::vector<int> sortedVec;
        std::deque<int> deqsort;
        std::deque<int> sortedDeq;

    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void parseInputVec(int ac, char **av);
        void parseInputDQ(int ac, char **av);
        void printResults(int i) const;
        // void mergeInsertSort(const std::vector<int> &vec);
        void sortVector(const std::vector<int> &vec);
        void sortDeque(const std::deque<int> &deq);
        std::vector<int> getVector() const;
        std::deque<int> getDeque() const;
};

#endif