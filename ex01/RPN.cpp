#include "RPN.hpp"

int RPN::evaluate(const std::string &expression)
{
	std::stack<int> stack;
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		if (isdigit(token[0]))
		{
			stack.push(token[0] - '0'); // convertit le caractère en entier (caractère '3' devient l'entier 3).
		}
		else if (token.size() == 1 && isOperator(token[0])) // is it and operator ?
		{
			if (stack.size() < 2) // not enough data to do the math
			{ 
				throw std::runtime_error("Error: Insufficient operands");
			}
			int b = stack.top(); stack.pop();
			int a = stack.top(); stack.pop();

			switch (token[0]) {
				case '+': stack.push(a + b); break;
				case '-': stack.push(a - b); break;
				case '*': stack.push(a * b); break;
				case '/':
					if (b == 0) {
						throw std::runtime_error("Error: Division by zero");
					}
					stack.push(a / b);
					break;
				default:
					throw std::runtime_error("Error: Unknown operator");
			}
		}
		else
		{
			throw std::runtime_error("Error: Invalid token");
		}
	}

	if (stack.size() != 1) {
		throw std::runtime_error("Error: Invalid expression");
	}

	return stack.top();
}

bool RPN::isOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}
