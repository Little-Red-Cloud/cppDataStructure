#ifndef MYSORT_H
#define MYSORT_H

#include<iostream>

#include <MySortBase.h>
#include <BubbleSort.h>
#include<InsertSort.h>
#include <SelectSort.h>
#include <ShellSort.h>
#include <HeapSort.h>
#include <MergeSort.h>
#include <QuickSort.h>

// Factory class to create sorting objects
template <typename T>
class MySort {
private:
    MySortBase<T>* ptr; // Pointer to the sorting object

public:
    // Constructor to create a sorting object based on the sorting type
    MySort(SortType sortType, std::function<bool(const T&,const T&)> cmp = std::less<T>(), int maxStep = 5,
           std::function<int(int)> stepfunc = [](int i) { return 2 << i - 1; })
    {
        switch (sortType) {
        case bubbleSort:
            ptr = new BubbleSort<T>(cmp);
            break;
        case insertSort:
            ptr = new InsertSort<T>(cmp);
            break;
        case selectSort:
            ptr = new SelectSort<T>(cmp);
            break;
        case shellSort:
            if (maxStep <= 0) {
                std::cout << "\nmaxStep should be greater than 0. maxStep auto change into 5\n";
                maxStep = 5;
            }
            ptr = new ShellSort<T>(cmp, maxStep, stepfunc);
            break;
        case heapSort:
            ptr = new HeapSort<T>(cmp);
            break;
        case mergeSort:
            ptr = new MergeSort<T>(cmp);
            break;
        case quickSort:
            ptr = new QuickSort<T>(cmp);
            break;
        default:
            ptr = new HeapSort<T>(cmp);
        }
    }

    // Destructor to clean up the sorting object
    ~MySort() { delete ptr; }

    // Operator to perform the sorting
    void operator()(std::vector<T>& vec, int start = 0, int end = -1, int sep = 1) {
        (*ptr)(vec, start, end, sep);
    }

    // Function to get the sorting type
    SortType getSortType() const { return ptr->getSortType(); }
};

#endif