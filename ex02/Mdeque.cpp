#include "PmergeMe.hpp"


void PmergeMe::parseInputDQ(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
        int num;
        std::istringstream iss(av[i]);
        if (!(iss >> num)) {
            std::cerr << "Error: invalid number\n";
            throw std::invalid_argument("Invalid number");
        }
        if (num < 0) {
            std::cerr << "Error: negative number\n";
            throw std::invalid_argument("Negative number");
        }
        deqsort.push_back(num);
    }
}

static void spliter(const std::deque<int> &deqsort, std::deque<int> &larger, std::deque<int> &smaller, int &unpaired)
{
    for (size_t i = 0; i < deqsort.size(); i++)
    {
        if (i + 1 < deqsort.size())
        {
            if (deqsort[i] > deqsort[i + 1])
            {
                larger.push_back(deqsort[i]);
                smaller.push_back(deqsort[i + 1]);
            }
            else
            {
                larger.push_back(deqsort[i + 1]);
                smaller.push_back(deqsort[i]);
            }
            i++;
        }
        else
            unpaired = deqsort[i];
    }
}

static void RealSorting(std::deque<int> &holders)
{
    if (holders.size() <= 1)
        return;

    std::deque<int> larger;
    std::deque<int> smaller;
    int unpaired = -1;
    size_t n = holders.size();
    if (n % 2 == 1)
        unpaired = holders[n - 1];

    spliter(holders, larger, smaller, unpaired);

    // sort only the larger chain recursively
    RealSorting(larger);

    std::deque<int> result = larger;
    for (size_t i = 0; i < smaller.size(); i++)
    {
        std::deque<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), smaller[i]);
        result.insert(pos, smaller[i]);
    }

    if (unpaired != -1)
    {
        std::deque<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), unpaired);
        result.insert(pos, unpaired);
    }

    holders = result;
}

int jacobsthal(int k)
{
    if (k == 0)
        return 0;
    if (k == 1)
        return 1;
    return jacobsthal(k - 1) + 2 * jacobsthal(k - 2);
}

void PmergeMe::sortDeque(const std::deque<int> &deq)
{
    if (deq.size() <= 1)
        return;

    std::deque<int> larger, smaller;
    int unpaired = -1;
    size_t n = deq.size();
    if (n % 2 == 1)
        unpaired = deq[n - 1];

    spliter(deq, larger, smaller, unpaired);

    // sort only the larger chain recursively
    RealSorting(larger);

    // Jacobsthal controls insertion ORDER to minimise comparisons.
    // Actual insertion POSITION is always via lower_bound (binary search).
    // shity -------------------------------------------- part


    // add the deque 
    std::deque<int> insertOrder;
    // std::deque <int> insertingOrder;
    int prev = 0;

    for (int k = 2; ; k++) // start in infinit loop
    {
        int jac = jacobsthal(k);
        int end = (jac < (int)smaller.size()) ? jac - 1 : (int)smaller.size() - 1;
        // for (int idx = end; idx >= prev; idx--)
        //     insertOrder.push_back(idx);
        for (int idx = end; idx >= prev; idx--)
            insertOrder.push_back(idx);
        prev = jac;
        if (prev >= (int)smaller.size())
            break;
    }

    std::deque<int> result = larger;
    for (size_t i = 0; i < insertOrder.size(); i++)
    {
        std::deque<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), smaller[insertOrder[i]]);
        result.insert(pos, smaller[insertOrder[i]]); // binary search insertion
    }
    if (unpaired != -1)
    {
        std::deque<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), unpaired);
        result.insert(pos, unpaired);
    }
    sortedDeq = result;


}
