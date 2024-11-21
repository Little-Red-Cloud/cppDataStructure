#ifndef MYSORTBASE_H
#define MYSORTBASE_H

#include<vector>
#include<functional>
#include<stdexcept>
#include<algorithm>

// Enum to define different sorting types
enum SortType { bubbleSort, insertSort, selectSort, shellSort, heapSort };

// Base class for all sorting algorithms
template <typename T>
class MySortBase {
public:
    // Constructor to initialize the sorting type and comparison function
    MySortBase(SortType sortType, std::function<bool(T&, T&)> cmp = std::less<T>()) 
        : sortType(sortType), cmp(cmp) {}

    // Pure virtual function to perform the sorting
    virtual void operator()(std::vector<T>& vec, int start = 0, int end = -1, int sep = 1) = 0;

    // Function to get the sorting type
    virtual SortType getSortType() const { return sortType; }

    // Destructor
    virtual ~MySortBase() {}

protected:
    std::function<bool(T&, T&)> cmp; // Comparison function
    SortType sortType; // Sorting type
};

// Function to validate and adjust the arguments for sorting
template <typename T>
void errorArgument(std::vector<T>& vec, int& start, int& end, int& sep) {
    if (end == -1)
        end = vec.size() - 1;
    if (start < 0 || end >= vec.size() || start > end || sep <= 0)
        throw std::invalid_argument("Invalid argument");
}

#endif