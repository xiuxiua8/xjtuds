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



int test() {
        // 示例用法
    SeqStack<Stuff<int>*> stack(10);

    // 入栈操作
    
    Stuff<int>* stuff1 = new Stuff<int>(1, 1, 'a');
    stack.Push(stuff1);
    Stuff<int>* stuff2 = new Stuff<int>(8, 1, 'b');
    stack.Push(stuff2);
    Stuff<int>* stuff3 = new Stuff<int>(4, 1, 'c');
    stack.Push(stuff3);
    Stuff<int>* stuff4 = new Stuff<int>(3, 1, 'd');
    stack.Push(stuff4);
    Stuff<int>* stuff5 = new Stuff<int>(5, 1, 'e');
    stack.Push(stuff5);
    Stuff<int>* stuff6 = new Stuff<int>(2, 1, 'f');
    stack.Push(stuff6);
    Stuff<int>* stuff7 = new Stuff<int>(6, 1);
    stack.Push(stuff7);

    // 出栈操作
    std::cout << "出栈元素：" << stack.Pop()->mysize() << std::endl;

    // 获取栈顶元素
    std::cout << "栈顶元素：" << stack.GetTop()->mysize() << std::endl;

    // 获取栈的长度
    std::cout << "栈的长度：" << stack.SeqStackLength() << std::endl;

    // 清空栈
    stack.SeqStackClear();

    return 0;

}

void helper0(Stuff<int>* set[], std::string log, int T, int stuffnum) {
    SeqStack<Stuff<int>*> stack(10);
    int content = 0;
    for (int i = 0; i < stuffnum; i++) {
        stack.Push(set[i]);
        content = content + set[i]->mysize();
        if (content > T) {
            stack.Pop();
            continue;
        }   
        if (content == T) {
            //do some thing ..
        }
        for (int j = i; j < stuffnum; j++) {
            while (content + set[j]->mysize() <= T) {
                stack.Push(set[j]);
                content = content + set[j]->mysize();
                //log it 
                continue;   
            }
            if (content + set[j]->mysize() > T) {
                continue;
            }
            
            
            
        }

        
    }
}



void helper1(Stuff<int>* set[], std::string log, int T, int stuffnum) {
    SeqStack<Stuff<int>*> stack(10);
    int content = 0;
    int ptr = 0;
    int count = 0;
    int i = 0;
    while (content != T && i < stuffnum) {
        int i = ptr;
        stack.Push(set[i]);
        content = content + set[i]->mysize();
        //log it 
        //i++;
        if (content == T) {
            
        }
    }

}
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
    StackItem* list = solution.GetStackArray();
    printf("(");
    for (int i = 0; i < size; i++) {
        printf("%d", set[list[i].index - 1]->mysize());
        if (i < size - 1) {
            printf(",");
        }
    }
    printf(")\n");
}

void packup(Stuff<int>* set[], std::string log, int stuffnum, int T) {
    SeqStack<StackItem> stack(10);
    //SeqStack<> stack(10);
    /*int content = 0;
    int ptr = 0;
    int count = 0;
    int i = 0;*/


    stack.Push(StackItem(0, 0, 0));//从第 0 个物品开始，当前体积为 0，当前解的大小为 0
    StackItem current;

    while (!stack.IsEmpty()) {
        if (stack.GetTop().currentVolume != T) {
            //StackItem current = stack.Pop();
        }
        
        StackItem current = stack.Pop();

        if (current.currentVolume == T) {
            //do stuff
            printSolution(set, stack, current.size);
            continue;
        } else if (!stack.IsEmpty()) {
            current = stack.GetTop();
            current.index++;
        }

        for (int i = current.index; i < stuffnum; i++) {
            if (current.currentVolume + set[i]->mysize() <= T) {
                current.size += 1;
                current.currentVolume += set[i]->mysize();
                stack.Push(StackItem(i + 1, current.currentVolume, current.size));
                std::cout << "push" <<i + 1 << current.currentVolume << current.size << std::endl;
            }
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
