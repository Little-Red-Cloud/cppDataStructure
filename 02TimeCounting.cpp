#include <stdio.h>
#include <time.h>
#include<stdexcept>
#include "./include/TimeCounting.h"

double timeCounting(int n,std::function<void()> func){
	clock_t start,stop;
	start=clock();
	if(n<=0)
		throw std::runtime_error("n should be bigger than zero.\n");
	for(int i=0;i<n;i++)
		func();
	stop=clock();
	double time=(double)(stop-start)/CLOCKS_PER_SEC;
	return time;
}


