#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include <climits>
#include "Graph.h"
#include "List/MyList.h"
#include "List/MyPriorityQueueList.h"

class GraphList : public Graph
{
public:
    GraphList(int v = 10, bool directed = true);
    ~GraphList();

    void createEmptyGraph();
    bool generateRandomEdges(int maxRange, int rate);

    bool addVertex();
    bool deleteVertex(int v);

    bool addEdge(int v1, int v2, int range = 1);
    bool deleteEdge(int v1, int v2);

    int getEdge(int v1, int v2) const;
    int getEdgeCount(int v) const;

    int getTotalVertex() const;
    int getTotalEdge() const;

    int getVertexNumberAt(int index) const;

    void initializeNode();
    bool isConnected();
    bool isCycle();
    bool isTree();

    bool DFS(int v); //true - meet a visited vertex; false - not

    MyList<int>* dijkstra(int v1, int v2);
    GraphList* prim();


private:
    struct Node {
        int number;
        bool visited;
        int accDistance;
        int prev;
        bool primAdded;
    };
    struct Edge {
        int from;
        int to;
        int distance;
    };
    int vNumber;
    MyList<MyList<int> *> *edgeList;
    MyList<Node *> *nodeList;

    bool directed;

};

#endif // GRAPHLIST_H
