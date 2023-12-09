#include <iostream>
#include "seqstack.cpp"
#include "stuff.cpp"
#include <string.h>
#include <string>

struct StackItem {
    int index;
    int currentVolume;
    int size;

    // Constructor
    StackItem(int i, int vol, int s) : index(i), currentVolume(vol), size(s) {}
    StackItem() : index(0), currentVolume(0), size(0) {}
};


void printSolution(Stuff<int>* set[], SeqStack<StackItem> solution, int size) {
    //const StackItem* list = solution.GetStackArray1();
    const StackItem* list = solution.base;
    printf("(");
    for (int i = 0; i < size; i++) {
        printf("%d", set[list[i].index]->mysize());
        if (i < size - 1) {
            printf(",");
        }
    }
    printf(")\n");

}


void packup(Stuff<int>* set[], std::string log, int stuffnum, int T) {
    SeqStack<StackItem> stack(10);
    //SeqStack<> stack(10);
    int currentIndex = 0; 
    int currentVolume = 0; 
    int currentSize = 0;


    //stack.Push(StackItem(0, 0, 0));
    //从第 0 个物品开始，当前体积为 0，当前解的大小为 0

    while (true) {
        currentVolume += set[currentIndex]->mysize();
        currentSize++;
        stack.Push(StackItem(currentIndex, currentVolume, currentSize));
        if (currentVolume == T) {
            //stack.printSolution(set, currentSize);
            printSolution(set, stack, currentSize);
        } else {
            if (currentVolume > T) {
                stack.Pop();
                currentVolume -= set[currentIndex]->mysize(); 
                currentSize--;
            }
        }
        if ((currentIndex >= stuffnum - 1) && (currentVolume != T)) {
            currentIndex = stack.GetTop().index;
            if (currentIndex == stuffnum - 1) {
                stack.Pop();
                currentVolume -= set[currentIndex]->mysize();
                if (!stack.IsEmpty()) {
                    currentIndex = stack.GetTop().index;
                }
                currentSize--;
            }
            stack.Pop();
            currentVolume -= set[currentIndex]->mysize();
            currentSize--;
        }
        if (currentVolume == T) {
            currentIndex = stack.GetTop().index;
            if ((currentIndex == stuffnum - 1) && (stack.End().index != stuffnum - 1)) {
                stack.Pop();
                currentVolume -= set[currentIndex]->mysize();
                currentIndex = stack.GetTop().index;
                currentSize--;
            }      
            stack.Pop();      
            currentVolume -= set[currentIndex]->mysize();
            currentSize--;
        }
        currentIndex++;
        if (stack.End().index == stuffnum - 1) {
            break;
    }
    }

}
int text() {
        int T = 10; //bagVolume
    Stuff<int>* stuffSet[10];
    int stuffNum = 6;

    std::string log = "solution:\n";


    stuffSet[0] = new Stuff<int>(1, 1);
    stuffSet[1] = new Stuff<int>(8, 1);
    stuffSet[2] = new Stuff<int>(4, 1);
    stuffSet[3] = new Stuff<int>(3, 1);
    stuffSet[4] = new Stuff<int>(5, 1);
    stuffSet[5] = new Stuff<int>(2, 1);

    for (int i = 0; i < stuffNum; i++) {
        stuffSet[i]->write(i);  
    }
}




int main() {

    int T; // bagVolume
    int stuffNum;
    std::string log = "solution:\n";
    Stuff<int>* stuffSet[100];

    std::cout << "Enter the number of items: ";
    std::cin >> stuffNum;

    std::cout << "Enter the size of each item: ";
    for (int i = 0; i < stuffNum; i++) {
        int size;
        std::cin >> size;
        stuffSet[i] = new Stuff<int>(size, 1); // input size, value is 1, message is the stuff's index
        stuffSet[i]->write(i);
    }

    std::cout << "Enter the target volume T: ";
    std::cin >> T;

    std::cout << "Possible solution that the sum is " << T << ":\n";
    packup(stuffSet, log, stuffNum, T);
    std::cout << "end! ";

    return 0;
}


int main0(int argc, char* argv[]) {
    int T; // bagVolume
    int stuffNum;
    std::string log = "solution:\n";
    Stuff<int>* stuffSet[100];

    // Check if the correct number of command line arguments is provided
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <num_items> <sizes> <target_volume>" << std::endl;
        return 1;
    }

    // Parse command line arguments
    stuffNum = std::stoi(argv[1]);
    T = std::stoi(argv[3]);

    // Initialize stuffSet array
    for (int i = 0; i < stuffNum; i++) {
        stuffSet[i] = new Stuff<int>(std::stoi(argv[2+i]), 1);
        stuffSet[i]->write(i);
    }

    // Rest of your code remains unchanged

    return 0;
}
