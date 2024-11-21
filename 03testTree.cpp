#include<Tree.h>
#include<stdio.h>

int main(){
    BinaryTree<int> t;
    for(int i=0;i<10;i++){
        t.insert(i);
    }
    for(BinaryTree<int>::preOrderIterator p=t.preOrderBegin();p!=t.preOrderEnd();p++)
        printf("%d\n",*p);
    printf("Correct");
    return 0;
}