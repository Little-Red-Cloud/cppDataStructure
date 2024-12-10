#include<vector>
#include<iostream>
#include <myLibraries.h>
#include <testData.h>
using namespace std;

void test(SortType t){
    cout<<"----------------------\nsep=1\n";
    vector<int> v = {124,47654,547,234,789,-23,-93};
    MySort<int> mySort(t);
    mySort(v);
    for(auto x:v){
        cout<<x<<" ";
    }
    cout<<"\n";
    cout<<"----------------------\nsep=2\n";
    vector<int> v2 = {10,9,8,7,6,5,4,3,2,1};
    MySort<int> mySort2(t);
    mySort2(v2,0,-1,2);
    for(auto x:v2){
        cout<<x<<" ";
    }
    cout<<"\n";
    cout<<"----------------------\nsep=3\n";
    vector<int> v3 = {10,9,8,7,6,5,4,3,2,1};
    MySort<int> mySort3(t);
    mySort3(v3,0,-1,3);
    for(auto x:v3){
        cout<<x<<" ";
    }
    cout<<"\n";
}

void testBigData(SortType t){
    cout<<"----------------------\n";
    cout<<"BigDataSize:"<<myBigData.size()<<"\n";
    MySort<int> mySort(t);
    mySort(myBigData);
    for(int i=0;i<myBigData.size();i++){
        if(i>0 && myBigData[i]<myBigData[i-1])
        {
            cout<<"error\n";
            return;
        }    
    }
    cout<<"success\n";
}
int main(){
    
    cout<<timeCounting(1,[](){
        SortType testType=quickSort;
        test(testType);
    })<<'\n';
    cout<<timeCounting(1,[&](){
        SortType testType=quickSort;
        testBigData(testType);
    })<<'\n';
    return 0;
}