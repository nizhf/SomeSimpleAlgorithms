#ifndef GRAPHLIST_H_INCLUDED
#define GRAPHLIST_H_INCLUDED

#include <limits.h>
#include "../List/MyList.h"
#include "Graph.h"
#include "../List/MyPriorityQueueList.h"


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

inline GraphList::GraphList(int v, bool directed) : directed(directed) {
    int vMax = v > 0? v : 0;
    vNumber = 0;
    nodeList = new MyList<Node *>;
    edgeList = new MyList<MyList<int> *>;
    for (int i = 0; i < vMax; i++)
        addVertex();
}

inline GraphList::~GraphList() {
    for (int i = 0; i < getTotalVertex(); i++)
        deleteVertex(getVertexNumberAt(i));
    delete nodeList;
    delete edgeList;
}

inline void GraphList::createEmptyGraph() {

}

inline bool GraphList::generateRandomEdges(int maxRange, int rate) {
    srand((unsigned)time(0));
    if (directed) {
        for (int i = 0; i < getTotalVertex(); i++) {
            for (int j = 0; j < getTotalVertex(); j++) {
                if (rand() % 100 >= rate) {
                    if (!addEdge(i, j, rand() % maxRange + 1))
                        return false;
                }
            }
        }
    }
    else {
        for (int i = 0; i < getTotalVertex(); i++) {
            for (int j = 0; j < getTotalVertex() - i; j++) {
                if (rand() % 100 >= rate) {
                    if (!addEdge(i, j, rand() % maxRange + 1))
                        return false;
                }
            }
        }
    }
    return true;
}

inline bool GraphList::addVertex() {
    Node *newNode = new Node{vNumber, false, INT_MAX, -1, false};
    nodeList->pushBack(newNode, vNumber);
    MyList<int> *newList = new MyList<int>;
    edgeList->pushBack(newList, vNumber);
    vNumber++;
    return true;
}

inline bool GraphList::deleteVertex(int v) {
    bool found = false;
    for (int i = 0; i < getTotalVertex(); i++) {
        if (nodeList->keyAt(i) == v) {
            found = true;
            delete nodeList->at(i);
            nodeList->removeKey(v);
            break;
        }
    }
    if (!found)
        return false;

    delete edgeList->search(v);
    edgeList->removeKey(v);
    for (int i = 0; i < getTotalVertex(); i++)
        edgeList->at(i)->removeKey(v);
    return true;
}

inline bool GraphList::addEdge(int v1, int v2, int range) {
    if (range < 1)
        return false;
    bool found1 = false;
    bool found2 = false;
    for (int i = 0; i < getTotalVertex(); i++) {
        if (nodeList->keyAt(i) == v1)
            found1 = true;
        if (nodeList->keyAt(i) == v2)
            found2 = true;
        if (found1 && found2)
            break;
    }
    if (!found1 || !found2)
        return false;


    bool add12 = edgeList->search(v1)->pushBack(range, v2);
    if (directed)
        return add12;
    else {
        bool add21 = edgeList->search(v2)->pushBack(range, v1);
        return add12 && add21;
    }
}

inline bool GraphList::deleteEdge(int v1, int v2) {
    bool found1 = false;
    for (int i = 0; i < getTotalVertex(); i++) {
        if (nodeList->keyAt(i) == v1) {
            found1 = true;
            break;
        }
    }
    if (!found1)
        return false;

    bool del12 = edgeList->search(v1)->removeKey(v2);
    if (directed)
        return del12;
    else {
        bool del21 = edgeList->search(v2)->removeKey(v1);
        return del12 && del21;
    }
}

inline int GraphList::getEdge(int v1, int v2) const {
    bool found1 = false;
    bool found2 = false;
    for (int i = 0; i < getTotalVertex(); i++) {
        if (nodeList->keyAt(i) == v1)
            found1 = true;
        if (nodeList->keyAt(i) == v2)
            found2 = true;
        if (found1 && found2)
            break;
    }
    if (!found1 || !found2)
        return 0;

    try {
        return edgeList->search(v1)->search(v2);
    }
    catch (const char *err) {
        return 0;
    }
}

inline int GraphList::getEdgeCount(int v) const {
    bool found = false;
    for (int i = 0; i < getTotalVertex(); i++) {
        if (nodeList->keyAt(i) == v) {
            found = true;
            break;
        }
    }
    if (!found)
        return -1;

    return edgeList->search(v)->size();
}

inline int GraphList::getTotalVertex() const {
    return nodeList->size();
}

inline int GraphList::getTotalEdge() const {
    int e = 0;
    for (int i = 0; i < edgeList->size(); i++) {
        e += edgeList->at(i)->size();
    }
    if (directed)
        return e;
    else
        return e / 2;
}

inline int GraphList::getVertexNumberAt(int index) const {
    if (index < 0 || index >= getTotalVertex())
        return -1;
    return nodeList->keyAt(index);
}

