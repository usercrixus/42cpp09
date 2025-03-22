#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>

class RPN {
public:
    int evaluate(const std::string& expression);

private:
    bool isOperator(char c);
};