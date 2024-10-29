#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <limits>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _exchangeRates;
		struct NotSpace {
		    bool operator()(unsigned char ch) const;
		};
		bool _isValidPositiveNumber(const std::string &value);
		bool _isValidDate(const std::string &date);
		bool _isLeapYear(const std::string &date);
		bool _isValidValue(const std::string &value);
		std::string _findClosestDate(const std::string &date);
		bool _rateLine(const std::string &line);
    	bool _validateInput(const std::string &date, const std::string &value);
    	void _calculateResult(const std::string &date, const std::string &value);
    	std::string _trim(const std::string &str);
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &other);

		bool parseDataFile(const std::string &fileName);
		bool getRates(const std::string &fileName);
};

#endif
