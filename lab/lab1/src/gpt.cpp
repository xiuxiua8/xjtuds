#include <iostream>
 
using namespace std;
class Stack {
private:
    const int CAPACITY; //Stack的存储空间大小定义为常量，需要通过初始化列表来赋值
    int top;            //栈顶
    int * data;         //线性表
public:
    Stack();            //无参构造函数
    Stack(int cpc, int top = -1); //有参构造函数，其中cpc用于初始化常量CAPACITY，top定义为默认值-1
    ~Stack();            //析构函数用于释放内存
    void Push(int e);    //入栈
    int Pop();          //出栈
    int GetTop();        //获取栈顶元素
    bool IsEmpty();      //测试栈是否已空
    bool IsFull();       //测试栈是否已满
    void PrintStack();   //打印栈的内容
    int end();
};
Stack::Stack(): CAPACITY(12) {
    this->top = -1;
    this->data = new int[CAPACITY];
}
 
Stack::Stack(int cpc, int top): CAPACITY(cpc) {
    this->top = top;
    this->data = new int[CAPACITY];
}
 
Stack::~Stack() {
    delete[] this->data;
}
 
bool Stack::IsEmpty() {
    return this->top == -1;
}
 
bool Stack::IsFull() {
    return this->top == CAPACITY;
}
 
int Stack::GetTop() {
    return this->data[this->top];
}
 
void Stack::Push(int e) {
    this->data[++ this->top] = e;
}
 
int Stack::Pop() {
    if(this->top < 0) {
        return -2;//error
    }
    return this->data[top --];
}
 
void Stack::PrintStack() {
    for(int i = 0; i <= this->top; i ++) {
        cout << data[i] << endl;
    }
}
 
int Stack::end(){
    return data[0];
}
//以10个元素的物品、背包存放重量25为例
int main() {
    const int SIZE = 10;
    int goods[SIZE] = {1, 8, 4, 3, 5, 2};
    int totalWeight = 10;
    int idx = 0;
    Stack stack;
    while(true) {
        totalWeight -= goods[idx];
        stack.Push(idx);
        if(totalWeight == 0) {
            stack.PrintStack();
            cout << endl;
        } else {
            if(totalWeight < 0) {
                stack.Pop();
                totalWeight += goods[idx];
            }
        }
        if((idx >= SIZE - 1) && (totalWeight != 0)) {   //到最后未找到就弹出栈顶元素，然后从栈顶元素继续向后找
            idx = stack.GetTop();
            if(idx == SIZE - 1) {    //如果栈顶元素是最后一个则弹出两个元素
                stack.Pop();
                totalWeight += goods[idx];
                idx = stack.GetTop();
            }
            stack.Pop();
            totalWeight += goods[idx];
        }
        if(totalWeight == 0) {  //如果找到答案，也继续向后找新的一组答案
            idx = stack.GetTop();
            if((idx == SIZE - 1)&&(stack.end()!=SIZE-1)) {  //栈顶元素不为最后一个才弹出两次
                stack.Pop();
                totalWeight += goods[idx];
                idx = stack.GetTop();
            }
            stack.Pop();
            totalWeight += goods[idx];
        }
        idx++;
        if (stack.end() == SIZE - 1) {
            break;
        }
    }
    //system("pause");
    return 0;
}