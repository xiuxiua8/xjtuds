#include <iostream>

template<class Type>
class Stuff{
    private:
        Type *message;
        int size;   
        int value; 
    public: 
        Stuff() : size(0), value(0), message(nullptr) {}

        Stuff(int S, int V) {
            size = S; 
            value = V;
            message = nullptr;
        }
        
        Stuff(int S, int V, const Type &M) {
            size = S; 
            value = V;
            message = new Type;
            *message = M;
        }

        ~Stuff() {
            delete message;
        }

        int mysize() { 
            return size;
        }

        int myvalue() {
            return value;
        }

        void write(const Type &newMessage) {
            // Allocate memory for the message
            message = new Type;
            // Copy the value
            *message = newMessage;
        }

        Type &read() const {
            if (message != nullptr) {
                return *message;
            } else {
                throw std::runtime_error("Message is not allocated.");
            }
        }


};



