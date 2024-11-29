#ifndef ShellSort_h
#define ShellSort_h

#include<MySortBase.h>
#include<InsertSort.h>
// Shell Sort implementation
template <typename T>
class ShellSort : public MySortBase<T> {
    int maxStep; // Maximum step size
    std::function<int(int)> stepFunction; // Step function to calculate step sizes

public:
    // Constructor to initialize the base class and additional parameters
    ShellSort(std::function<bool(const T&,const T&)> cmp = std::less<T>(), int maxStep = 5,
              std::function<int(int)> stepfunc = [](int i) { return 2 << i - 1; })
        : MySortBase<T>(shellSort, cmp), maxStep(maxStep), stepFunction(stepfunc) {}

    // Overridden operator to perform shell sort
    void operator()(std::vector<T>& vec, int start = 0, int end = -1, int sep = 1) override;
};

// Implementation of Shell Sort
template <typename T>
void ShellSort<T>::operator()(std::vector<T>& vec, int start, int end, int sep) {
    this->errorArgument(vec, start, end, sep);
    int i = this->maxStep;
    int trueSep = this->stepFunction(i) * sep;
    InsertSort<T> insrtSort(this->cmp);
    while (trueSep >= sep) {
        insrtSort(vec, start, end, trueSep);
        trueSep = this->stepFunction(--i) * sep;
    }
    insrtSort(vec, start, end, sep);
}

#endif