#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &obj) { (void)obj; }

RPN& RPN::operator=(const RPN &obj)
{
    (void)obj;
	return *this;
}

int RPN::evaluate(const std::string &expression) {
    std::istringstream tokens(expression);
    std::string token;
    std::stack<int> stack;

    while (tokens >> token) {
        bool isNumber = true;
         int number = 0;

        for (size_t i = 0; i < token.length(); i++)
        {
            if (!std::isdigit(token[i])) {
                isNumber = false;
                break;
            }
            if (number > (std::numeric_limits<int>::max() - (token[i] - '0')) / 10) {
                isNumber = false;
                break;
            }
            number = number * 10 + (token[i] - '0');
        }

        if (isNumber && token.length() == 1 && std::isdigit(token[0])) {
            stack.push(number);
        } 
		else if (token == "+" || token == "-" || token == "*" || token == "/")
		{
            if (stack.size() < 2)
			{
                std::cerr << "Error: Insufficient operands.\n";
                return -1;
            }
            int b = stack.top();
			stack.pop();
            int a = stack.top();
			stack.pop();
            int result;

            if (token == "+")
				result = a + b;
            else if (token == "-")
				result = a - b;
            else if (token == "*")
				result = a * b;
            else if (token == "/")
			{
                if (b == 0)
				{
                    std::cerr << "Error: Division by zero" << std::endl;
                    return -1;
                }
                result = a / b;
            }
            stack.push(result);
        }
		else
		{
            std::cerr << "Error: Invalid token.\n" ;
            return -1;
        }
    }

    if (stack.size() != 1) {
        std::cerr << "Error: Malformed expression\n";
        return -1;
    }
    std::cout << stack.top() << std::endl;
    return 0;
}

