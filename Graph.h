#include <time.h>
#include <stdlib.h>

class Graph
{
public:
    Graph(int v = 10);
    ~Graph();
    void createEmptyGraph();
    void generateRandomEdges(int maxRange, int rate);
    void addVertice();
    void deleteVertice(int v);
    void addEdge(int v1, int v2, int range = 1);
    void deleteEdge(int v1, int v2);
    int getEdgeMatrix(int v1, int v2);
    int getEdgeList(int v1, int v2);
    int* getEdgeList(int v);
    int* getEdgeRangeList(int v);
    int getEdgeCount(int v);
    int getTotalVertice();
    int getTotalEdge();

private:
    int v; //number of vertices
    int e; //number of edges
    int **matrix; //adjacency matrix
    struct verticeList *beginList, *endList;
};

struct verticeList {
    int number;
    struct verticeList *next, *last;
    struct vertice *beginVertice, *endVertice;
};

struct vertice {
    int number;
    int range;
    struct vertice *next, *last;
};

