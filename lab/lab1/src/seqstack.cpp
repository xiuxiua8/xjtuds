#include <iostream>
//#include "stuff.cpp"
template<class Type>
class SeqStack{
    private:
        
        int maxsize;   
        int top; 
    public: 
        Type *base;
        SeqStack(int size) {
            maxsize = size;
            base = new Type[maxsize];
            top = -1;
        }

        ~SeqStack() {
            //delete[] base;
        }

        int IsEmpty() const {
            return top == -1;
        }

        int IsFull() {
            return top == maxsize - 1;
        }

        void SeqStackClear() {
            top = -1;
        }

        int SeqStackLength() { 
            return top + 1;
        }

        void Push(const Type &e) {
            if (!IsFull()) {
                top++;
                base[top] = e; 
            } else { 
                std::cout << "the stack is full!" << std::endl;
                throw std::out_of_range("Stack is full");
            }
        }

        Type &Pop() { 
            if (!IsEmpty()) {
                return base[top--];
            } else { 
                //std::cout << "the stack is empty!" << std::endl;
                //throw std::out_of_range("Stack is empty");
            }
        }
        
        Type &GetTop(){
            if (!IsEmpty()) {
                return base[top];
            } else { 
                std::cout << "the stack is empty!" << std::endl;
                throw std::out_of_range("Stack is empty");

            }
        }

        Type* GetStackArray() const {
            return base;
        }

        const Type* GetStackArray1() const {
            // Return a copy of the array to prevent external modification
            Type* copyArray = new Type[maxsize];
            std::copy(base, base + maxsize, copyArray);
            return copyArray;
        }

        Type &End() const{ 
            if (!IsEmpty()) {
                return base[0];
            } else { 
                return base[0]; //todosomething
            }
        }




};



