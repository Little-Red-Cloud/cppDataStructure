#ifndef SelectSort_h
#define SelectSort_h

#include <MySortBase.h>

// Selection Sort implementation
template <typename T>
class SelectSort : public MySortBase<T> {
public:
    // Constructor to initialize the base class
    SelectSort(std::function<bool(const T&,const T&)> cmp = std::less<T>()) 
        : MySortBase<T>(selectSort, cmp) {}

    // Overridden operator to perform selection sort
    void operator()(std::vector<T>& vec, int start = 0, int end = -1, int sep = 1) override;
};

// Implementation of Selection Sort
template <typename T>
void SelectSort<T>::operator()(std::vector<T>& vec, int start, int end, int sep) {
    this->errorArgument(vec, start, end, sep);

    for (int i = start; i < end; i += sep) {
        int min = i;
        for (int j = i + sep; j <= end; j += sep) {
            if (this->cmp(vec[j], vec[min]))
                min = j;
        }
        if (min != i)
            std::swap(vec[i], vec[min]);
    }
}

#endif