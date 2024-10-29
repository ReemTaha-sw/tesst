#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cstdlib>
#include <sstream>
#include <sys/time.h>
#include <climits>
#include <iomanip>


class PmergeMe
{
	private:
		std::vector<int> _vec;
		std::deque<int> _deq;
		double _vectorSortTime;
		double _dequeSortTime;
		
		void _mergeInsertSortVector();
		void _mergeInsertSortDeque();
	    template <typename Container>
		bool _isValidNumber(const Container &input);

	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe &copy);
		PmergeMe &operator=(const PmergeMe &other);

		bool setVector(const std::vector<int> &inputVec);
		void sortVector();
		void printVector() const; 
		double getVectorSortTime() const;

		bool setDeque(const std::deque<int> &inputDeq);
		void sortDeque();
		void printDeque() const;
		double getDequeSortTime() const;

};


template <typename Container>
bool PmergeMe::_isValidNumber(const Container &input)
{
	typename Container::const_iterator it;
    for (it = input.begin(); it != input.end(); ++it)
    {
        std::stringstream ss;
        ss << *it;
        
        int number;
        if (!(ss >> number)) 
        {
            std::cerr << "Error: Not a valid number.\n";
            return false;
        }
        if (ss.fail() || !ss.eof()) 
        {
            std::cerr << "Error: Not a valid number.\n";
            return false;
        }
    }
    return true;
}

#endif
