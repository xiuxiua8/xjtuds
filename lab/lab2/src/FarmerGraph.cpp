#include <iostream>

#include <queue>
#include "graph.cpp"

#define SOUTH 0
#define NORTH 1

class FarmerCrossingGraph : public Graphl {
private:
    static const int NUM_STATES = 16;

    // Helper function to check if a state is safe
    bool isSafe(int state) {
        int farmer = (state & 8) >> 3;
        int wolf = (state & 4) >> 2;
        int cabbage = (state & 2) >> 1;
        int sheep = state & 1;

        if ((wolf == sheep) && (farmer != wolf)) {
            return false;  // wolf eats sheep
        } else if ((sheep == cabbage) && (farmer != sheep)) {
            return false;  // sheep eats cabbage
        }

        return true;
    }

    // Helper function to check if two states can be connected by a valid move
    bool isValidMove(int state1, int state2) {
        int diff = state1 ^ state2;  // XOR to find the differing bits

        // Only one bit should be different (representing the move of the farmer)
        //return ((diff != 0) && ((diff & (diff - 1)) == 0));
        return (diff == 8 || diff == 9 || diff == 10 || diff == 12);
    }

public:
    FarmerCrossingGraph() : Graphl(NUM_STATES) {
        // Create edges between safe and valid states
        for (int state1 = 0; state1 < NUM_STATES; state1++) {
            for (int state2 = 0; state2 < NUM_STATES; state2++) {
                if (isSafe(state1) && isSafe(state2) && isValidMove(state1, state2)) {
                    setEdge(state1, state2, 1);
                }
            }
        }
    }

    void printState(int state) {
        std::cout << "(";
        std::cout << ((state & 8) >> 3);  // Farmer
        std::cout << ((state & 4) >> 2);  // Wolf
        std::cout << ((state & 2) >> 1);  // Sheep
        std::cout << (state & 1);         // Cabbage
        std::cout << ")";
    }


    // Perform BFS to find a path from goalState to startState
    void findSolution(int startState, int goalState) {
        std::queue<int> Q;
        Q.push(goalState);

        int pred[NUM_STATES];
        for (int i = 0; i < NUM_STATES; i++) {
            pred[i] = -1;
        }

        Visited[goalState] = true;

        while (!Q.empty()) {
            int currentState = Q.front();
            Q.pop();

            for (int next = FirstAdj(currentState); next != -1; next = NextAdj(currentState, next)) {
                if (!Visited[next]) {
                    Q.push(next);
                    Visited[next] = true;
                    pred[next] = currentState;
                }
            }
        }

        // Print the solution path
        int currentState = startState;
        while (currentState != -1) {
            printState(currentState);
            std::cout << " -> ";
            currentState = pred[currentState];
        }
        std::cout << "target State" << std::endl;

        currentState = startState;
        int nextState;
        int count = 0;
        while (currentState != -1) {
            nextState = pred[currentState];
            int diff = currentState ^ nextState;
            count ++;
            if (diff == 8) {
                std::cout << "第" << count << "步，"<< "农夫只身到达对岸。" << std::endl;         
            } else if (diff == 9) {
                std::cout << "第" << count << "步，"<< "农夫带羊到达对岸。" << std::endl;   
            } else if (diff == 10) {
                std::cout << "第" << count << "步，"<< "农夫带菜到达对岸。" << std::endl;   
            } else if (diff == 12) {
                std::cout << "第" << count << "步，"<< "农夫带狼到达对岸。" << std::endl;
            }
            currentState = nextState;
        }
        std::cout << "结束！" << std::endl;
    }

};

int main() {
    FarmerCrossingGraph farmerCrossingGraph;

    const int startState = 0;  // Initial state: 0000 (farmer, wolf, cabbage, sheep on the south bank)
    const int goalState = 15;  // Goal state: 1111 (farmer, wolf, cabbage, sheep on the north bank)

    std::cout << "Solution Path:" << std::endl;
    farmerCrossingGraph.findSolution(startState, goalState);
    //farmerCrossingGraph.displayGraph();

    return 0;
}
