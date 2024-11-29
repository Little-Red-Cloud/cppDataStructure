#ifndef InsertSort_h
#define InsertSort_h

#include <MySortBase.h>
// Insertion Sort implementation
template <typename T>
class InsertSort : public MySortBase<T> {
public:
    // Constructor to initialize the base class
    InsertSort(std::function<bool(const T&,const T&)> cmp = std::less<T>()) 
        : MySortBase<T>(insertSort, cmp) {}

    // Overridden operator to perform insertion sort
    void operator()(std::vector<T>& vec, int start = 0, int end = -1, int sep = 1) override;
};

// Implementation of Insertion Sort
template <typename T>
void InsertSort<T>::operator()(std::vector<T>& vec, int start, int end, int sep) {
    this->errorArgument(vec, start, end, sep);

    for (int i = start; i <= end; i += sep) {
        T tmp = vec[i];
        int j = i;
        for (; j - sep >= start && this->cmp(tmp, vec[j - sep]); j -= sep) {
            vec[j] = vec[j - sep];
        }
        vec[j] = tmp;
    }
}

#endif