inline void GraphList::initializeNode() {
    for (int i = 0; i < nodeList->size(); i++) {
        nodeList->at(i)->visited = false;
        nodeList->at(i)->accDistance = INT_MAX;
        nodeList->at(i)->prev = -1;
        nodeList->at(i)->primAdded = false;
    }
}

inline bool GraphList::isConnected() {
    initializeNode();
    DFS(getVertexNumberAt(0));
    for (int i = 0; i < getTotalVertex(); i++) {
        if (!nodeList->at(i)->visited)
            return false;
    }
    return true;

}

inline bool GraphList::isCycle() {
    initializeNode();
    for (int i = 0; i < getTotalVertex(); i++) {
        initializeNode();
        if (DFS(getVertexNumberAt(i)))
            return true;
    }
    return false;
}

inline bool GraphList::isTree() {
    return !isCycle() && isConnected();
}

inline bool GraphList::DFS(int v) {
    bool meet = false;
    if (nodeList->search(v)->visited) return true;
    nodeList->search(v)->visited = true;
    for (int i = 0; i < getEdgeCount(v); i++) {
        int vNext = edgeList->search(v)->keyAt(i);
        if (DFS(vNext))
            meet = true;
    }
    return meet;
}

inline MyList<int>* GraphList::dijkstra(int v1, int v2) {
    bool found1 = false;
    bool found2 = false;
    for (int i = 0; i < getTotalVertex(); i++) {
        if (nodeList->keyAt(i) == v1)
            found1 = true;
        if (nodeList->keyAt(i) == v2)
            found2 = true;
        if (found1 && found2)
            break;
    }
    if (!found1 || !found2)
        return NULL;

    initializeNode();
    nodeList->search(v1)->accDistance = 0;
    MyPriorityQueueList<int> pq;

    for (int i = 0; i < getTotalVertex(); i++)
        pq.insert(getVertexNumberAt(i), nodeList->at(i)->accDistance);

    for (int i = 0; i < getTotalVertex(); i++) {
        int vCurrent = pq.extractMin();
        int dCurrent = nodeList->search(vCurrent)->accDistance;
        if (dCurrent == INT_MAX)
            break;
        for (int j = 0; j < getEdgeCount(vCurrent); j++) {
            int vNext = edgeList->search(vCurrent)->keyAt(j);
            int newDistance = dCurrent + getEdge(vCurrent, vNext);
            if (newDistance < nodeList->search(vNext)->accDistance) {
                nodeList->search(vNext)->accDistance = newDistance;
                nodeList->search(vNext)->prev = vCurrent;
                pq.changeKeyWithData(vNext, newDistance);
                pq.sortKey();
            }
        }
    }

    MyList<int> *path = new MyList<int>;
    int vCurrent = v2;
    while (vCurrent != -1) {
        if (nodeList->search(vCurrent)->accDistance != INT_MAX)
            path->pushFront(nodeList->search(vCurrent)->accDistance, vCurrent);
        vCurrent = nodeList->search(vCurrent)->prev;
    }
    return path;
}

inline GraphList* GraphList::prim() {
    GraphList *mst = new GraphList(0, directed);

    for (int i = 0, ii = 0; i < vNumber; i++) {
        mst->addVertex();
        if (mst->getVertexNumberAt(ii) == getVertexNumberAt(ii))
            ii++;
        else
            mst->deleteVertex(i);
    }

    if (!isConnected())
        return mst;

    initializeNode();
    nodeList->at(0)->accDistance = 0;
    MyPriorityQueueList<int> pq;
    for (int i = 0; i < getTotalVertex(); i++)
        pq.insert(getVertexNumberAt(i), nodeList->at(i)->accDistance);

    for (int i = 0; i < getTotalVertex(); i++) {
        int vCurrent = pq.extractMin();
        nodeList->search(vCurrent)->visited = true;
        int dCurrent = nodeList->search(vCurrent)->accDistance;
        if (dCurrent == INT_MAX)
            break;
        for (int j = 0; j < getEdgeCount(vCurrent); j++) {
            int vNext = edgeList->search(vCurrent)->keyAt(j);
            if (nodeList->search(vNext)->visited)
                continue;
            int newDistance = getEdge(vCurrent, vNext);
            if (newDistance < nodeList->search(vNext)->accDistance) {
                nodeList->search(vNext)->accDistance = newDistance;
                nodeList->search(vNext)->prev = vCurrent;
                pq.changeKeyWithData(vNext, newDistance);
                pq.sortKey();
            }
        }
    }

    for (int i = 0; i < getTotalVertex(); i++) {
        int vCurrent = nodeList->at(i)->number;
        int vPrev = nodeList->at(i)->prev;
        if (vPrev != -1)
            mst->addEdge(vPrev, vCurrent, getEdge(vPrev, vCurrent));
    }
    return mst;

}


#endif // GRAPHLIST_H_INCLUDED