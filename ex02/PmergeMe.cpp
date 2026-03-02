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

static void sorting(std::vector <int> &holders, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        sorting(holders, left, mid);
        sorting(holders, mid + 1, right);
        std::vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;
        while (i <= mid && j <= right)
        {
            if (holders[i] < holders[j])
                temp[k++] = holders[i++];
            else
                temp[k++] = holders[j++];
        }
        while (i <= mid)
            temp[k++] = holders[i++];
        while (j <= right)
            temp[k++] = holders[j++];
        for (i = left; i <= right; i++)
            holders[i] = temp[i - left];
    }
}

static int binarySearchVector(std::vector<int> &arr, int value, int end)
{
    int left = 0;
    int right = end;
    
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
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

    // next stage is to sort the larger vector using merge sort
    sorting(larger, 0, larger.size() - 1);
    sorting(smaller, 0, smaller.size() - 1);
    // next stage is to insert the smaller elements into the larger vector using binary search
    sortedVec = larger;
    // the first is guaranteed to be smaller then the first element in larger vector
    sortedVec.insert(sortedVec.begin(), smaller[0]);
    for (size_t i = 1; i < smaller.size(); i++)
    {
        int pos = binarySearchVector(sortedVec, smaller[i], sortedVec.size());
        sortedVec.insert(sortedVec.begin() + pos, smaller[i]);
    }

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
