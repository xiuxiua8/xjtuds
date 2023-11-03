#include <iostream>
#include "../hw2/SeqStack.cpp"
#include "../hw2/SeqQueue.cpp"
//#define NULL nullptr
#define cin std::cin 
#define cout std::cout
#define endl std::endl


template <class T>
class BinaryTreeNode{
private:
    T data;           			
    BinaryTreeNode<T>*  left; 	
    BinaryTreeNode<T>*  right; 	


public:
	BinaryTreeNode(); 	                   
	BinaryTreeNode(const T& elem);	
	BinaryTreeNode(const T& elem, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r);
	~BinaryTreeNode(){};
	T value() const;				
	BinaryTreeNode<T>*  leftchild() const;	
	BinaryTreeNode<T>*  rightchild() const;	
	void  setLeftchild(BinaryTreeNode<T>*);	
	void  setRightchild(BinaryTreeNode<T>*);	
	void  setValue(const T& val);		
	bool  isLeaf() const;		
};



template<class T>
BinaryTreeNode<T>::BinaryTreeNode(){
    data = T();
    left = nullptr;
    right = nullptr;
}

template<class T>
BinaryTreeNode<T>::BinaryTreeNode(const T& elem){
    data = elem;
    left = nullptr;
    right = nullptr;
}

template<class T>
BinaryTreeNode<T>::BinaryTreeNode(const T& elem, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r){
    data = elem;
    left = l;
    right = r;
}


template<class T>
T BinaryTreeNode<T>::value() const{
    return this->data;
}

template<class T>
BinaryTreeNode<T>*  BinaryTreeNode<T>::leftchild() const{
    return this->left;
}

template<class T>
BinaryTreeNode<T>*  BinaryTreeNode<T>::rightchild() const{
    return this->right;
}

template<class T>
void BinaryTreeNode<T>::setLeftchild(BinaryTreeNode<T>* Lchild){
    this->left = Lchild;
}

template<class T>
void BinaryTreeNode<T>::setRightchild(BinaryTreeNode<T>* Rchild){
    this->right = Rchild;
}

template<class T>
void BinaryTreeNode<T>::setValue(const T& Value){
    this->data = Value;
}

template<class T>
bool BinaryTreeNode<T>::isLeaf() const{
    return false;
}


enum Tag{L, R, M};
template <class T>
class StackNode{
public:
    BinaryTreeNode<T>* pointer;
    Tag tag;
    StackNode() {pointer = nullptr; tag = L;}
    StackNode(BinaryTreeNode<T>* ptr,Tag tg){pointer = ptr; tag =tg;}
};




template <class T>
class BinaryTree{
protected:
    BinaryTreeNode<T>* root;        			
public:
    BinaryTree() {root = nullptr;} 			
    BinaryTree(BinaryTreeNode<T>* r) {root = r;}
    ~BinaryTree() { DeleteBinaryTree(root); };    	
    bool isEmpty() { return root==nullptr; };  		
    void visit(const BinaryTree<T>& curr){cout << curr.root->value() << " ";} 
    BinaryTreeNode<T>*& Root() {return root;};   	
    void CreateTree(const T& data, BinaryTreeNode<T>* lefttree, BinaryTreeNode<T>* righttree);
    void CreateTree(BinaryTreeNode<T> *&r); 
	void DeleteBinaryTree(BinaryTreeNode<T>* root); 

	void PreOrder(BinaryTreeNode<T>* root); 	
	void InOrder(BinaryTreeNode<T>* root); 	
	void PostOrder(BinaryTreeNode<T>* root); 	
    void PreOrderLikeRecusion(BinaryTreeNode<T>* root);
	void InOrderLikeRecusion(BinaryTreeNode<T>* root);
	void PostOrderLikeRecusion(BinaryTreeNode<T>* root);
	void PreOrderWithoutRecusion(BinaryTreeNode<T>* root);
	void InOrderWithoutRecusion(BinaryTreeNode<T>* root); 
	void PostOrderWithoutRecusion(BinaryTreeNode<T>* root);
	void LevelOrder(BinaryTreeNode<T>* root);	
};


template<class T> 
void BinaryTree<T>::CreateTree(const T& data, BinaryTreeNode<T>* leftTree, BinaryTreeNode<T>* rightTree) {
    root = new BinaryTreeNode<T>(data, leftTree, rightTree);
    BinaryTree(root);
}




