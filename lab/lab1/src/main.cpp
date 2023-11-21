#include <iostream>
#include "seqstack.cpp"
#include "stuff.cpp"
#include <string.h>
//#include <vector>
//#define vector std::vector<int> 

struct StackItem {
    int index;
    int currentVolume;
    int size;

    // Constructor
    StackItem(int i, int vol, int s) : index(i), currentVolume(vol), size(s) {}
    StackItem() : index(0), currentVolume(0), size(0) {}
};


/*
void printSolution(Stuff<int>* set[], SeqStack<StackItem> solution, int size) {
    printf("(");
    for (int i = 0; i < size; i++) {
        printf("%d", set[solution.Pop().index - 1]->mysize());
        if (i < size - 1) {
            printf(",");
        }
    }
    printf(")\n");
}*/





void printSolution(Stuff<int>* set[], SeqStack<StackItem> solution, int size) {
    const StackItem* list = solution.GetStackArray1();
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
                currentIndex = stack.GetTop().index;
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





int main() {
    int T = 10; //bagVolume
    Stuff<int>* stuffSet[10];
    int stuffNum = 6;


    stuffSet[0] = new Stuff<int>(1, 1);
    stuffSet[1] = new Stuff<int>(8, 1);
    stuffSet[2] = new Stuff<int>(4, 1);
    stuffSet[3] = new Stuff<int>(3, 1);
    stuffSet[4] = new Stuff<int>(5, 1);
    stuffSet[5] = new Stuff<int>(2, 1, 5);

    for (int i = 0; i < stuffNum - 1; i++) {
        stuffSet[i]->write(i);  
    }

    std::string log = "solution:\n";

    /*printf("Enter the number of items: ");
    scanf("%d", &stuffNum);

    printf("Enter the target volume T: ");
    scanf("%d", &T);*/



    printf("Possible subsets that sum up to %d:\n", T);
    packup(stuffSet, log, stuffNum, T);

    printf("end! ");

    return 0;



}
