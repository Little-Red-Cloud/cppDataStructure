#ifndef HeapSort_h
#define HeapSort_h

#include <MySortBase.h>

// Heap Sort implementation
template <typename T>
class HeapSort : public MySortBase<T> {
private:
    // Helper function to perform heap sort
    void helpFunction(std::vector<T>& vec);

public:
    // Constructor to initialize the base class
    HeapSort(std::function<bool(T&, T&)> cmp = std::less<T>())
        : MySortBase<T>(heapSort, cmp) {}

    // Overridden operator to perform heap sort
    void operator()(std::vector<T>& vec, int start = 0, int end = -1, int sep = 1) override;
};

// Helper function for Heap Sort
template <typename T>
void HeapSort<T>::helpFunction(std::vector<T>& vec) {
    auto getParent=[](int i){return i& 1? (i)/2:(i-1)/2;};
    auto sink=[&](int start,int end){
        int index=start;
        T tmp=vec[index];
        while(index*2+1<=end){
            int left=index*2+1;
            int right=index*2+2;
            int largest=left;
            if(right<=end && this->cmp(vec[left],vec[right]))
                largest=right;
            if(this->cmp(vec[index],vec[largest])){
                std::swap(vec[largest],vec[index]);
                index=largest;
            }
            else break;
        }
        vec[index]=tmp;
    };
    int i= getParent(vec.size()-1); 
    for(;i>=0;i--){
        sink(i,vec.size()-1);
    }
    for(i=vec.size()-1;i>0;i--){
        std::swap(vec[0],vec[i]);
        sink(0,i-1);
    }
}

// Implementation of Heap Sort
template <typename T>
void HeapSort<T>::operator()(std::vector<T>& vec, int start, int end, int sep) {
    errorArgument(vec, start, end, sep);

    std::vector<T> help;
    for (int i = start; i <= end; i += sep)
        help.push_back(vec[i]);
    this->helpFunction(help);
    for (int i = start, j = 0; i <= end && j < help.size(); i += sep, j++)
        vec[i] = help[j];
}

#endif