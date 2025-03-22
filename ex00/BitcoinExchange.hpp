#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept> 

class BitcoinExchange
{
private:
	std::map<std::string, float> _data;

	void loadData();
	
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &cpy);
	BitcoinExchange &operator=(const BitcoinExchange &cpy);
	~BitcoinExchange();

	void printQuant(std::string fileName);
};