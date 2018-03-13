#include "Graph.h"


Graph::Graph(int v) : v(v)
{
    if (this->v < 1) this->v = 10;
    createEmptyGraph();
}


Graph::~Graph()
{
    for (int i = 0; i < v; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    verticeList *tempList = beginList;
    while(tempList != NULL && tempList->next != NULL) {
        vertice *tempVertice = tempList->beginVertice;
        while(tempVertice != NULL && tempVertice->next != NULL) {
            tempVertice = tempVertice->next;
            delete tempVertice->last;
        }
        delete tempVertice;
        tempList = tempList->next;
        delete tempList->last;
    }
    delete tempList;
}

void Graph::createEmptyGraph() {
    matrix = new int*[v];
    for (int i = 0; i < v; i++) {
        matrix[i] = new int[v];
        for (int j = 0; j < v; j++) {
            matrix[i][j] = 0;
        }
    }

    struct verticeList *currentList;
    struct verticeList *lastList = NULL;
    for (int i = 0; i < v; i++) {
        currentList = new verticeList;
        currentList->number = i;
        currentList->beginVertice = NULL;
        currentList->endVertice = NULL;
        currentList->last = lastList;
        if (i == 0) {
            beginList = currentList;
        }
        else {
            lastList->next = currentList;
        }
        if (i == v - 1) {
            endList = currentList;
            currentList->next = NULL;
        }
        lastList = currentList;
    }

}

void Graph::generateRandomEdges(int maxRange, int rate) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (rand() % 100 >= rate) {
                addEdge(i, j, rand() % maxRange + 1);
            }
        }
    }
}

void Graph::addVertice() {
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

    struct verticeList *currentList = new verticeList;
    currentList->number = v - 1;
    currentList->beginVertice = NULL;
    currentList->endVertice = NULL;
    currentList->next = NULL;
    currentList->last = endList;
    endList->next = currentList;
    endList = currentList;
}

void Graph::deleteVertice(int v) {
    if (v >= this->v || v < 0) return;
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

    struct verticeList *tempList = beginList;
    for (int i = 0; i < v; i++) {
        tempList = tempList->next;
    }
    if (tempList->last != NULL) {
        tempList->last->next = tempList->next;
    }
    if (tempList->next != NULL) {
        tempList->next->last = tempList->last;
    }
    if (tempList->beginVertice != NULL) {
        struct vertice *tempVertice = tempList->beginVertice;
        while (tempVertice != NULL) {
            tempVertice = tempVertice->next;
            delete tempVertice->last;
        }
    }

}

void Graph::addEdge(int v1, int v2, int range) {
    if (v1 >= v || v2 >= v) return;
    matrix[v1][v2] = range;
}

void Graph::deleteEdge(int v1, int v2) {
    if (v1 >= v || v2 >= v) return;
    matrix[v1][v2] = 0;
}

//int Graph::getEdgeList(int v1, int v2);
//int* Graph::getEdgeList(int v);
//int* Graph::getEdgeRangeList(int v);
//int Graph::getEdgeCount(int v);

int Graph::getEdgeMatrix(int v1, int v2) {
    if (v1 < v && v2 < v)
        return matrix[v1][v2];
    else
        return -1;
}

int Graph::getTotalVertice() {
    return v;
}

int Graph::getTotalEdge() {
    return e;
}



