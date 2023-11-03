#include <iostream>
#define cin std::cin 
#define cout std::cout
#define endl std::endl
//FIFO(First In First Out)

template<class Type>
class SeqQueue{
    private:
        Type *queue;		
        int maxsize;            
        int front,rear;
        int fillCount;
        void indexcheck(); 	
    public: 
        SeqQueue(int size);      	//构造函数,构造一个数组空间大小为size的空栈
        //~SeqQueue() {delete [] elem; }           	//析构函数，销毁队列，释放队列空间
        ~SeqQueue();
        int IsEmpty() const {return fillCount == 0; }     	//判断栈是否为空栈，若是，返回1；否则返回0
        int IsFull() {return (rear + 1)%maxsize == front; }         	//判断栈是否是满栈，若是，返回1；否则返回0
        void SeqQueueClear(Type &Q){front = 0; rear =0;}	//将队列清空
        int SeqQueueLength() const {return (rear - front + maxsize) % maxsize;}    
        void InQueue(const Type &e) ;   //入队列操作，将元素e从队列尾插入队列
        Type &OutQueue();	//出队列操作，将当前队列头元素删除，并返回其值 
        Type &GetFront();          	//返回队列头元素    
};

template<class Type>
SeqQueue<Type>::SeqQueue(int size):maxsize(size) {
    front = 0;
    rear = 0;
    fillCount = 0;
    queue = new Type[maxsize];
    if (queue  == NULL ) {
        cout << "" << endl;
        exit(0);
    }
}


template<class Type>
SeqQueue<Type>::~SeqQueue() {
    delete[] queue;
}

template<class Type>
void SeqQueue<Type>::indexcheck() {
    if (front >= maxsize) {
        front = front % maxsize;
    }
    if (rear >= maxsize) {
        rear = rear % maxsize;
    }
    if (fillCount > maxsize) {
        fillCount = maxsize;
    }
}

template<class Type>
void SeqQueue<Type>::InQueue(const Type &e){
    queue[rear] = e;
    rear++;
    fillCount++;
    indexcheck();
}

template<class Type>
Type& SeqQueue<Type>::OutQueue() {
    Type& returnfirst = queue[front];
    if (this->IsEmpty()) {
            cout << "queue underflow" << endl;
    } else {
        front = (front + 1) % maxsize;
        fillCount--;
    }
    return returnfirst;
}

template<class Type>
Type& SeqQueue<Type>::GetFront() {
    if (this->IsEmpty()) {
        cout << "queue is empty" << endl;
    }
    return queue[front];
}

int main01() {
    SeqQueue<int> Queue(10); // Creating a queue with a maximum size of 10
    cout << "Pushing elements into the queue:" << endl;
    for (int i = 1; i <= 9; ++i) {
        Queue.InQueue(i * 10);
        cout << "Pushed: " << i * 10 << endl;
    }

    cout << "queue length: " << Queue.SeqQueueLength() << endl;

    cout << "Top element: " << Queue.GetFront() << endl;

    cout << "Popping elements from the Queue:" << endl;
    while (!Queue.IsEmpty()) {
        cout << "Out: " << Queue.OutQueue() << endl;
    }

    cout << "QUEUE length: " << Queue.SeqQueueLength() << endl;

    return 0;
}