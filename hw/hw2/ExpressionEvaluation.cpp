#include <iostream>
#include <string>
using namespace std;

template <typename Type>
class SeqStack {
private:
    Type *base;      // 栈底指针
    int maxsize;     // 顺序栈的最大空间
    int top;         // 栈顶指针

public: 
    SeqStack(int size);        // 构造函数,构造一个数组空间大小为size的空栈
    ~SeqStack();              // 析构函数，销毁栈，释放栈空间
    int IsEmpty() const;      // 判断栈是否为空栈，若是，返回1；否则返回0
    int IsFull();             // 判断栈是否是满栈，若是，返回1；否则返回0
    void SeqStackClear();     // 将栈清空
    int SeqStackLength();     // 栈的长度，即栈中元素的个数
    void Push(Type &e);       // 入栈操作，将元素e插入栈顶
    Type &Pop();              // 出栈操作，将当前栈顶元素删除，并返回其值
    Type &GetTop();           // 返回栈顶元素
};

template <typename Type>
SeqStack<Type>::SeqStack(int size) : maxsize(size) {
    base = new Type[maxsize];
    if(base == NULL) { 
        cout << "分配内存失败"; 
        exit(0);
    }
    top = 0;
}

template <typename Type>
SeqStack<Type>::~SeqStack() {
    delete[] base;
}

template <typename Type>
int SeqStack<Type>::IsEmpty() const {
    return top == 0 ? 1 : 0;
}

template <typename Type>
int SeqStack<Type>::IsFull() {
    return top == maxsize ? 1 : 0;
}

template <typename Type>
void SeqStack<Type>::SeqStackClear() {
    top = 0;
}

template <typename Type>
int SeqStack<Type>::SeqStackLength() {
    return top;
}

template <typename Type>
void SeqStack<Type>::Push(Type &e) {
    if (IsFull()) {
        cout << "栈空间已满" << endl;
        exit(0);
    } else {
        base[top++] = e; 
    }
}

template <typename Type>
Type &SeqStack<Type>::Pop() {
    if (IsEmpty()) { 
        cout << "栈为空" << endl; 
        exit(0); 
    } else {
        return base[--top];
    }
}

template <typename Type>
Type &SeqStack<Type>::GetTop() {
    if (IsEmpty()) { 
        cout << "栈为空" << endl; 
        exit(0); 
    } else {
        return base[top - 1];
    }
}

int main() {
    SeqStack<int> stack(10);

    for(int i = 0; i < 10; i++) {
        stack.Push(i);
    }

    SeqStack<char> stackchar(10);

    for(int i = 0; i < 10; i++) {
        string A = "a/b^c+d*e-a*c";
        stackchar.Push(A[i]);
    }

    while(!stack.IsEmpty()) {
        cout << stack.Pop() << " ";
    }

    while(!stackchar.IsEmpty()) {
        cout << stackchar.Pop() << " ";
    }
    
    return 0;
}



