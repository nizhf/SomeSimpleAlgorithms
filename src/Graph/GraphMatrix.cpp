#include "Graph/GraphMatrix.h"

GraphMatrix::GraphMatrix(int v) : v(v) {
    if (this->v < 1)
        this->v = 10;
    e = 0;
    createEmptyGraph();
}

GraphMatrix::~GraphMatrix() {
    for (int i = 0; i < v; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void GraphMatrix::createEmptyGraph() {
    matrix = new int*[v];
    for (int i = 0; i < v; i++) {
        matrix[i] = new int[v];
        for (int j = 0; j < v; j++) {
            matrix[i][j] = 0;
        }
    }
}

bool GraphMatrix::generateRandomEdges(int maxRange, int rate) {
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

bool GraphMatrix::addVertex() {
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

bool GraphMatrix::deleteVertex(int v) {
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

bool GraphMatrix::addEdge(int v1, int v2, int range) {
    if (v1 >= v || v2 >= v || v1 < 0 || v2 < 0) return false;
    matrix[v1][v2] = range;
    e++;
    return true;
}

bool GraphMatrix::deleteEdge(int v1, int v2) {
    if (v1 >= v || v2 >= v || v1 < 0 || v2 < 0) return false;
    matrix[v1][v2] = 0;
    e--;
    return true;
}

int GraphMatrix::getEdge(int v1, int v2) const {
    if (v1 >= v || v2 >= v || v1 < 0 || v2 < 0) return -1;
    return matrix[v1][v2];
}

int GraphMatrix::getEdgeCount(int v) const {
    if (v >= this->v || v < 0) return -1;
    int count = 0;
    for (int i = 0; i < this->v; i++) {
        if (matrix[v][i] > 0)
            count++;
    }
    return count;
}

int GraphMatrix::getTotalVertex() const {
    return v;
}

int GraphMatrix::getTotalEdge() const {
    return e;
}
