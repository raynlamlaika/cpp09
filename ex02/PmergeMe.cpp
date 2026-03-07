#include "PmergeMe.hpp"



PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &other) : vec(other.vec), sortedVec(other.sortedVec) {}
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)  //  best practice even if i didn't allocat any memoory
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
            throw std::invalid_argument("Negative number");
            return;
        }
        if (num < 0) {std::cerr << "Error: negative number\n"; throw std::invalid_argument("Negative number"); return ;}
        vec.push_back(num);
    }
}

static void spliter(const std::vector<int> &vec, std::vector<int> &larger, std::vector<int> &smaller, int &unpaired)
{
    for (size_t i = 0 ;vec.size() > i ; i++)
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

    // recursive step
    RealSorting(larger);

    // main chain
    std::vector<int> result = larger;

    // insert first element
    result.insert(result.begin(), smaller[0]);

    // binary search
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


void PmergeMe::mergeInsertSort(const std::vector<int> &vec)
{

    // start of the merge insert sort algorithm
    // base  checks
    if (vec.size() <= 1)
        return ;
    // first the split of the vector into pairs and the split of the larger and smaller elements into two vectors itn stor unpaired element if the size of the vector is odd
    std::vector<int> larger, smaller;
    int unpaired = -1;
    size_t n = vec.size();
    if (n % 2 == 1)
        unpaired = vec[n - 1];

    spliter(vec, larger, smaller, unpaired);
    // if (unpaired != -1)
    //     larger.insert(larger.end() , unpaired);



    // // next stage is to sort the larger vector using merge sort
    RealSorting(smaller);
    RealSorting(larger);
    // // next stage is to insert the smaller elements into the larger vector using binary search
    // // sortedVec = larger;


    std::cout << "-------------------------------: ";
    for (size_t i = 0; i < larger.size(); i++)
        std::cout << larger[i] << " ";
    std::cout << "\n++++++++++++++++++++++++++++: ";
    for (size_t i = 0; i < smaller.size(); i++)
        std::cout << smaller[i] << " ";
    std::cout << "\n";


    // the first is guaranteed to be smaller then the first element in larger vector
    // sortedVec.insert(sortedVec.begin(), smaller[0]);
    // for (size_t i = 1; i < smaller.size(); i++)
    // {
    //     int pos = binarySearchVector(sortedVec, smaller[i], sortedVec.size());
    //     sortedVec.insert(sortedVec.begin() + pos, smaller[i]);
    // }



    // here change the implemmentation to jacopstal
    std::vector<int> result = larger;

    // insert first smaller
    result.insert(result.begin(), smaller[0]);

    // insert remaining smaller elements
    for (size_t i = 1; i < smaller.size(); i++)
    {
        std::vector<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), smaller[i]);

        result.insert(pos, smaller[i]);
    }

    // insert unpaired element
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
