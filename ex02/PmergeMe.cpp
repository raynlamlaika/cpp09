#include "PmergeMe.hpp"


PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &other) : vec(other.vec),  sortedVec(other.sortedVec),deqsort(other.deqsort), sortedDeq(other.sortedDeq) {} // check why the order is matters
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vec = other.vec;
        deqsort = other.deqsort;
        sortedVec = other.sortedVec;
        sortedDeq = other.sortedDeq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}


static int jacobsthal(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

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

static void spliterDq(const std::deque<int> &deqsort, std::deque<int> &larger, std::deque<int> &smaller, int &unpaired)
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

static void RealSortingDq(std::deque<int> &holders)
{
    if (holders.size() <= 1)
        return;

    std::deque<int> larger;
    std::deque<int> smaller;
    int unpaired = -1;

    spliterDq(holders, larger, smaller, unpaired);
    RealSortingDq(larger);

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

void PmergeMe::sortDeque(const std::deque<int> &deq)
{
    if (deq.size() <= 1)
        {std::cout << "Already sorted or empty deque.\n"; return;}

    std::deque<int> larger, smaller;
    int unpaired = -1;
    size_t n = deq.size();
    if (n % 2 == 1)
        unpaired = deq[n - 1];

    spliterDq(deq, larger, smaller, unpaired);
    RealSortingDq(larger);

    std::deque<int> insertOrder;

    int prev = 0;

    for (int k = 2; ; k++) // start in infinit loop
    {
        int jac = jacobsthal(k);int end = jac - 1;
        if (end >= static_cast<int>(smaller.size()))
            end = static_cast<int>(smaller.size()) - 1;

        for (int idx = end; idx >= prev; idx--)
            insertOrder.push_back(idx);
        prev = jac;
        if (prev >= (int)smaller.size())break;
    }
    std::deque<int> result = larger;
    for (size_t i = 0; i < insertOrder.size(); i++)
    {
        std::deque<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), smaller[insertOrder[i]]);
        result.insert(pos, smaller[insertOrder[i]]);
    }
    if (unpaired != -1)
    {
        std::deque<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), unpaired);
        result.insert(pos, unpaired);
    }
    sortedDeq = result;
}

void PmergeMe::parseInputVec(int ac, char **av)
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
    RealSorting(larger);
    std::vector<int> result = larger;

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

void PmergeMe::sortVector(const std::vector<int> &vec)
{
    if (vec.size() <= 1)return;

    std::vector<int> larger, smaller;
    int unpaired = -1;

    spliter(vec, larger, smaller, unpaired);
    RealSorting(larger);
    std::vector<int> insertOrder;

    int prev = 0;
    for (int k = 2; ; k++)
    {
        int jac = jacobsthal(k);
        int end = jac - 1;
        if (end >= static_cast<int>(smaller.size()))
            end = static_cast<int>(smaller.size()) - 1;

        for (int idx = end; idx >= prev; idx--)
            insertOrder.push_back(idx);
        prev = jac;
        if (prev >= (int)smaller.size())
            break;
    }

    std::vector<int> result = larger;
    for (size_t i = 0; i < insertOrder.size(); i++)
    {
        std::vector<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), smaller[insertOrder[i]]);
        result.insert(pos, smaller[insertOrder[i]]); // binary search insertion
    }

    if (unpaired != -1)
    {
        std::vector<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), unpaired);
        result.insert(pos, unpaired);
    }
    sortedVec = result;
}

void PmergeMe::printResults(int i) const
{
    if (i == 0)
    {
        std::cout << "Before: ";
        for (size_t i = 0; i < vec.size(); i++)
            std::cout << vec[i] << " ";
        std::cout << "\nAfter: ";
        for (size_t i = 0; i < sortedVec.size(); i++)
            std::cout << sortedVec[i] << " ";
        std::cout << "\n";
    }
    if (i == 1)
    {
        std::cout << "Before: ";
        for (size_t i = 0; i < deqsort.size(); i++)
            std::cout << deqsort[i] << " ";
        std::cout << "\nAfter: ";
        for (size_t i = 0; i < sortedDeq.size(); i++)
            std::cout << sortedDeq[i] << " ";
        std::cout << "\n";
    }
}

std::vector<int> PmergeMe::getVector() const { return vec; }
std::deque<int> PmergeMe::getDeque() const { return deqsort; }
