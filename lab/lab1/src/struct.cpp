#include <iostream>

struct StackItem {
    int index;
    int currentVolume;
    int size;

    // Constructor
    StackItem(int i, int vol, int s) : index(i), currentVolume(vol), size(s) {}
};

int main() {
    // Example of creating a StackItem object using the constructor
    StackItem myItem(0, 0, 0);

    // Accessing the members of the created object
    std::cout << "Index: " << myItem.index << ", Current Volume: " << myItem.currentVolume << ", Size: " << myItem.size << std::endl;

    return 0;
}
