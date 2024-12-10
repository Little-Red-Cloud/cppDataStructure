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
#include <RadixSort.h>

// Factory class to create sorting objects
template <typename T>
class MySort {
private:
    MySortBase<T>* ptr; // Pointer to the sorting object

public:
    // Constructor to create a sorting object based on the sorting type
    MySort(SortType sortType, std::function<bool(const T&,const T&)> cmp = std::less<T>())
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
            ptr = new ShellSort<T>(cmp);
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
        case radixSort:
            ptr=new RadixSort<T>();
            break;
        default:
            ptr = new QuickSort<T>(cmp);
        }
    }
    MySort(SortType sortType, int maxStep,std::function<int(int)> stepfunc, 
        std::function<bool(const T&,const T&)> cmp = std::less<T>())
    {
        if(sortType!=shellSort)
            throw std::invalid_argument("Invalid sort type");
        if (maxStep <= 0) {
            std::cout << "\nmaxStep should be greater than 0. maxStep auto change into 5\n";
            maxStep = 5;
        }
        ptr = new ShellSort<T>(cmp, maxStep, stepfunc);
    }
    MySort(SortType sortType,int maxWeight,size_t bucketSize,
        std::function<size_t(const T&)> getKey,
        std::function<T(const T &)> getNextWeight,
        std::function<bool(const T&,const T&)> cmp=std::less())
    {    
        if(sortType!=radixSort)
            throw std::invalid_argument("Invalid sort type");
        ptr=new RadixSort<T>(maxWeight,bucketSize,getKey,getNextWeight);
    }

    // Destructor to clean up the sorting object
    ~MySort() { 
        if(ptr) delete ptr; 
    }

    // Operator to perform the sorting
    void operator()(std::vector<T>& vec, int start = 0, int end = -1, int sep = 1) {
        (*ptr)(vec, start, end, sep);
    }

    // Function to get the sorting type
    SortType getSortType() const { return ptr->getSortType(); }
};

#endif