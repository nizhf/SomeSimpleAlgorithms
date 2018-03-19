#ifndef GRAPHMATRIX_H_INCLUDED
#define GRAPHMATRIX_H_INCLUDED

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

    int getEdge(int v1, int v2);
    int getEdgeCount(int v);

    int getTotalVertex();
    int getTotalEdge();

private:
    int v; //number of vertices
    int e; //number of edges
    int **matrix; //adjacency matrix

};

inline GraphMatrix::GraphMatrix(int v) : v(v) {
    if (this->v < 1)
        this->v = 10;
    e = 0;
    createEmptyGraph();
}

inline GraphMatrix::~GraphMatrix() {
    for (int i = 0; i < v; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

inline void GraphMatrix::createEmptyGraph() {
    matrix = new int*[v];
    for (int i = 0; i < v; i++) {
        matrix[i] = new int[v];
        for (int j = 0; j < v; j++) {
            matrix[i][j] = 0;
        }
    }
}

inline bool GraphMatrix::generateRandomEdges(int maxRange, int rate) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (rand() % 100 >= rate) {
                if (!addEdge(i, j, rand() % maxRange + 1))
                    return false;
            }
        }
    }
    return true;
}

inline bool GraphMatrix::addVertex() {
    v++;
    int **newMatrix = new int*[v];
    for (int i = 0; i < v; i++) {
        newMatrix[i] = new int[v];
        for (int j = 0; j < v; j++) {
            if (i < v - 1 && j < v - 1)
                newMatrix[i][j] = matrix[i][j];
            else newMatrix[i][j] = 0;
        }
    }
    for (int i = 0; i < v - 1; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = newMatrix;
    return true;
}

inline bool GraphMatrix::deleteVertex(int v) {
    if (v >= this->v || v < 0) return false;
    this->v--;
    int **newMatrix = new int*[this->v];
    for (int i = 0, ii = 0; i < this->v + 1; i++) {
        if (i != v) {
            newMatrix[ii] = new int[this->v];
            for (int j = 0, jj = 0; j < this->v + 1; j++) {
                if (j != v) {
                    newMatrix[ii][jj] = matrix[i][j];
                    jj++;
                }
            }
            ii++;
        }
    }
    for (int i = 0; i < this->v + 1; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = newMatrix;
    return true;
}

inline bool GraphMatrix::addEdge(int v1, int v2, int range) {
    if (v1 >= v || v2 >= v || v1 < 0 || v2 < 0) return false;
    matrix[v1][v2] = range;
    e++;
    return true;
}

inline bool GraphMatrix::deleteEdge(int v1, int v2) {
    if (v1 >= v || v2 >= v || v1 < 0 || v2 < 0) return false;
    matrix[v1][v2] = 0;
    e--;
    return true;
}

inline int GraphMatrix::getEdge(int v1, int v2) {
    if (v1 >= v || v2 >= v || v1 < 0 || v2 < 0) return -1;
    return matrix[v1][v2];
}

inline int GraphMatrix::getEdgeCount(int v) {
    if (v >= this->v || v < 0) return -1;
    int count = 0;
    for (int i = 0; i < this->v; i++) {
        if (matrix[v][i] > 0)
            count++;
    }
    return count;
}

inline int GraphMatrix::getTotalVertex() {
    return v;
}

inline int GraphMatrix::getTotalEdge() {
    return e;
}

#endif // GRAPHMATRIX_H_INCLUDED
