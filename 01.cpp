#include<stdio.h>
#include <stdlib.h>

using namespace std;
int main(){
    FILE* fp=fopen("myData.txt","w");
    srand(time_t(NULL));
    fprintf(fp,"vector<int> data={");
    for(int i=0;i<100000;i++){
        fprintf(fp,"%d,",rand()%1000000);
        srand(time_t(NULL)+i);
    }
    fprintf(fp,"%d};",rand()%1000000);
    fclose(fp);
}