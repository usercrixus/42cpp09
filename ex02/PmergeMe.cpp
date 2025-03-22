#include "PmergeMe.hpp"

PmergeMe::PmergeMe(/* args */)
{
}

PmergeMe::~PmergeMe()
{
}
// Fonction pour mesurer le temps
long PmergeMe::getTimeInMicroseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

// Merge-insert sort pour std::vector
void PmergeMe::mergeInsertSortVector(std::vector<int>& data) {
    if (data.size() <= 1) return;

    std::vector<int> left(data.begin(), data.begin() + data.size() / 2);
    std::vector<int> right(data.begin() + data.size() / 2, data.end());

    mergeInsertSortVector(left);
    mergeInsertSortVector(right);

    std::merge(left.begin(), left.end(), right.begin(), right.end(), data.begin());
}

// Merge-insert sort pour std::list
void PmergeMe::mergeInsertSortList(std::list<int>& data) {
    if (data.size() <= 1) return;

    std::list<int> left, right;
    std::list<int>::iterator mid = data.begin();
    std::advance(mid, data.size() / 2);

    left.splice(left.begin(), data, data.begin(), mid);
    right.splice(right.begin(), data, data.begin(), data.end());

    mergeInsertSortList(left);
    mergeInsertSortList(right);

    data.merge(left);
    data.merge(right);
}