template<class T> 
void BinaryTree<T>::DeleteBinaryTree(BinaryTreeNode<T>* Root){
    if (Root != NULL) {
        DeleteBinaryTree(Root->leftchild());   
        DeleteBinaryTree(Root->rightchild());  
        Root->~BinaryTreeNode();
    }
}

template<class T>
void BinaryTree<T>::PreOrder(BinaryTreeNode<T>* root){
    if (root == NULL)  return;
    visit(root);			
    PreOrder(root->leftchild());		
    PreOrder(root->rightchild());		
}


template<class T>
void BinaryTree<T>::InOrder(BinaryTreeNode<T>* root){
    if (root == NULL) return;
    InOrder(root->leftchild());
    visit(root);
    InOrder(root->rightchild());
}


template<class T>
void BinaryTree<T>::PostOrder(BinaryTreeNode<T>* root){
    if (root == NULL) return;
    PostOrder(root->leftchild());
    PostOrder(root->rightchild());
    visit(root);
}


template<class T>
void BinaryTree<T>::PreOrderLikeRecusion(BinaryTreeNode <T> * root){
    SeqStack<BinaryTreeNode<T>*> tStack(10);
    BinaryTreeNode<T>* pointer = root;
    while(!tStack.IsEmpty() || pointer){
        if (pointer){
            visit(pointer);               
            tStack.Push(pointer);                  
            pointer = pointer->leftchild();     
        } else{	                                    
            pointer = tStack.Pop();               
            //tStack.Pop();                            
            pointer = pointer->rightchild(); }
    }
}


template<class T>
void BinaryTree<T>::InOrderLikeRecusion(BinaryTreeNode <T> * root){
    SeqStack<BinaryTreeNode<T>*> tStack(10);
    BinaryTreeNode<T>* pointer = root;
    while(!tStack.IsEmpty() || pointer){
        if (pointer){            
            tStack.Push(pointer);                   
            pointer = pointer->leftchild();     
        } else{	                                    
            pointer = tStack.Pop();  
            visit(pointer);
            //tStack.Push(pointer);               
            //tStack.Pop();                            
            pointer = pointer->rightchild(); }  
    }
}

template<class T>
void BinaryTree<T>::PostOrderLikeRecusion(BinaryTreeNode <T> * root){
    SeqStack<StackNode<T>* > tStack(10);
    StackNode<T>* Tagptr = new StackNode<T>(root, L);

    while (!tStack.IsEmpty() || Tagptr->pointer != nullptr ){
        while (Tagptr->pointer != nullptr) {
            StackNode<T>* tem = new StackNode<T>(Tagptr->pointer, L);
            tStack.Push(tem);
            Tagptr->pointer = Tagptr->pointer->leftchild();
        }
        if (!tStack.IsEmpty()) {
            Tagptr = tStack.Pop();
            if (Tagptr->tag == L ) {
                StackNode<T>* tem = new StackNode<T>(Tagptr->pointer, R);
                tStack.Push(tem);
                Tagptr->pointer = Tagptr->pointer->rightchild();
            } else {
                visit(Tagptr->pointer);
                Tagptr->pointer = nullptr;
            }
        }
    }
}

template<class T>
void BinaryTree<T>::PreOrderWithoutRecusion(BinaryTreeNode <T> * root){
    SeqStack<BinaryTreeNode<T>*> tStack(10);
    BinaryTreeNode<T>* pointer = root;
    if (!pointer) {return;};
    tStack.Push(pointer);
    while(!tStack.IsEmpty()){  //use the feature of stack
        pointer = tStack.Pop();
        visit(pointer);
        if(pointer->rightchild()){
            tStack.Push(pointer->rightchild());// first in then out
        }
        if (pointer->leftchild()){
            tStack.Push(pointer->leftchild());
        }
    }
    //does queue do the same work?
}   




