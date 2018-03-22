#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <time.h>
#include <stdlib.h>

class Graph
{
public:
    virtual ~Graph();

    virtual void createEmptyGraph() = 0;
    virtual bool generateRandomEdges(int maxRange, int rate) = 0;

    virtual bool addVertex() = 0;
    virtual bool deleteVertex(int v) = 0;

    virtual bool addEdge(int v1, int v2, int range = 1) = 0;
    virtual bool deleteEdge(int v1, int v2) = 0;

    virtual int getEdge(int v1, int v2) const = 0;
    virtual int getEdgeCount(int v) const = 0;

    virtual int getTotalVertex() const = 0;
    virtual int getTotalEdge() const = 0;

private:
};

inline Graph::~Graph() {

}

#endif // GRAPH_H_INCLUDED

