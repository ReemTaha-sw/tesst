#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vectorSortTime(0), _dequeSortTime(0) {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &copy) : _vec(copy._vec), _deq(copy._deq) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

bool PmergeMe::setVector(const std::vector<int> &inputVec) {
    if (!_isValidNumber(inputVec))
        return false;
    _vec = inputVec;
    return true;
}

bool PmergeMe::setDeque(const std::deque<int> &inputDeq) {
    if (!_isValidNumber(inputDeq))
        return false;
    _deq = inputDeq;
    return true;
}

void PmergeMe::sortVector() {
    struct timeval startVec, endVec;
    gettimeofday(&startVec, NULL);
    _mergeInsertSortVector();
    gettimeofday(&endVec, NULL);
    _vectorSortTime = (endVec.tv_sec - startVec.tv_sec) * 1000000.0 + (endVec.tv_usec - startVec.tv_usec);
}

void PmergeMe::sortDeque() {
    struct timeval startDeq, endDeq;
    gettimeofday(&startDeq, NULL);
    _mergeInsertSortDeque();
    gettimeofday(&endDeq, NULL);    
    _dequeSortTime = (endDeq.tv_sec - startDeq.tv_sec) * 1000000.0 + (endDeq.tv_usec - startDeq.tv_usec);
}

void PmergeMe::printVector() const {
    std::cout << "Vector: ";
    for (size_t i = 0; i < _vec.size(); ++i) {
        std::cout << _vec[i] << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::printDeque() const {
    std::cout << "Deque: ";
    for (size_t i = 0; i < _deq.size(); ++i) {
        std::cout << _deq[i] << " ";
    }
    std::cout << std::endl;
}

template <typename Container>
void mergeSortedPairs(Container &container, typename Container::iterator start, typename Container::iterator end) {
    if (std::distance(start, end) <= 1)
        return;

    typename Container::iterator mid = start + std::distance(start, end) / 2;
    mergeSortedPairs(container, start, mid);
    mergeSortedPairs(container, mid, end);

    Container temp;
    typename Container::iterator left = start, right = mid;
    while (left != mid && right != end) {
        if (*left < *right) {
            temp.push_back(*left++);
        } else {
            temp.push_back(*right++);
        }
    }
    while (left != mid) {
        temp.push_back(*left++);
    }
    while (right != end) {
        temp.push_back(*right++);
    }

    std::copy(temp.begin(), temp.end(), start);
}



void PmergeMe::_mergeInsertSortVector() {
    std::vector<std::pair<int, int> > pairs;
    std::vector<int> result;

    for (size_t i = 0; i + 1 < _vec.size(); i += 2) {
        if (_vec[i] > _vec[i + 1]) {
            pairs.push_back(std::make_pair(_vec[i + 1], _vec[i]));
        } else {
            pairs.push_back(std::make_pair(_vec[i], _vec[i + 1]));
        }
    }

    if (_vec.size() % 2 == 1) {
        result.push_back(_vec.back());
    }

    for (size_t i = 0; i < pairs.size(); ++i) {
        result.push_back(pairs[i].second);
    }

    for (size_t i = 0; i < pairs.size(); ++i) {
        std::vector<int>::iterator it = std::lower_bound(result.begin(), result.end(), pairs[i].first);
        result.insert(it, pairs[i].first);
    }

    _vec = result;
}

void PmergeMe::_mergeInsertSortDeque() {
    std::deque<std::pair<int, int> > pairs;
    std::deque<int> result;

    for (size_t i = 0; i + 1 < _deq.size(); i += 2) {
        if (_deq[i] > _deq[i + 1]) {
            pairs.push_back(std::make_pair(_deq[i + 1], _deq[i]));
        } else {
            pairs.push_back(std::make_pair(_deq[i], _deq[i + 1]));
        }
    }

    if (_deq.size() % 2 == 1) {
        result.push_back(_deq.back());
    }

    for (size_t i = 0; i < pairs.size(); ++i) {
        result.push_back(pairs[i].second);
    }

    for (size_t i = 0; i < pairs.size(); ++i) {
        std::deque<int>::iterator it = std::lower_bound(result.begin(), result.end(), pairs[i].first);
        result.insert(it, pairs[i].first);
    }

    _deq = result;
}


double PmergeMe::getVectorSortTime() const { return _vectorSortTime; }
double PmergeMe::getDequeSortTime() const { return _dequeSortTime; }