template<class T>
void BinaryTree<T>::InOrderWithoutRecusion(BinaryTreeNode <T> * root){
    SeqStack<StackNode<T>*> tStack(10);
    //BinaryTreeNode<T>* pointer = root;
    StackNode<T>* Tagptr = new StackNode<T>();
    Tagptr->pointer = root;
    
    if (!Tagptr->pointer) {return;};
    tStack.Push(Tagptr);
    while(!tStack.IsEmpty()){  
        Tagptr = tStack.Pop();
        if (Tagptr->tag == L) {
            if(Tagptr->pointer->rightchild()){
                StackNode<T>* tem = new StackNode<T>(Tagptr->pointer->rightchild(), L);
                tStack.Push(tem);
            }
            StackNode<T>* tem = new StackNode<T>(Tagptr->pointer, R);
            tStack.Push(tem);
            if (Tagptr->pointer->leftchild()){
                StackNode<T>* tem = new StackNode<T>(Tagptr->pointer->leftchild(), L);
                tStack.Push(tem);
            } 
        } else visit(Tagptr->pointer);
    }
}
template<class T>
void BinaryTree<T>::PostOrderWithoutRecusion(BinaryTreeNode <T> * root){
    SeqStack<StackNode<T>*> tStack(10);
    //BinaryTreeNode<T>* pointer = root;
    StackNode<T>* Tagptr = new StackNode<T>();
    Tagptr->pointer = root;
    
    if (!Tagptr->pointer) {return;};
    tStack.Push(Tagptr);
    while(!tStack.IsEmpty()){  
        Tagptr = tStack.Pop();
        if (Tagptr->tag == L) {
            StackNode<T>* tem = new StackNode<T>(Tagptr->pointer, R);
            tStack.Push(tem);
            if (Tagptr->pointer->rightchild()){
                StackNode<T>* tem = new StackNode<T>(Tagptr->pointer->rightchild(), L);
                tStack.Push(tem);
            }
            if (Tagptr->pointer->leftchild()){
                StackNode<T>* tem = new StackNode<T> (Tagptr->pointer->leftchild(), L);
                tStack.Push(tem);
            }
        } else if (Tagptr->tag == R) {
            StackNode<T>* tem = new StackNode<T>(Tagptr->pointer, M);
            tStack.Push(tem);
        } else {
            visit(Tagptr->pointer);
        }
    }
}


template<class T>
void BinaryTree<T>::LevelOrder(BinaryTreeNode <T> * root){
    SeqQueue<BinaryTreeNode<T>*> Queue(16);
    Queue.InQueue(root);
    while(!Queue.IsEmpty()) {
        //cout << "Starting Level Order Traversal..." << endl;
        BinaryTreeNode<T>* pointer = Queue.OutQueue();
        if (pointer->leftchild()){
            Queue.InQueue(pointer->leftchild());
        }
        if (pointer->rightchild()){
            Queue.InQueue(pointer->rightchild());
        }
        visit(pointer);
    }
}


void traversalTest() {
    BinaryTreeNode<int> node1(1);
    BinaryTreeNode<int> node2(2);
    BinaryTreeNode<int> node3(3);
    BinaryTreeNode<int> node4(4);
    BinaryTreeNode<int> node5(5);
    BinaryTreeNode<int> node6(6);

    node1.setLeftchild(&node2);
    node1.setRightchild(&node3);
    node2.setLeftchild(&node4);
    node4.setRightchild(&node5);
    node5.setRightchild(&node6);

    BinaryTree<int> tree(&node1);

    cout << "PreOrder traversal:" << endl;
    tree.PreOrder(tree.Root());
    cout << endl;
    cout << "InOrder traversal:" << endl;
    tree.InOrder(tree.Root());
    cout << endl;
    cout << "PostOrder traversal:" << endl;
    tree.PostOrder(tree.Root());
    cout << endl;

    cout << "PreOrder traversal Like recursion:" << endl;
    tree.PreOrderLikeRecusion(tree.Root());
    cout << endl;
    cout << "InOrder traversal Like recursion:" << endl;
    tree.InOrderLikeRecusion(tree.Root());
    cout << endl;
    cout << "PostOrder traversal Like recursion:" << endl;
    tree.PostOrderLikeRecusion(tree.Root());
    cout << endl;

    cout << "PreOrder traversal Without recursion:" << endl;
    tree.PreOrderWithoutRecusion(tree.Root());
    cout << endl;
    cout << "InOrder traversal Without recursion:" << endl;
    tree.InOrderWithoutRecusion(tree.Root());
    cout << endl;
    cout << "PostOrder traversal Without recursion:" << endl;
    tree.PostOrderWithoutRecusion(tree.Root());
    cout << endl;

    cout << "LevelOrder:" << endl;
    tree.LevelOrder(tree.Root());
    cout << endl;

}

int main() {
    traversalTest();
    return 0;
}
