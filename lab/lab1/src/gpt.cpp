#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void findSolutions(int T, const vector<int>& items) {
    int n = items.size();
    stack<int> itemStack; // Stack to store the selected items
    int currentVolume = 0; // Current volume of items in the stack
    int currentIndex = 0; // Current index for selecting items

    while (true) {
        // Check if the current volume is equal to the total volume
        if (currentVolume == T) {
            // Output the solution
            cout << "(";
            bool isFirst = true;
            for (int item : itemStack) {
                if (!isFirst) cout << ",";
                cout << items[item];
                isFirst = false;
            }
            cout << ")\n";
        }

        // Check if there are more items to select
        if (currentIndex < n) {
            // Select the next item
            itemStack.push(currentIndex);
            currentVolume += items[currentIndex];
            currentIndex++;
        } else {
            // Backtrack if there are no more items to select
            if (itemStack.empty()) break; // No more solutions
            int lastItem = itemStack.top();
            itemStack.pop();
            currentVolume -= items[lastItem];
            currentIndex = lastItem + 1;
        }
    }
}

int main() {
    int T = 10;
    vector<int> items = {1, 8, 4, 3, 5, 2};

    findSolutions(T, items);

    return 0;
}
