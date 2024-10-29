#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj) : _exchangeRates(obj._exchangeRates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &obj)
{
	this->_exchangeRates = obj._exchangeRates;
	return *this;
}

bool BitcoinExchange::NotSpace::operator()(unsigned char ch) const {
    return !std::isspace(ch);
}

bool BitcoinExchange::parseDataFile(const std::string &fileName)
{
	std::ifstream file(fileName.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file.\n";
		return false;
	}
	if (file.peek() == std::ifstream::traits_type::eof())
	{
		std::cerr << "Error: Empty file.\n";
		return false;
	}

	std::string line;
	std::getline(file, line);

	if (line != "date,exchange_rate")
	{
		std::cerr << "Error: Wrong header.\n";
		return false;
	}

	while (std::getline(file, line))
	{
		std::istringstream stringStream(line);
		std::string date, rateStr;
		float rate;

		if (!std::getline(stringStream, date, ',') || !std::getline(stringStream, rateStr) || rateStr.empty())
		{
			std::cerr << "Error: bad line format in file => " << line << "\n";
			return false;
		}

		date = _trim(date);
		rateStr = _trim(rateStr);

		if (_exchangeRates.find(date) != _exchangeRates.end())
		{
			std::cerr << "Error: Duplicate date found => " << date << "\n";
			return false;
		}

		if (!_isValidDate(date) || !_isValidPositiveNumber(rateStr))
		{
			std::cerr << "Error: Invalid data => " << line << "\n";
			return false;
		}

		rate = std::strtof(rateStr.c_str(), NULL);
		_exchangeRates[date] = rate;
	}
	
	file.close();
	return true;
}

bool BitcoinExchange::_isValidPositiveNumber(const std::string &value)
{
	bool hasDecimalPoint = false;
	for (std::string::const_iterator it = value.begin(); it != value.end(); ++it)
	{
		if (*it == '.')
		{
			if (hasDecimalPoint) return false;
			hasDecimalPoint = true;
		}
		else if (!std::isdigit(*it))
		{
			return false;
		}
	}

	double floatVal = std::atof(value.c_str());
	if (floatVal < 0 || floatVal > std::numeric_limits<int>::max())
	{
		std::cerr << "Error: Invalid positive number or exceeds max integer value.\n";
		return false;
	}

	return true;
}


bool BitcoinExchange::getRates(const std::string &fileName)
{
	std::ifstream file(fileName.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file.\n";
		return false;
	}
	if (file.peek() == std::ifstream::traits_type::eof())
	{
		std::cerr << "Error: Empty file.\n";
		return false;
	}

	std::string line;
	std::getline(file, line);

	if (line != "date | value")
	{
		std::cerr << "Error: Wrong header.\n";
		return false;
	}
	
	while (std::getline(file, line))
	{
		_rateLine(line);
	}
	
	file.close();
	return true;
}

bool BitcoinExchange::_rateLine(const std::string &line)
{
	std::istringstream stringStream(line);
	std::string date_key, rate_value;
	if (!std::getline(stringStream, date_key, '|') || !std::getline(stringStream, rate_value))
	{
		std::cerr << "Error: bad input => " << date_key << (rate_value.empty() ? "" : "|" ) << rate_value << "\n";
		return false;
	}
	date_key = _trim(date_key);
	rate_value = _trim(rate_value);
	if (date_key.empty())
	{
		std::cerr << "Error: bad input => " << date_key << "\n";
		return false;
	}
	if (rate_value.empty())
	{
		std::cerr << "Error: bad input => " << date_key << "|" << rate_value << "\n";
		return false;
	}
	if (!_validateInput(date_key, rate_value))
		return false;
	_calculateResult(date_key, rate_value);
	return true;
}

std::string BitcoinExchange::_trim(const std::string &str)
{
	std::string::const_iterator start = std::find_if(str.begin(), str.end(), NotSpace());
    std::string::const_iterator end = std::find_if(str.rbegin(), str.rend(), NotSpace()).base();

    return (start < end ? std::string(start, end) : "");
}

bool BitcoinExchange::_validateInput(const std::string& date, const std::string& value)
{
    if (!_isValidDate(date))
    {
		std::cout << "Error: invalid date => " << date << "\n";
		return false;
	}
    if (!_isValidValue(value))
		return false;
	return true;
}

bool BitcoinExchange::_isValidDate(const std::string& date)
{
    if (date.length() != 10)
		return false;
    if (date[4] != '-' || date[7] != '-')
		return false;
	
    int year, month, day;
    std::istringstream stringStream(date);
    char delimiter;

    stringStream >> year >> delimiter >> month >> delimiter >> day;
    if (year < 2009 || year > 2024|| month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    if ((month == 2 && day == 29 && !_isLeapYear(date)) || (month == 2 && day > 29))
        return false;
    return true;
}

bool BitcoinExchange::_isLeapYear(const std::string& date)
{
	int year = std::atoi(date.substr(0, 4).c_str());
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

bool BitcoinExchange::_isValidValue(const std::string& value)
{
    char *end;
    float val = std::strtof(value.c_str(), &end);

	if (*end != '\0') 
	{
		std::cerr << "Error: not a valid number\n";
		return false;
	}
	if (val < 0) 
	{
		std::cerr << "Error: not a positive number.\n";
		return false;
	}
	if (val > 1000)
	{
		std::cerr << "Error: too large number.\n";
		return false;
	}
    return true;
}

void BitcoinExchange::_calculateResult(const std::string& date, const std::string& value)
{
    std::string closestDate = _findClosestDate(date);
    float rate = _exchangeRates[closestDate];
    float amount = std::strtof(value.c_str(),NULL);
    float result = amount * rate;
    
    std::cout << date << " => " << value << " = " << result << "\n";
}

std::string BitcoinExchange::_findClosestDate(const std::string& date)
{
	std::map<std::string, float>::iterator it = _exchangeRates.lower_bound(date);
	if (it == _exchangeRates.begin())
		return it->first;
	if (it == _exchangeRates.end() || it->first != date)
		--it;
	return it->first;
}
