#include <iostream>
#include <iomanip>
#include <queue>
// Assuming you have a linklist.h header file with the necessary declarations
#include "linklist.h"

typedef int Vextype;   // Define Vextype if not already defined
typedef int ArcValType;  // Define ArcValType if not already defined
typedef int ArcInfoType;  // Define ArcInfoType if not already defined
typedef int WeightType;  // Define WeightType if not already defined
typedef int InfoType;  // Define InfoType if not already defined
typedef int AdjType;  // Define AdjType if not already defined

#define MAX_VAL 999999  // Define MAX_VAL if not already defined
#define MAX_VEX_NUM 20
typedef enum { DG, AG, WDG, WAG } GraphKind;

class Graph {
public:
    int numVertex;
    int numEdge;
    bool *Visited;
    int *InDegree;

    Graph(int numVert) : numVertex(numVert), numEdge(0) {
        Visited = new bool[numVert];
        InDegree = new int[numVert];

        for (int i = 0; i < numVert; ++i) {
            Visited[i] = false;
            InDegree[i] = 0;
        }
    }

    ~Graph() {
        delete[] Visited;
        delete[] InDegree;
    }

    virtual int FirstAdj(int oneVertex) = 0;
    virtual int NextAdj(int oneVertex, int preVertex) = 0;

    int VerticesNum() { return numVertex; }
    int EdgesNum() { return numEdge; }

    virtual int weight(int from, int to) = 0;
    virtual void setEdge(int from, int to, int weight) = 0;
    virtual void delEdge(int from, int to) = 0;
    
    virtual void DFS(int V) {
        for (int i = 0; i < numVertex; i++)
            Visited[i] = false;
        DFSHelper(V);
    }

    virtual void BFS(int V) {
        for (int i = 0; i < numVertex; i++)
            Visited[i] = false;
        BFSHelper(V);
    }

    virtual void TopSort_DFS() {
        for (int i = 0; i < numVertex; i++)
            Visited[i] = false;
        for (int i = 0; i < numVertex; i++)
            if (Visited[i] == false)
                Do_TopSort(i);
    }
protected:
    virtual void DFSHelper(int V) = 0;
    virtual void BFSHelper(int V) = 0;
    virtual void Do_TopSort(int V) = 0;

};

typedef struct {
    GraphKind kind;
    int vexnum;
    Vextype vexs[MAX_VEX_NUM];
    AdjType adj[MAX_VEX_NUM][MAX_VEX_NUM];
} AdjGraph;

class Graphm : public Graph {
private:
    int **AdjMatrix;

        void DFSHelper(int V) override {
        Visited[V] = true;
        std::cout << V << "\t";
        for (int w = FirstAdj(V); w != -1; w = NextAdj(V, w))
            if (Visited[w] == false)
                DFSHelper(w);
    }

    void BFSHelper(int V) override {
        std::queue<int> Q;
        Visited[V] = true;
        Q.push(V);
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            std::cout << v << "\t";
            for (int w = FirstAdj(v); w != -1; w = NextAdj(v, w)) {
                if (Visited[w] == false) {
                    Visited[w] = true;
                    Q.push(w);
                }
            }
        }
    }

    void Do_TopSort(int V) override {
        Visited[V] = true;
        for (int w = FirstAdj(V); w != -1; w = NextAdj(V, w))
            if (Visited[w] == false)
                Do_TopSort(w);
        std::cout << V << "\t";
    }

