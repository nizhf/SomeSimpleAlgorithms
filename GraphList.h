#ifndef GRAPHLIST_H_INCLUDED
#define GRAPHLIST_H_INCLUDED

#include <stdlib.h>
#include <time.h>
#include "MyList.h"
#include "Graph.h"


class GraphList : public Graph
{
public:
    GraphList(int v = 10);
    ~GraphList();

    void createEmptyGraph();
    bool generateRandomEdges(int maxRange, int rate);

    bool addVertice();
    bool deleteVertice(int v);

    bool addEdge(int v1, int v2, int range = 1);
    bool deleteEdge(int v1, int v2);

    int getEdge(int v1, int v2);
    int getEdgeCount(int v);

    int getTotalVertice();
    int getTotalEdge();

    int getVerticeNumberAt(int index);

private:
    struct Node {
        int number;
        bool visited;
        int accRange;
    };
    int vNumber;
    MyList<MyList<int> *> *edgeList;
    MyList<Node *> *nodeList;


};

inline GraphList::GraphList(int v) {
    int vMax = v >= 1? v : 10;
    vNumber = 0;
    nodeList = new MyList<Node *>;
    edgeList = new MyList<MyList<int> *>;
    for (int i = 0; i < vMax; i++)
        addVertice();
}

inline GraphList::~GraphList() {
    delete nodeList;
    delete edgeList;
}

inline void GraphList::createEmptyGraph() {

}

inline bool GraphList::generateRandomEdges(int maxRange, int rate) {
    srand((unsigned)time(0));
    for (int i = 0; i < getTotalVertice(); i++) {
        for (int j = 0; j < getTotalVertice(); j++) {
            if (rand() % 100 >= rate) {
                if (!addEdge(i, j, rand() % maxRange + 1))
                    return false;
            }
        }
    }
    return true;
}

inline bool GraphList::addVertice() {
    Node *newNode = new Node{vNumber, false, 0};
    nodeList->pushBack(newNode, vNumber);
    MyList<int> *newList = new MyList<int>;
    edgeList->pushBack(newList, vNumber);
    vNumber++;
    return true;
}

inline bool GraphList::deleteVertice(int v) {
    bool found = false;
    for (int i = 0; i < getTotalVertice(); i++) {
        if (nodeList->keyAt(i) == v) {
            found = true;
            nodeList->removeKey(v);
            break;
        }
    }
    if (!found)
        return false;

    edgeList->removeKey(v);
    for (int i = 0; i < getTotalVertice(); i++)
        edgeList->at(i)->removeKey(v);
    return true;
}

inline bool GraphList::addEdge(int v1, int v2, int range) {
    if (range < 1)
        return false;
    bool found1 = false;
    bool found2 = false;
    for (int i = 0; i < getTotalVertice(); i++) {
        if (nodeList->keyAt(i) == v1)
            found1 = true;
        if (nodeList->keyAt(i) == v2)
            found2 = true;
        if (found1 && found2)
            break;
    }
    if (!found1 || !found2)
        return false;

    return edgeList->search(v1)->pushBack(range, v2);
}

inline bool GraphList::deleteEdge(int v1, int v2) {
    bool found1 = false;
    for (int i = 0; i < getTotalVertice(); i++) {
        if (nodeList->keyAt(i) == v1) {
            found1 = true;
            break;
        }
    }
    if (!found1)
        return false;

    return edgeList->search(v1)->removeKey(v2);
}

inline int GraphList::getEdge(int v1, int v2) {
    bool found1 = false;
    bool found2 = false;
    for (int i = 0; i < getTotalVertice(); i++) {
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

inline int GraphList::getEdgeCount(int v) {
    bool found = false;
    for (int i = 0; i < getTotalVertice(); i++) {
        if (nodeList->keyAt(i) == v) {
            found = true;
            nodeList->removeKey(v);
            break;
        }
    }
    if (!found)
        return -1;

    return edgeList->search(v)->size();
}

inline int GraphList::getTotalVertice() {
    return nodeList->size();
}

inline int GraphList::getTotalEdge() {
    int e = 0;
    for (int i = 0; i < edgeList->size(); i++) {
        e += edgeList->at(i)->size();
    }
    return e;
}

inline int GraphList::getVerticeNumberAt(int index) {
    if (index < 0 || index >= getTotalVertice())
        return -1;
    return nodeList->keyAt(index);
}



#endif // GRAPHLIST_H_INCLUDED
