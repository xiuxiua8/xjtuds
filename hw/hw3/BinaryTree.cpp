
#include <iostream>
#include "../hw2/SeqStack.cpp"
//#define NULL nullptr
#define cin std::cin 
#define cout std::cout
#define endl std::endl


template <class T>
class BinaryTreeNode{
private:
    T data;           			//二叉树结点数据域
    BinaryTreeNode<T>*  left; 	//二叉树结点指向左子树的指针
    BinaryTreeNode<T>*  right; 	//二叉树结点指向左子树的指针


public:
	BinaryTreeNode(); 	                   //缺省构造函数
	BinaryTreeNode(const T& elem);	//给定数据的构造函数
	BinaryTreeNode(const T& elem, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r);
		//给定数据的左右指针的构造函数
	~BinaryTreeNode(){};
	T value() const;				//返回当前结点的数据
	BinaryTreeNode<T>*  leftchild() const;	//返回当前结点指向左子树的指针
	BinaryTreeNode<T>*  rightchild() const;	//返回当前结点指向右子树的指针
	void  setLeftchild(BinaryTreeNode<T>*);	//设置当前结点的左子树
	void  setRightchild(BinaryTreeNode<T>*);	//设置当前结点的右子树
	void  setValue(const T& val);		//设置当前结点的数据域
	bool  isLeaf() const;		//判定当前结点是否为叶结点,若是返回true
};



template<class T>
BinaryTreeNode<T>::BinaryTreeNode(){
    data = nullptr;
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





template <class T>
class BinaryTree{
protected:
    BinaryTreeNode<T>* root;        			//二叉树根结点指针
public:
    BinaryTree() {root = nullptr;} 			//构造函数
    BinaryTree(BinaryTreeNode<T>* r) {root = r;}
    ~BinaryTree() { DeleteBinaryTree(root); };    	//析构函数
    bool isEmpty() { return root==nullptr; };  		//判断二叉树是否为空树
    void visit(BinaryTree<T>& curr){cout <<curr->data << " ";} //访问当前结点
    BinaryTreeNode<T>*& Root() {return root;};   	//返回二叉树的根结点
    void CreateTree(const T& data, BinaryTreeNode<T>* lefttree, BinaryTreeNode<T>* righttree);
	//以data作为根结点，ltree作为树的左子树，rtree作为树的右子树，构造一棵新二叉树 
    void CreateTree(BinaryTreeNode<T> *&r); //根据先序遍历序列构造二叉树
	void DeleteBinaryTree(BinaryTreeNode<T>* root); //删除二叉树及其子树

	void PreOrder(BinaryTreeNode<T>* root); 	//前序遍历二叉树或其子树
	void InOrder(BinaryTreeNode<T>* root); 	//中序遍历二叉树或其子树
	void PostOrder(BinaryTreeNode<T>* root); 	//后序遍历二叉树或其子树
	void PreOrderWithoutRecusion(BinaryTreeNode<T>* root);//非递归前序遍历
	void InOrderWithoutRecusion(BinaryTreeNode<T>* root); //非递归中序遍历
	void PostOrderWithoutRecusion(BinaryTreeNode<T>* root);//非递归后序遍历
	void LevelOrder(BinaryTreeNode<T>* root);	 //按层次遍历二叉树或其子树
};


template<class T> 
void BinaryTree<T>::CreateTree(const T& data, BinaryTreeNode<T>* leftTree, BinaryTreeNode<T>* rightTree) {
    root = BinaryTreeNode<T>(data, leftTree, rightTree);
    BinaryTree(root);
}




template<class T> 
void BinaryTree<T>::DeleteBinaryTree(BinaryTreeNode<T>* Root){
    if (Root != NULL) {
        DeleteBinaryTree(Root->left);   // 递归删除左子树
        DeleteBinaryTree(Root->right);  // 递归删除右子树
        delete Root;                    // 删除当前节点
    }
}

template<class T>
void BinaryTree<T>::PreOrder(BinaryTreeNode<T>* root){
    if (root == NULL)  return;
    visit(root->value());			//访问根结点
    PreOrder(root->leftchild());		//先序遍历左子树
    PreOrder(root->rightchild());		//先序遍历右子树
}


template<class T>
void BinaryTree<T>::PreOrderWithoutRecusion(BinaryTreeNode <T> * root){
    SeqStack<BinaryTreeNode<T>* > tStack;
    BinaryTreeNode<T>* pointer = root;
    while(!tStack.empty() || pointer){
        if (pointer){
            visit(pointer->value());                //访问当前结点
            tStack.push(pointer);                   //当前结点地址入栈
            pointer = pointer->leftchild();     //当前链接结构指向左孩子
        } else{	                                    //左子树访问完毕，转向访问右子树
            pointer = tStack.top();                 //当前链接结构指向栈顶的元素
            tStack.pop();                                //栈顶元素出栈
            pointer = pointer->rightchild(); }
    }
}



int main2(){
    return 0;
}