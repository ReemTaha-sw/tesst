#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <limits>

class RPN
{
	private:
		RPN(const RPN &copy);
		RPN &operator=(const RPN &other);
	public:
		RPN();
		~RPN();

		static int evaluate(const std::string &expression);
};

#endif