public:
    Graphm(int numVert) : Graph(numVert) {
        AdjMatrix = new int *[numVertex];
        for (int i = 0; i < numVertex; i++)
            AdjMatrix[i] = new int[numVertex];

        for (int i = 0; i < numVertex; i++)
            for (int j = 0; j < numVertex; j++)
                AdjMatrix[i][j] = 0;
    }

    ~Graphm() {
        for (int i = 0; i < numVertex; i++)
            delete[] AdjMatrix[i];
        delete[] AdjMatrix;
    }

    int weight(int from, int to) override {
        return AdjMatrix[from][to];
    }

    void setEdge(int from, int to, int weight) override {
        if (AdjMatrix[from][to] == 0) {
            numEdge++;
            InDegree[to]++;
        }
        AdjMatrix[from][to] = weight;
    }

    void delEdge(int from, int to) override {
        if (AdjMatrix[from][to] != 0) {
            numEdge--;
            InDegree[to]--;
        }
        AdjMatrix[from][to] = 0;
    }

    int FirstAdj(int oneVertex) override {
        for (int i = 0; i < numVertex; i++)
            if (AdjMatrix[oneVertex][i] != 0)
                return i;
        return -1;
    }

    int NextAdj(int oneVertex, int preVertex) override {
        for (int i = preVertex + 1; i < numVertex; i++)
            if (AdjMatrix[oneVertex][i] != 0)
                return i;
        return -1;
    }

    void displayGraph() {
        std::cout << "Adjacency Matrix:" << std::endl;
        for (int i = 0; i < numVertex; ++i) {
            for (int j = 0; j < numVertex; ++j) {
                std::cout << std::setw(3) << AdjMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

struct listUnit {
    int vertex;
    int weight;
};

class Graphl : public Graph {
private:
    LList<listUnit> *vexList;

        void DFSHelper(int V) override {
        Visited[V] = true;
        std::cout << V << "\t";
        for (int w = FirstAdj(V); w != -1; w = NextAdj(V, w))
            if (Visited[w] == false)
                DFSHelper(w);
    }

    void BFSHelper(int V) override {
        std::queue<int> Q;
        Visited[V] = true;
        Q.push(V);
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            std::cout << v << "\t";
            for (int w = FirstAdj(v); w != -1; w = NextAdj(v, w)) {
                if (Visited[w] == false) {
                    Visited[w] = true;
                    Q.push(w);
                }
            }
        }
    }

    void Do_TopSort(int V) override {
        Visited[V] = true;
        for (int w = FirstAdj(V); w != -1; w = NextAdj(V, w))
            if (Visited[w] == false)
                Do_TopSort(w);
        std::cout << V << "\t";
    }

public:
    Graphl(int numVert) : Graph(numVert) {
        vexList = new LList<listUnit>[numVertex];
    }

    ~Graphl() {
        delete[] vexList;
    }

    int weight(int from, int to) override {
        Link<listUnit> *temp = vexList[from].head;
        while (temp->next != nullptr && temp->next->element.vertex != to)
            temp = temp->next;
        return temp->next->element.weight;
    }

    int FirstAdj(int oneVertex) override {
        Link<listUnit> *temp = vexList[oneVertex].head;
        if (temp->next != nullptr)
            return temp->next->element.vertex;
        return -1;
    }

    int NextAdj(int oneVertex, int preVertex) override {
        Link<listUnit> *temp = vexList[oneVertex].head;
        while (temp->next != nullptr && temp->next->element.vertex <= preVertex)
            temp = temp->next;
        if (temp->next != nullptr)
            return temp->next->element.vertex;
        return -1;
    }

    void setEdge(int from, int to, int weight) override {
        Link<listUnit> *temp = vexList[from].head;
        while (temp->next != nullptr && temp->next->element.vertex < to)
            temp = temp->next;
        if (temp->next == nullptr) {
            temp->next = new Link<listUnit>;
            temp->next->element.vertex = to;
            temp->next->element.weight = weight;
            numEdge++;
            InDegree[to]++;
            return;
        }
        if (temp->next->element.vertex == to) {
            temp->next->element.weight = weight;
            return;
        }
        if (temp->next->element.vertex > to) {
            Link<listUnit> *other = temp->next;
            temp->next = new Link<listUnit>;
            temp->next->element.vertex = to;
            temp->next->element.weight = weight;
            temp->next->next = other;
            numEdge++;
            InDegree[to]++;
        }
    }

    void delEdge(int from, int to) override {
        Link<listUnit> *temp = vexList[from].head;
        while (temp->next != nullptr && temp->next->element.vertex < to)
            temp = temp->next;
        if (temp->next == nullptr)
            return;
        if (temp->next->element.vertex == to) {
            Link<listUnit> *other = temp->next->next;
            delete temp->next;
            temp->next = other;
            numEdge--;
            InDegree[to]--;
        }
    }

    void displayGraph() {
        std::cout << "Adjacency List:" << std::endl;
        for (int i = 0; i < numVertex; ++i) {
            std::cout << "Vertex " << i << ": ";
            Link<listUnit> *temp = vexList[i].head->next;  // Skip the dummy header
            while (temp != nullptr) {
                std::cout << "(" << temp->element.vertex << ", " << temp->element.weight << ") ";
                temp = temp->next;
            }
            std::cout << std::endl;
        }
    }

};

void test() {
    const int numVertices = 5;
    Graphm graphm(numVertices);
    Graphl graphl(numVertices);

    // Add edges to the graphs
    graphm.setEdge(0, 1, 1);
    graphm.setEdge(0, 3, 2);
    graphm.setEdge(1, 2, 3);
    graphm.setEdge(2, 3, 4);
    graphm.setEdge(3, 4, 5);

    graphl.setEdge(0, 1, 1);
    graphl.setEdge(0, 3, 2);
    graphl.setEdge(1, 2, 3);
    graphl.setEdge(2, 3, 4);
    graphl.setEdge(3, 4, 5);

    // Display the graphs
    graphm.displayGraph();
    graphl.displayGraph();

    std::cout << "DFS on Graphm: ";
    graphm.DFS(0);
    std::cout << std::endl;

    std::cout << "BFS on Graphm: ";
    graphm.BFS(0);
    std::cout << std::endl;

    std::cout << "Topological Sort on Graphm: ";
    graphm.TopSort_DFS();
    std::cout << std::endl;

    std::cout << "DFS on Graphl: ";
    graphl.DFS(0);
    std::cout << std::endl;

    std::cout << "BFS on Graphl: ";
    graphl.BFS(0);
    std::cout << std::endl;

    std::cout << "Topological Sort on Graphl: ";
    graphl.TopSort_DFS();
    std::cout << std::endl;

}

int main0() {
    test();
    return 0;
}