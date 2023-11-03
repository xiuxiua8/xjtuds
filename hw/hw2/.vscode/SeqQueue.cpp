#include <iostream>
#define cin std::cin 
#define cout std::cout
#define endl std::endl
//FIFO(First In First Out)
template<class Type>
class SeqQueue{
    private:
        Type *queue;		//栈底指针
        int maxsize;             	//顺序栈的最大空间
        int front,rear;        	 	//栈顶指针
    public: 
        SeqQueue(int size);      	//构造函数,构造一个数组空间大小为size的空栈
        //~SeqQueue() {delete [] elem; }           	//析构函数，销毁队列，释放队列空间
        ~SeqQueue();
        int IsEmpty() const {return front == rear; }     	//判断栈是否为空栈，若是，返回1；否则返回0
        int IsFull() {return (rear + 1)%maxsize == front; }         	//判断栈是否是满栈，若是，返回1；否则返回0
        void SeqQueueClear(Type &Q){front = rear =0;}	//将队列清空
        int SeqQueueLength() const {return (rear - front + maxsize)%maxsize;}    
        void InQueue(Type &e);   //入队列操作，将元素e从队列尾插入队列
        Type &OutQueue();	//出队列操作，将当前队列头元素删除，并返回其值 
        Type &GetFront();          	//返回队列头元素    
};
/*
template<class Type> 
SeqQueue<Type>::~SeqQueue() { 
    delete queue;
}
*/

template<class Type>
SeqQueue<Type>::SeqQueue(int size):maxsize(size){
    queue = new Type[maxsize];
    if(queue == NULL)    { cout<<"分配内存失败" ; exit(0);}
    front = 0;
    rear = 0;
}

template<class Type> 
SeqQueue<Type>::~SeqQueue() { 
    delete queue;
    //delete top;
    //delete maxsize;
}

template<class Type> 
void SeqQueue<Type>::InQueue (Type &e){
    if( IsFull() ){cout<<"队列已满！"<<endl; exit(0);}
    queue[rear] = e;
    rear = (rear+1)%maxsize;
}

template<class Type> 
Type & SeqQueue<Type>::OutQueue(){
    if( IsEmpty() ){ cout<<"队列为空！"<<endl; exit(0); }
    Type e=queue[front];
    front = (front+1)%maxsize;
    return e;
}

template<class Type> 
Type &SeqQueue<Type>::GetFront(){
    if( IsEmpty() ){cout<<"队列为空！"<<endl; exit(0);}
    return queue[front];
}


int main() {
    /*
    SeqQueue<int> Queue(10); // Creating a stack with a maximum size of 10

    cout << "Pushing elements into the stack:" << endl;
    for (int i = 1; i <= 5; ++i) {
        Stack.InQueue(i * 10);
        cout << "Pushed: " << i * 10 << endl;
    }

    cout << "Stack length: " << Stack.SeqStackLength() << endl;

    cout << "Top element: " << Stack.GetTop() << endl;

    cout << "Popping elements from the stack:" << endl;
    while (!Stack.IsEmpty()) {
        cout << "Popped: " << Stack.Pop() << endl;
    }

    cout << "Stack length: " << Stack.SeqStackLength() << endl;
*/
    cout << "Stack length: "<< endl;
    return 0;
}
