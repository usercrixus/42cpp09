#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <sys/time.h>
#include <sstream>

class PmergeMe
{
private:
	/* data */
public:
	PmergeMe(/* args */);
	~PmergeMe();

	long getTimeInMicroseconds();
	void mergeInsertSortVector(std::vector<int>& data);
	void mergeInsertSortList(std::list<int>& data);
};