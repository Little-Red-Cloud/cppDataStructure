#ifndef RADIXSORT_H_
#define RADIXSORT_H_

#include "MySortBase.h"

template<typename T>
struct listNode{
public:
    T data;
    T now;
    listNode<T>* next;
    listNode(const T & data,const T* next=nullptr):data(data),now(data),next(nullptr){}
};

template<typename T>
struct myList {
public:
    listNode<T>* head;
    listNode<T>* tail;
    myList() {
        head = tail = nullptr;
    }
    void push_back(const T& t){
        listNode<T>* newNode = new listNode<T>(t);
        if(head==nullptr){
            head=tail=newNode;
            return ;
        }
        tail->next=newNode;
        tail=newNode;
    }
    void push_back(listNode<T>* newNode){
        if(head==nullptr){
            head=tail=newNode;
            tail->next=nullptr;
            return ;
        }
        tail->next=newNode;
        tail=newNode;
        tail->next=nullptr;
    }
    ~myList(){
        while(head!=nullptr){
            listNode<T>* temp = head;
            head=head->next;
            delete temp;
        }
    }
};


template <typename T>
class RadixSort:public MySortBase<T>{
public:
    //default construction arguments for integer 64bits types ascending.
    //If you want to change the type, you should change the default arguments,
    //such as maxWeight, bucketSize, getKey, getNextWeight.
    //@param maxWeight: the max weight of the number.
    //@param bucketSize: the size of the bucket.
    //@param getKey: get the key (bucket index) of now number that also controls the orders.
    //@param getNextWeight: get the next number of now number, which is less weight than now.
    RadixSort(
        int maxWeight=20,size_t bucketSize=19,
        std::function<size_t(const T&)> getKey=[](const T& x)->size_t{return x%10+9;},
        std::function<T(const T &)> getNextWeight=[](const T &x)->T{return x/10;}
        ):
        MySortBase<T>(radixSort,std::less()),maxWeight(maxWeight),bucketSize(bucketSize),getKey(getKey),getNextWeight(getNextWeight){}
    void operator()(std::vector<T>& vec, int start = 0, int end = -1, int sep = 1);
protected:
    int maxWeight;
    size_t bucketSize;
    std::function<size_t(const T&)> getKey;
    std::function<T(const T &)> getNextWeight;
    void helpSort(std::vector<T>& vec, int start = 0, int end = -1);
};

template <typename T>
void RadixSort<T>::helpSort(std::vector<T>& vec,int start,int end){
    this->errorArgument(vec,start,end,1);
    myList<T> dataList;
    for(int i=start;i<=end;i++){
        dataList.push_back(vec[i]);
    }
    std::vector<myList<T>> bucketList(bucketSize);
    for(int i=0;i<maxWeight;i++){
        listNode<T>* curr=dataList.head;
        while(curr!=nullptr){
            listNode<T>* next=curr->next;
            bucketList[this->getKey(curr->now)].push_back(curr);
            curr->now=this->getNextWeight(curr->now);
            curr=next;
        }
        dataList.tail=bucketList.front().tail;
        dataList.head=bucketList.front().head;
        for(int j=1;j<bucketSize;j++){
            if(bucketList[j].head){
                if(dataList.head==nullptr)
                    dataList.head=bucketList[j].head;
                if(dataList.tail)
                    dataList.tail->next=bucketList[j].head;
                dataList.tail=bucketList[j].tail;
            }
            
        }
        for(int j=0;j<bucketSize;j++){
            bucketList[j].tail=nullptr;
            bucketList[j].head=nullptr;
        }
    }
    listNode<T>* curr=dataList.head;
    int i=start;
    while(curr!=nullptr){
        vec[i++]=curr->data;
        curr=curr->next;
    }
}



template <typename T>
void RadixSort<T>::operator()(std::vector<T>& vec,int start,int end,int sep){
    this->errorArgument(vec,start,end,sep);
    if(sep==1){
        helpSort(vec,start,end);
        return ;
    }
    std::vector<T> tmp;
    for(int i=start;i<=end;i+=sep){
        tmp.push_back(vec[i]);
    }
    helpSort(tmp);
    for(int i=start,j=0;i<=end && j<tmp.size();i+=sep,j++){
        vec[i]=tmp[j];
    }
}
#endif