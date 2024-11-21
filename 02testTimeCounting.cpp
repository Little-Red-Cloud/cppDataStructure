#include <iostream>
#include "./include/TimeCounting.h"
#include <math.h>

using namespace std;

double f1(int n,double a[],double x)
{
    int i;
    double p=a[0];
    for(i=1;i<=n;i++)
        p+=(a[i]*pow(x,i));
    return p;
}

double f2(int n,double a[],double x)
{
	int i;
	double p=a[n];
	for(i=n;i>0;i--)
		p=a[i-1]+x*p;
	return p;
}

int main(){
	int N=100000;
	double a[N];
	for(int i=0;i<N;i++)
		a[i]=i;
	int n=1;
	cout<<"input run times:\n";
	cin>>n;
	cout<<"f1 n:"<<n<<endl<<"f1 time(s):"<<timeCounting(n,[&](){f1(N,a,1.1);})<<endl;
	cout<<"f2 n:"<<n<<endl<<"f2 time(s):"<<timeCounting(n,[&](){f2(N,a,1.1);})<<endl;
	return 0;
}
