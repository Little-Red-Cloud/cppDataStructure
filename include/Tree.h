#ifndef TREE_H_
#define TREE_H_

#include<vector>
#include<stdexcept>

using std::vector;

template<typename dataType>
class BinaryTreeNode{
private:
    dataType data;
    BinaryTreeNode *parent,*left,*right;
public:
    BinaryTreeNode(){
        parent=left=right=nullptr;
    }
    BinaryTreeNode(const dataType& data,BinaryTreeNode* parent=nullptr,BinaryTreeNode * left=nullptr,BinaryTreeNode* right=nullptr)
        :data(data),parent(parent),left(left),right(right){}
    BinaryTreeNode(const BinaryTreeNode& other)
        :data(other.data),parent(other.parent),left(other.left),right(other.right){}
    BinaryTreeNode& operator=(const BinaryTreeNode& other){
        data=other.data;
        parent=other.parent;
        left=other.left;
        right=other.right;
    }
    void setLeftChild(BinaryTreeNode* ptr){left=ptr;};
    void setRightChild(BinaryTreeNode* ptr){right=ptr;};
    void setParent(BinaryTreeNode* ptr){parent=ptr;};
    BinaryTreeNode* getLeftChild()const{return left;}
    BinaryTreeNode* getRightChild()const{return right;}
    BinaryTreeNode* getParent()const{return parent;}
    dataType& getData(){return data;}
    ~BinaryTreeNode(){}
};

template<typename dataType,typename comp=std::less<dataType>>
class BinaryTree{
protected:
    BinaryTreeNode<dataType> head;
    size_t size;
    size_t depth;
    vector<BinaryTreeNode<dataType>*> preOrder,inOrder;
    comp comparator;

    void updatePreOrder(BinaryTreeNode<dataType>* root){
        if(root==head.getLeftChild())
            preOrder.clear();
        if(root){
            preOrder.push_back(root);
            updatePreOrder(root->getLeftChild());
            updatePreOrder(root->getRightChild());
        }
    }

    void updateinOrder(BinaryTreeNode<dataType>* root){
        if(root==head.getLeftChild())
            inOrder.clear();
        if(root){
            updateinOrder(root->getLeftChild());
            inOrder.push_back(root);
            updateinOrder(root->getRightChild());
        }
    }


public:
    BinaryTree():size(0),depth(0){}
    void insert(const dataType& data){
        BinaryTreeNode<dataType> *prev=&head,*now=head.getLeftChild();
        while(now!=nullptr){
            if(comparator(now->getData(),data)){
                prev=now;
                now=now->getRightChild();
            }else{
                prev=now;
                now=now->getLeftChild();
            }
        }
        now=new BinaryTreeNode<dataType>(data,prev);
        if(prev==&head){
            prev->setLeftChild(now);
            return;
        }
        if(comparator(prev->getData(),data)){
            prev->setRightChild(now);
        }
        else{
            prev->setLeftChild(now);
        }
        size++;
    }
    ~BinaryTree(){
        updatePreOrder(head.getLeftChild());
        for(auto p:preOrder){
            delete p;
        }
    }

    class preOrderIterator{
    private:
        BinaryTreeNode<dataType>* ptr;
        size_t index;
        const BinaryTree<dataType,comp>* out;
    public:
        preOrderIterator(BinaryTreeNode<dataType>* ptr,size_t index,const BinaryTree<dataType,comp>* out):ptr(ptr),index(index),out(out){}
        preOrderIterator(const preOrderIterator& other):ptr(other.ptr),index(other.index),out(other.out){}
        preOrderIterator& operator=(const preOrderIterator& other){
            ptr=other.ptr;
            index=other.index;
            out=other.out;
            return *this;
        }
        dataType operator*()const{
            return ptr->getData();
        }
        bool operator==(const preOrderIterator& other)const{
            return ptr==other.ptr && index==other.index && out==other.out;
        }
        bool operator!=(const preOrderIterator& other)const{
            return !operator==(other);
        }
        bool isEnd()const{return index==0&&ptr==nullptr;}
        preOrderIterator operator++(int){
            if(isEnd())
                throw std::runtime_error("overflow");
            preOrderIterator ret=*this;
            index++;
            if(index>=out->preOrder.size()){
                index=0;
                ptr=nullptr;
            }
            else
                ptr=out->preOrder[index];
            return ret;
        }
        preOrderIterator operator--(int){
            preOrderIterator ret=*this;
            if(index==0)
                throw std::underflow_error();
            index--;
            ptr=out->preOrder[index];
            return ret;
        }
    };
    preOrderIterator preOrderBegin() {
        updatePreOrder(head.getLeftChild());
        return preOrderIterator(preOrder.empty() ? nullptr : preOrder[0], 0,this);
    }
    preOrderIterator preOrderEnd(){return preOrderIterator(nullptr,0,this);}
    
    class inOrderIterator{
    private:
        BinaryTreeNode<dataType>* ptr;
        size_t index;
        const BinaryTree<dataType,comp>* out;
    public:
        inOrderIterator(BinaryTreeNode<dataType>* ptr,size_t index,const BinaryTree<dataType,comp>* out):ptr(ptr),index(index),out(out){}
        inOrderIterator(const inOrderIterator& other):ptr(other.ptr),index(other.index),out(other.out){}
        inOrderIterator& operator=(const inOrderIterator& other){
            ptr=other.ptr;
            index=other.index;
            out=other.out;
            return *this;
        }
        dataType operator*()const{
            return ptr->getData();
        }
        bool operator==(const inOrderIterator& other)const{
            return ptr==other.ptr && index==other.index && out==other.out;
        }
        bool operator!=(const inOrderIterator& other)const{
            return !operator==(other);
        }
        bool isEnd()const{return index==0&&ptr==nullptr;}
        inOrderIterator operator++(int){
            if(isEnd())
                throw std::overflow_error();
            inOrderIterator ret=*this;
            index++;
            if(index>=out->inOrder.size()){
                index=0;
                ptr=nullptr;
            }
            else
                ptr=out->inOrder[index];
            return ret;
        }
        inOrderIterator operator--(int){
            inOrderIterator ret=*this;
            if(index==0)
                throw std::underflow_error();
            index--;
            ptr=out->inOrder[index];
            return ret;
        }
    };
    inOrderIterator inOrderBegin() {
        updateinOrder(head.getLeftChild());
        return inOrderIterator(inOrder.empty() ? nullptr : inOrder[0], 0,this);
    }
    inOrderIterator inOrderEnd(){return inOrderIterator(nullptr,0,this);}

};

#endif