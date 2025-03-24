#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(/* args */)
{
	loadData();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &cpy)
{
	_data = cpy._data;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &cpy)
{
	_data = cpy._data;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadData()
{
	std::ifstream file("data.csv");
	if (!file) {
		std::cerr << "Error: Could not open file data.csv" << std::endl;
	}
	else
	{
		std::string line;
		// Skip the first line (header)
		if (!std::getline(file, line)) {
			std::cerr << "Error: CSV file is empty or corrupted" << std::endl;
			return;
		}
		while (std::getline(file, line)) 
		{
			std::stringstream ss(line);
			std::string date;
			std::string rateStr;
			if (std::getline(ss, date, ',') && std::getline(ss, rateStr)) 
			{
				std::stringstream rateStream(rateStr);
				float rate;
				if (!(rateStream >> rate))  // Check for invalid floats
					throw std::runtime_error("Bad csv format");
				else
					_data[date] = rate;
			}
		}
	}
}


void BitcoinExchange::printQuant(std::string fileName)
{
    std::ifstream file(fileName.c_str());
    if (!file) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return;
    }
    std::string line;
    // ✅ Skip the first line (header)
    if (!std::getline(file, line)) {
        std::cerr << "Error: CSV file is empty or corrupted" << std::endl;
        return;
    }

    while (std::getline(file, line)) 
    {
        std::stringstream ss(line);
        std::string date;
        std::string valueStr;
        if (std::getline(ss, date, '|') && std::getline(ss, valueStr))
        {
            std::stringstream valueStream(valueStr);
            float value;
            if (!(valueStream >> value))
                std::cerr << "Not a valid float: " + date + "|" + line << std::endl;
            else if (value < 0 || value > 1000)
                std::cerr << "Bad float range: " + date + "|" + line << std::endl;
            else
            {
                // Find closest date
                std::map<std::string, float>::iterator it = _data.lower_bound(date);
                if (it == _data.end())
                {
                    --it; // Last available date if nothing is greater or equal
                } 
                else if (it != _data.begin() && it->first != date)
                {
                    std::map<std::string, float>::iterator prev = it;
                    --prev;
                    // Compare date differences
                    if (date.compare(prev->first) < date.compare(it->first))
                        it = prev;
                }
                std::cout << date << " => " << it->first << " = " << it->second * value << std::endl;
            }
        }
    }
}