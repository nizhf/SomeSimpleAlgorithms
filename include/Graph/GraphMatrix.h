#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

#include "Graph.h"

class GraphMatrix : public Graph
{
public:
    GraphMatrix(int v = 10);
    ~GraphMatrix();

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

private:
    int v; //number of vertices
    int e; //number of edges
    int **matrix; //adjacency matrix

};

#endif // GRAPHMATRIX_H
