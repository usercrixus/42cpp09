#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <sys/time.h>
#include <sstream>

#include "PmergeMe.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2)
	{
        std::cerr << "Error" << std::endl;
        return 1;
    }

	// Create vector and push them
    std::vector<int> vec;
    std::list<int> lst;
    for (int i = 1; i < argc; ++i) {
        int num;
        if (!(std::istringstream(argv[i]) >> num) || num < 0) {
            std::cerr << "Error" << std::endl;
            return 1;
        }
        vec.push_back(num);
        lst.push_back(num);
    }

	// display before sorting
    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

	PmergeMe sorter;
    // sort with vect
    long start = sorter.getTimeInMicroseconds();
    sorter.mergeInsertSortVector(vec);
    long vectorTime = sorter.getTimeInMicroseconds() - start;

    // sort with list
    start = sorter.getTimeInMicroseconds();
    sorter.mergeInsertSortList(lst);
    long listTime = sorter.getTimeInMicroseconds() - start;

    // display sorted data
    std::cout << "After: ";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    // display performance
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << lst.size() << " elements with std::list : " << listTime << " us" << std::endl;

    return 0;
}