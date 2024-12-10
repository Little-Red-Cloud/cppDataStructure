#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include "MySortBase.h"

template<typename T>
class QuickSort:public MySortBase<T>
{
public:
    QuickSort(std::function<bool(const T&,const T&)> cmp=std::less())
        :MySortBase<T>(quickSort,cmp){}
    void operator()(std::vector<T>& vec, int start = 0, int end = -1, int sep = 1);
protected:
    void helpSort(std::vector<T>& vec, int start, int end);
    int findSep(std::vector<T>& vec, int start, int end);
};

template<typename T>
int QuickSort<T>::findSep(std::vector<T>& vec, int start, int end)
{
    int sep = start + (end - start) / 2;
    if(this->cmp(vec[end],vec[start]))
        std::swap(vec[start], vec[end]);
    if(this->cmp(vec[sep], vec[start]))
        std::swap(vec[start], vec[sep]);
    if(this->cmp(vec[end], vec[sep]))
        std::swap(vec[end], vec[sep]);
    if(sep!=end-1){
        std::swap(vec[sep], vec[end - 1]);
        sep = end - 1;
    }
    return sep;
}

template<typename T>
void QuickSort<T>::helpSort(std::vector<T>& vec, int start, int end)
{
    if(start >= end) return;
    int sep=findSep(vec,start,end);
    int i=start+1;
    int j=end-2;
    bool istop=false;
    bool jstop=false;
    while(i<=j){
        if(this->cmp(vec[sep],vec[i]))
            istop=true;
        if(this->cmp(vec[j],vec[sep]))
            jstop=true;
        if(!istop)
            i++;
        if(!jstop)
            j--;
        if(istop&&jstop){
            if(i!=j)
                std::swap(vec[i],vec[j]);
            i++;
            j--;
            istop=false;
            jstop=false;
        }
    }
    if(i<end-1)
        std::swap(vec[i],vec[end-1]);
    helpSort(vec,start,i-1);
    helpSort(vec,i+1,end);
}

template<typename T>
void QuickSort<T>::operator()(std::vector<T>& vec, int start, int end, int sep)
{
    this->errorArgument(vec,start,end,sep);
    if(sep==1)
        helpSort(vec,start,end);
    else{
        std::vector<T> tmp;
        for(int i=start;i<=end;i+=sep)
            tmp.push_back(vec[i]);
        helpSort(tmp,0,tmp.size()-1);
        for(int i=0,j=0;i<=end&&j<tmp.size();i+=sep,j++)
            vec[i]=tmp[j];

    }
}

#endif