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

void PmergeMe::mergeInsertSortVector(std::vector<int>& data) {
    if (data.size() <= 1) return;

    // Step 1: Pairing & Sorting
    std::vector<int> mainChain, spareList;
    for (size_t i = 0; i < data.size(); i += 2) {
        if (i + 1 < data.size()) {
            if (data[i] > data[i + 1]) {
                mainChain.push_back(data[i]);
                spareList.push_back(data[i + 1]);
            } else {
                mainChain.push_back(data[i + 1]);
                spareList.push_back(data[i]);
            }
        } else {
            mainChain.push_back(data[i]); // Unpaired element
        }
    }

    // Step 2: Recursively sort the main chain
    mergeInsertSortVector(mainChain);

    // Step 3: Insert spare list elements with binary insertion
    for (std::vector<int>::iterator sit = spareList.begin(); sit != spareList.end(); ++sit) {
        std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), *sit);
        mainChain.insert(pos, *sit);
    }

    // Step 4: Copy result back to original data
    data = mainChain;
}

void PmergeMe::binaryInsert(std::vector<int>& chain, int value) {
    std::vector<int>::iterator pos = std::lower_bound(chain.begin(), chain.end(), value);
    chain.insert(pos, value);
}

void PmergeMe::mergeInsertSortList(std::list<int>& data) {
    if (data.size() <= 1) return;

    // Step 1: Pairing & Sorting
    std::list<int> mainChain, spareList;
    std::list<int>::iterator it = data.begin();

    while (it != data.end()) {
        int first = *it;
        ++it;

        if (it != data.end()) {
            int second = *it;
            if (first > second) {
                mainChain.push_back(first);
                spareList.push_back(second);
            } else {
                mainChain.push_back(second);
                spareList.push_back(first);
            }
            ++it;
        } else {
            mainChain.push_back(first); // Unpaired element
        }
    }

    // Step 2: Recursively sort the main chain
    mergeInsertSortList(mainChain);

    // Step 3: Insert spare list elements using binary insertion
    for (std::list<int>::iterator sit = spareList.begin(); sit != spareList.end(); ++sit) {
        std::list<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), *sit);
        mainChain.insert(pos, *sit);
    }

    // Step 4: Copy result back to original data
    data = mainChain;
}
