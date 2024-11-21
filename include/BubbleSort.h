#ifndef BubbleSort_h
#define BubbleSort_h

#include <MySortBase.h>

// Bubble Sort implementation
template <typename T>
class BubbleSort : public MySortBase<T> {
public:
    // Constructor to initialize the base class
    BubbleSort(std::function<bool(T&, T&)> cmp = std::less<T>()) 
        : MySortBase<T>(bubbleSort, cmp) {}

    // Overridden operator to perform bubble sort
    void operator()(std::vector<T>& vec, int start = 0, int end = -1, int sep = 1) override;
};

// Implementation of Bubble Sort
template <typename T>
void BubbleSort<T>::operator()(std::vector<T>& vec, int start, int end, int sep) {
    errorArgument(vec, start, end, sep);
    for (int i = start; i <= end; i += sep) {
        int flag = 1;
        for (int j = start; j < end; j += sep) {
            if (j + sep > end) {
                flag = 0;
                break;
            }
            if (this->cmp(vec[j + sep], vec[j])) {
                std::swap(vec[j], vec[j + sep]);
                flag = 0;
            }
        }
        if (flag)
            break;
    }
}


#endif