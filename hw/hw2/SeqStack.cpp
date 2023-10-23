#include <iostream>
#define cin std::cin 
#define cout std::cout
#define endl std::endl

template<class Type>
class SeqStack{
    private:
        Type *base;		//栈底指针
        int maxsize;             	//顺序栈的最大空间
        int top;        	 	//栈顶指针
    public: 
        SeqStack(int size);      	//构造函数,构造一个数组空间大小为size的空栈
        ~SeqStack();            	//析构函数，销毁栈，释放栈空间
        int IsEmpty() const;       	//判断栈是否为空栈，若是，返回1；否则返回0
        int IsFull();            	//判断栈是否是满栈，若是，返回1；否则返回0
        void SeqStackClear();    	//将栈清空
        int SeqStackLength();    	//栈的长度，即栈中元素的个数
        void Push(Type &e);      	//入栈操作，将元素e插入栈顶
        Type &Pop();           	//出栈操作，将当前栈顶元素删除，并返回其值
        Type &GetTop();         	//返回栈顶元素
};




template<class Type>
SeqStack<Type>::SeqStack(int size):maxsize(size){
    base = new Type[maxsize];
    if(base == NULL)    { cout<<"分配内存失败" ; exit(0);}
    top = 0;
}

template<class Type> 
SeqStack<Type>::~SeqStack() { 
    delete base;
    delete top;
    delete maxsize;
}

template<class Type>
int SeqStack<Type>::IsEmpty() const {
    return top == 0;
}

template<class Type>
int SeqStack<Type>::IsFull() {
    return top == maxsize;
}

template<class Type>
void SeqStack<Type>::SeqStackClear() {
    top = 0;
}

template<class Type>
int SeqStack<Type>::SeqStackLength() {
    return top;
}

template<class Type>
void SeqStack<Type>::Push(Type &e){
     if( IsFull() ){
        cout<<"栈空间已满"<<endl;
        exit(0);
     } else {
        base[top++] = e; 
     }
 }

template<class Type>
//将当前栈顶元素出栈
Type& SeqStack<Type>::Pop(){  
    if( IsEmpty())
    { cout<<"栈为空"<<endl; exit(0); }
    else return base[--top];
}


template<class Type>
//返回当前栈顶元素
Type& SeqStack<Type>::GetTop(){   
    if( IsEmpty())
       { cout<<"栈为空"<<endl; exit(0); }
    else  return base[top-1];
}

int main(){
    cout << "Hello, World!" << endl;
    return 0;
}
