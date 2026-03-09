#include "PmergeMe.hpp"



PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &other) : vec(other.vec), sortedVec(other.sortedVec) {}
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vec = other.vec;
        sortedVec = other.sortedVec;
    }
    return *this;
}
PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(int ac, char **av)
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
        vec.push_back(num);
    }
}

static void spliter(const std::vector<int> &vec, std::vector<int> &larger, std::vector<int> &smaller, int &unpaired)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (i + 1 < vec.size())
        {
            if (vec[i] > vec[i + 1])
            {
                larger.push_back(vec[i]);
                smaller.push_back(vec[i + 1]);
            }
            else
            {
                larger.push_back(vec[i + 1]);
                smaller.push_back(vec[i]);
            }
            i++;
        }
        else
            unpaired = vec[i];
    }
}

static void RealSorting(std::vector<int> &holders)
{
    if (holders.size() <= 1)
        return;

    std::vector<int> larger;
    std::vector<int> smaller;
    int unpaired = -1;

    spliter(holders, larger, smaller, unpaired);

    // recursive step: only sort the larger chain
    RealSorting(larger);

    std::vector<int> result = larger;

    // insert smaller elements using binary search
    result.insert(result.begin(), smaller[0]);
    for (size_t i = 1; i < smaller.size(); i++)
    {
        std::vector<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), smaller[i]);
        result.insert(pos, smaller[i]);
    }

    if (unpaired != -1)
    {
        std::vector<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), unpaired);
        result.insert(pos, unpaired);
    }

    holders = result;
}

static int jacopstal(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return jacopstal(n - 1) + 2 * jacopstal(n - 2);
}

void PmergeMe::mergeInsertSort(const std::vector<int> &vec)
{
    if (vec.size() <= 1)
        return;

    std::vector<int> larger, smaller;
    int unpaired = -1;
    size_t n = vec.size();
    if (n % 2 == 1)
        unpaired = vec[n - 1];

    spliter(vec, larger, smaller, unpaired);

    // sort only the larger chain recursively
    RealSorting(larger);

    // Jacobsthal controls insertion ORDER to minimise comparisons.
    // Actual insertion POSITION is always via lower_bound (binary search).
    // shity -------------------------------------------- part


    // add the deque 
    // std::vector<int> insertOrder;
    std::deque <int> insertingOrder;
    int prev = 0;

    for (int k = 2; ; k++) // start in infinit loop
    {
        int jac = jacopstal(k);
        int end = (jac < (int)smaller.size()) ? jac - 1 : (int)smaller.size() - 1;
        // for (int idx = end; idx >= prev; idx--)
        //     insertOrder.push_back(idx);
        for (int idx = end; idx >= prev; idx--)
            insertingOrder.push_back(idx);
        prev = jac;
        if (prev >= (int)smaller.size())
            break;
    }

    std::vector<int> result = larger;
    for (size_t i = 0; i < insertingOrder.size(); i++)
    {
        std::vector<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), smaller[insertingOrder[i]]);
        result.insert(pos, smaller[insertingOrder[i]]); // binary search insertion
    }
    if (unpaired != -1)
    {
        std::vector<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), unpaired);
        result.insert(pos, unpaired);
    }
    sortedVec = result;
}

void PmergeMe::printResults() const
{
    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << "\nAfter: ";
    for (size_t i = 0; i < sortedVec.size(); i++)
        std::cout << sortedVec[i] << " ";
    std::cout << "\n";
}

std::vector<int> PmergeMe::getVector() const { return vec; }
