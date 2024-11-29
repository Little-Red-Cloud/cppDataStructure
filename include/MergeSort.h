#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "MySortBase.h"

template<typename T>
class MergeSort : public MySortBase<T> {
public:
    MergeSort(std::function<bool(const T&,const T&)> cmp= std::less<T>()):
        MySortBase<T>(mergeSort,cmp){}
    void operator()(std::vector<T>& vec, int start = 0, int end = -1, int sep = 1) override;
protected:
    void helpSort(std::vector<T>& vec, int start, int end);
    void merge(std::vector<T>& vec, int start, int mid, int end);
};

template<typename T>
void MergeSort<T>::helpSort(std::vector<T>& vec, int start, int end){
    if(start >= end) return ;
    int mid = (start + end) / 2;
    helpSort(vec, start, mid);
    helpSort(vec, mid + 1, end);
    merge(vec, start, mid, end);
}

template<typename T>
void MergeSort<T>::merge(std::vector<T>& vec, int start, int mid, int end){
    int len = end - start + 1;
    std::vector<T> tmp(len);
    int i = start, j = mid + 1, k = 0;
    while(i <= mid && j <= end){
        if(this->cmp(vec[i], vec[j])){
            tmp[k++] = vec[i++];
        }else{
            tmp[k++] = vec[j++];
        }
    }
    while(i <= mid) tmp[k++] = vec[i++];
    while(j <= end) tmp[k++] = vec[j++];
    for(int i = 0; i < len; i++) vec[start + i] = tmp[i];
}



template<typename T>
void MergeSort<T>::operator()(std::vector<T>& vec, int start, int end, int sep) {
    this->errorArgument(vec, start, end,sep);
    if(sep==1){
        helpSort(vec, start, end);
        return;
    }
    std::vector<T> tmp;
    for(int i=start;i<=end;i+=sep){
        tmp.push_back(vec[i]);
    }
    helpSort(tmp, 0, tmp.size() - 1);
    for(int i=start, j=0;i<=end && j<tmp.size();i+=sep,j++){
        vec[i] = tmp[j];
    }
}
#endif