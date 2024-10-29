#include "PmergeMe.hpp"

bool isValidNumber(const std::string &str) {
    if (str.empty()) return false;

    if (str.length() > 1 && str[0] <= '0') return false;

    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        start = 1;
    }

    for (size_t i = start; i < str.length(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }

    long long num = std::atoll(str.c_str());

    if (num > INT_MAX || num < INT_MIN) {
        return false;
    }

    return true;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error: No numbers provided!" << std::endl;
        return 1;
    }

    std::vector<int> inputVec;
    std::deque<int> inputDeq;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (!isValidNumber(arg)) {
            std::cerr << "Error: Not a valid number: " << arg << std::endl;
            return 1;
        }
        int number = std::atoi(argv[i]);
        inputVec.push_back(number);
        inputDeq.push_back(number);
    }

    std::cout << "Before: ";
    for (size_t i = 0; i < inputVec.size(); ++i) {
        std::cout << inputVec[i] << " ";
    }
    std::cout << std::endl;

    PmergeMe sorter;

    if (!sorter.setVector(inputVec) || !sorter.setDeque(inputDeq))
        return 1;

    sorter.sortVector();
    sorter.sortDeque();
    std::cout << "After: ";
    sorter.printVector();
    std::cout << "Time to process a range of " << inputVec.size()
              << " elements with std::vector: " << std::fixed << std::setprecision(4) << sorter.getVectorSortTime() << " us" << std::endl;
    std::cout << "Time to process a range of " << inputDeq.size()
              << " elements with std::deque: " << std::fixed << std::setprecision(4) << sorter.getDequeSortTime() << " us" << std::endl;
}