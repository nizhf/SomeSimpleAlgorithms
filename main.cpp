#include <iostream>
#include <ctime>
#include <Windows.h>
#include <cstdlib>

#include "Sort/SortAlgorithm.h"
#include "Graph/GraphList.h"
#include "Graph/GraphMatrix.h"
#include "List/MyList.h"
#include "Tree/MinHeap.h"
#include "Tree/AVLTree.h"

using namespace std;

void showSort();
void showList();
void showGraphMatrix();
void printGraphMatrix(GraphMatrix *g);
void showGraphList();
void printGraphList(GraphList *g);
void showMinHeap();
void showAVLTree();

int main()
{
    bool exit = false;
    do {
        cout << "\nMain Menu\n1. Sort algorithm\n2. List\n3. Graph Matrix\n4. Graph List\n5. Min Heap\n6. AVL Tree\nOther. Exit\n";
        int option;
        exit = false;
        cin >> option;
        switch (option) {
        case 1:
            showSort();
            break;
        case 2:
            showList();
            break;
        case 3:
            showGraphMatrix();
            break;
        case 4:
            showGraphList();
            break;
        case 5:
            showMinHeap();
            break;
        case 6:
            showAVLTree();
            break;
        default:
            exit = true;
            break;
        }
    }
    while (!exit);

    return 0;
}

void showSort() {
    srand((unsigned)time(NULL));
    bool exit = false;
    int operation;
    int length;
    do {
        exit = false;
        cout << "\nSort menu:\n 1. Sort an array\n 2. Sort benchmark\n Other. Quit\n";
        cin >> operation;
        if (operation == 1) {
            cout << "Enter the count of numbers: ";
            cin >> length;
            int *arr = new int[length];
            for (int i = 0; i < length; i++) {
                cout << i + 1 << ". number: ";
                cin >> arr[i];
            }
            cout << "Original array: ";
            for (int i = 0; i < length; i++) {
                cout << arr[i] << " ";
            }

            int *arr1 = new int[length];
            for (int i = 0; i < length; i++) {
                arr1[i] = arr[i];
            }
            cout << "\n Insertion Sort: \n";
            SortAlgorithm<int>::insertionSort(arr1, length);
            for (int i = 0; i < length; i++) {
                cout << arr1[i] << " ";
            }

            int *arr2 = new int[length];
            for (int i = 0; i < length; i++) {
                arr2[i] = arr[i];
            }
            cout << "\n Bubble Sort: \n";
            SortAlgorithm<int>::bubbleSort(arr2, length);
            for (int i = 0; i < length; i++) {
                cout << arr2[i] << " ";
            }

            int *arr3 = new int[length];
            for (int i = 0; i < length; i++) {
                arr3[i] = arr[i];
            }
            cout << "\n Selection Sort: \n";
            SortAlgorithm<int>::selectionSort(arr3, length);
            for (int i = 0; i < length; i++) {
                cout << arr3[i] << " ";
            }

            int *arr4 = new int[length];
            for (int i = 0; i < length; i++) {
                arr4[i] = arr[i];
            }
            cout << "\n Quick Sort: \n";
            SortAlgorithm<int>::quickSort(arr4, 0, length - 1);
            for (int i = 0; i < length; i++) {
                cout << arr4[i] << " ";
            }

            int *arr5 = new int[length];
            for (int i = 0; i < length; i++) {
                arr5[i] = arr[i];
            }
            cout << "\n Quick Sort2: \n";
            SortAlgorithm<int>::quickSort2(arr5, 0, length - 1);
            for (int i = 0; i < length; i++) {
                cout << arr5[i] << " ";
            }

            int *arr6 = new int[length];
            for (int i = 0; i < length; i++) {
                arr6[i] = arr[i];
            }
            cout << "\n Merge Sort: \n";
            SortAlgorithm<int>::mergeSort(arr6, length);
            for (int i = 0; i < length; i++) {
                cout << arr6[i] << " ";
            }

            int *arr7 = new int[length];
            for (int i = 0; i < length; i++) {
                arr7[i] = arr[i];
            }
            cout << "\n Merge Sort2: \n";
            SortAlgorithm<int>::mergeSort2(arr7, length);
            for (int i = 0; i < length; i++) {
                cout << arr7[i] << " ";
            }

            int *arr8 = new int[length];
            for (int i = 0; i < length; i++) {
                arr8[i] = arr[i];
            }
            cout << endl << " Heap Sort:" << endl;
            MinHeap<int, int>::heapSort(arr8, length);
            for (int i = 0; i < length; i++) {
                cout << arr8[i] << " ";
            }

            delete[] arr;
            delete[] arr1;
            delete[] arr2;
            delete[] arr3;
            delete[] arr4;
            delete[] arr5;
            delete[] arr6;
            delete[] arr7;
            delete[] arr8;
        }
        else if (operation == 2) {
            cout << "Enter the count of random numbers: ";
            cin >> length;
            int *arr = new int[length];
            for (int i = 0; i < length; i++) {
                arr[i] = rand() % 100000;
                //std::cout << arr[i] << " ";
            }

            DWORD timeStart, timeStop;

            int *arr1 = new int[length];
            for (int i = 0; i < length; i++) {
                arr1[i] = arr[i];
            }
            cout << "\n Insertion Sort: \n";
            timeStart = GetTickCount();
            SortAlgorithm<int>::insertionSort(arr1, length);
            timeStop = GetTickCount();
            cout << (timeStop - timeStart) << "ms\n";

            int *arr2 = new int[length];
            for (int i = 0; i < length; i++) {
                arr2[i] = arr[i];
            }
            cout << "\n Bubble Sort: \n";
            timeStart = GetTickCount();
            SortAlgorithm<int>::bubbleSort(arr2, length);
            timeStop = GetTickCount();
            cout << (timeStop - timeStart) << "ms\n";

            int *arr3 = new int[length];
            for (int i = 0; i < length; i++) {
                arr3[i] = arr[i];
            }
            cout << "\n Selection Sort: \n";
            timeStart = GetTickCount();
            SortAlgorithm<int>::selectionSort(arr3, length);
            timeStop = GetTickCount();
            cout << (timeStop - timeStart) << "ms\n";

            int *arr4 = new int[length];
            for (int i = 0; i < length; i++) {
                arr4[i] = arr[i];
            }
            cout << "\n Quick Sort: \n";
            timeStart = GetTickCount();
            SortAlgorithm<int>::quickSort(arr4, 0, length - 1);
            timeStop = GetTickCount();
            cout << (timeStop - timeStart) << "ms\n";

            int *arr5 = new int[length];
            for (int i = 0; i < length; i++) {
                arr5[i] = arr[i];
            }
            cout << "\n Quick Sort2: \n";
            timeStart = GetTickCount();
            SortAlgorithm<int>::quickSort2(arr5, 0, length - 1);
            timeStop = GetTickCount();
            cout << (timeStop - timeStart) << "ms\n";

            int *arr6 = new int[length];
            for (int i = 0; i < length; i++) {
                arr6[i] = arr[i];
            }
            cout << "\n Merge Sort: \n";
            timeStart = GetTickCount();
            SortAlgorithm<int>::mergeSort(arr6, length);
            timeStop = GetTickCount();
            cout << (timeStop - timeStart) << "ms\n";

            int *arr7 = new int[length];
            for (int i = 0; i < length; i++) {
                arr7[i] = arr[i];
            }
            cout << "\n Merge Sort2: \n";
            timeStart = GetTickCount();
            SortAlgorithm<int>::mergeSort2(arr7, length);
            timeStop = GetTickCount();
            cout << (timeStop - timeStart) << "ms\n";

            delete[] arr;
            delete[] arr1;
            delete[] arr2;
            delete[] arr3;
            delete[] arr4;
            delete[] arr5;
            delete[] arr6;
            delete[] arr7;
        }
        else exit = true;
    } while(!exit);
}



void showList() {
    cout << "Count: ";
    int count;
    cin >> count;

    MyList<int> *myList = new MyList<int>;
    for (int i = 0; i < count; i++) {
        int number;
        cout << i << ". number: ";
        cin >> number;
        myList->pushBack(number);
    }
    cout << "All numbers: \n";
    for (int i = 0; i < myList->size(); i++) {
        cout << myList->at(i) << " ";
    }
    cout << "\n" << myList->back() << " " << myList->front();
    cout << "\n" << myList->popBack();
    cout << " " << myList->popFront();

    cout << "\nAll numbers after pop: \n";
    for (int i = 0; i < myList->size(); i++) {
        cout << myList->at(i) << " ";
    }

    myList->insert(0, 111);
    cout << "\nAll numbers: \n";
    for (int i = 0; i < myList->size(); i++) {
        cout << myList->at(i) << " ";
    }
    myList->insert(3, 999);
    cout << "\nAll numbers: \n";
    for (int i = 0; i < myList->size(); i++) {
        cout << myList->at(i) << " ";
    }

    cout << "\n" << myList->remove(4);
    cout << " " << myList->remove(0);
    cout << " " << myList->pushFront(0);
    cout << "\nAll numbers: \n";
    for (int i = 0; i < myList->size(); i++) {
        cout << myList->at(i) << " ";
    }

    myList->swap(2, 5);
    cout << "\nAll numbers after swap 1: \n";
    for (int i = 0; i < myList->size(); i++) {
        cout << myList->at(i) << " ";
    }

    myList->swap(2, 3);
    cout << "\nAll numbers after swap 2: \n";
    for (int i = 0; i < myList->size(); i++) {
        cout << myList->at(i) << " ";
    }

    myList->swap(6, 8);
    cout << "\nAll numbers after swap 3: \n";
    for (int i = 0; i < myList->size(); i++) {
        cout << myList->at(i) << " ";
    }

    myList->swap(0, 3);
    cout << "\nAll numbers after swap 4: \n";
    for (int i = 0; i < myList->size(); i++) {
        cout << myList->at(i) << " ";
    }

    myList->swap(0, 1);
    cout << "\nAll numbers after swap 5: \n";
    for (int i = 0; i < myList->size(); i++) {
        cout << myList->at(i) << " ";
    }

    myList->swap(7, 8);
    cout << "\nAll numbers after swap 6: \n";
    for (int i = 0; i < myList->size(); i++) {
        cout << myList->at(i) << " ";
    }

    cout << "\nsearch: " << myList->search(0);
    auto result = myList->searchAll(0);
    cout << "\nAll numbers found: \n";
    for (int i = 0; i < myList->searchCount(0); i++) {
        cout << result[i] << " ";
    }

    myList->sort();
    cout << "\nAll numbers after sort: \n";
    for (int i = 0; i < myList->size(); i++) {
        cout << myList->at(i) << " ";
    }

    cout << "\nBenchmark: ";
    int benchmark;
    cin >> benchmark;
    srand((unsigned)time(NULL));
    MyList<int> *benchmarkList = new MyList<int>;
    for (int i = 0; i < benchmark; i++) {
        benchmarkList->pushBack(rand() % benchmark);
    }
    DWORD timeStart, timeStop;
    timeStart = GetTickCount();
    benchmarkList->sort();
    timeStop = GetTickCount();
    cout << (timeStop - timeStart) << "ms\n";

    delete myList;
    delete benchmarkList;
}



void showGraphMatrix() {
    bool graphCreated = false;
    bool exit = false;
    GraphMatrix *g = NULL;
    int v1, v2, range;
    do {
        exit = false;
        int operation;
        cout << "\nGraph Matrix menu \n 1. Create Graph \n 2. Add Vertex \n 3. Delete Vertex \n 4. Add Edge \n 5. Delete Edge \n Other. Quit\n";
        cin >> operation;
        if (!graphCreated && operation > 1 && operation < 6) {
            cout << "You must first create a graph! \n";
            operation = 1;
        }
        switch (operation) {
        case 1:
            cout << "Graph size: ";
            int gsize;
            cin >> gsize;
            delete g;
            g = new GraphMatrix(gsize);

            char random;
            cout << "Random generate edges? (y/n): ";
            cin >> random;
            if (random == 'y') {
                int maxRange;
                int rate;
                cout << "Max range: ";
                cin >> maxRange;
                cout << "Rate: ";
                cin >> rate;
                g->generateRandomEdges(maxRange, rate);
            }
            printGraphMatrix(g);
            graphCreated = true;
            break;

        case 2:
            cout << "Add Vertex:\n";
            g->addVertex();
            printGraphMatrix(g);
            break;

        case 3:
            cout << "Delete Vertex: ";
            int deleteV;
            cin >> deleteV;
            g->deleteVertex(deleteV);
            printGraphMatrix(g);
            break;
        case 4:
            cout << "Add Edge: \nFirst Vertex: ";
            cin >> v1;
            cout << "Second Vertex: ";
            cin >> v2;
            cout << "Range: ";
            cin >> range;
            g->addEdge(v1, v2, range);
            printGraphMatrix(g);
            break;
        case 5:
            cout << "Delete Edge: \nFirst Vertex: ";
            cin >> v1;
            cout << "Second Vertex: ";
            cin >> v2;
            g->deleteEdge(v1, v2);
            printGraphMatrix(g);
            break;
        default:
            exit = true;
            break;
        }
    }
    while (!exit);
    delete g;
}

void printGraphMatrix(GraphMatrix *g) {
    cout << "\nMatrix: \n";
    for (int i = 0; i < g->getTotalVertex(); i++) {
        for (int j = 0; j < g->getTotalVertex(); j++) {
            cout << " " << g->getEdge(i, j) << " ";
        }
        cout << "\n";
    }
}



void showGraphList() {
    bool graphCreated = false;
    bool exit = false;
    GraphList *g = NULL;
    MyList<int> *path = NULL;
    GraphList *mst = NULL;
    do {
        exit = false;
        int operation;
        int v1, v2, range;
        cout << endl << "Graph List menu \n 1. Create Graph \n 2. Add Vertex \n 3. Delete Vertex \n 4. Add Edge \n 5. Delete Edge \n 6. Graph Properties \n 7. Find Shortest Path" << endl;
        cout << " 8. Find Minimum Spanning Tree \n Other. Quit" << endl;
        cin >> operation;
        if (!graphCreated && operation > 1 && operation < 9) {
            cout << "You must first create a graph!" << endl;
            operation = 1;
        }
        switch (operation) {
        case 1:
            cout << "Graph size: ";
            int gsize;
            cin >> gsize;
            cout << "Directed? (y/n) ";
            char directed;
            cin >> directed;
            delete g;
            g = new GraphList(gsize, (directed == 'y' ? true : false));

            char random;
            cout << "Random generate edges? (y/n): ";
            cin >> random;
            if (random == 'y') {
                int maxRange;
                int rate;
                cout << "Max range: ";
                cin >> maxRange;
                cout << "Rate: ";
                cin >> rate;
                g->generateRandomEdges(maxRange, rate);
            }
            try {printGraphList(g);}
            catch (const char *err) {cout << err << endl;}
            graphCreated = true;
            break;
        case 2:
            cout << "Add Vertex:" << endl;
            g->addVertex();
            printGraphList(g);
            break;
        case 3:
            cout << "Delete Vertex: ";
            int deleteV;
            cin >> deleteV;
            if (!g->deleteVertex(deleteV))
                cout << "invalid position!" << endl;
            printGraphList(g);
            break;
        case 4:
            cout << "Add Edge: \nFirst Vertex: ";
            cin >> v1;
            cout << "Second Vertex: ";
            cin >> v2;
            cout << "Range: ";
            cin >> range;
            if (!g->addEdge(v1, v2, range))
                cout << "invalid position!" << endl;
            printGraphList(g);
            break;
        case 5:
            cout << "Delete Edge: \nFirst Vertex: ";
            cin >> v1;
            cout << "Second Vertex: ";
            cin >> v2;
            if (!g->deleteEdge(v1, v2))
                cout << "invalid position!" << endl;
            printGraphList(g);
            break;
        case 6:
            cout << "This Graph is " << (g->isConnected() ? "connected" : "not connected") << ", ";
            cout << (g->isCycle() ? "cyclic" : "acyclic") << " and ";
            cout << (g->isTree() ? "a tree." : "not a tree.") << endl;
            break;
        case 7:
            cout << "Find Shortest Path" << endl << "First Vertex: ";
            cin >> v1;
            cout << "Second Vertex: ";
            cin >> v2;
            path = g->dijkstra(v1, v2);
            if (NULL == path)
                cout << "Invalid position!" << endl;
            else if (path->size() == 0)
                cout << "No path found between " << v1 << " and " << v2 <<endl;
            else {
                cout << path->keyAt(0);
                for (int i = 1; i < path->size(); i++)
                    cout << "-->" << path->keyAt(i);
                cout << ", Total Distance: " << path->back() << endl;
            }
            break;
        case 8:
            cout << "Minimum Spanning Tree";
            mst = g->prim();
            printGraphList(mst);
            break;
        default:
            exit = true;
            break;
        }
    }
    while (!exit);
    delete g;
    delete mst;
    delete path;
}

void printGraphList(GraphList *g) {
    cout << "\nList: \n";
    for (int i = 0; i < g->getTotalVertex(); i++) {
        cout << g->getVertexNumberAt(i) << ": ";
        for (int j = 0; j < g->getTotalVertex(); j++) {
            int range = g->getEdge(g->getVertexNumberAt(i), g->getVertexNumberAt(j));
            if (range > 0)
                cout << " " << g->getVertexNumberAt(j) << "-" << range << " ";
        }
        cout << endl;
    }
}



void showMinHeap() {
    bool heapCreated = false;
    bool exit = false;
    MinHeap<int, int> *mh = NULL;
    int *arr = NULL;
    do {
        exit = false;
        int operation, key, data;
        cout << endl << "Min Heap Menu:" << endl << " 1. Create new Min Heap" << endl << " 2. Show" << endl << " 3. Insert" << endl << " 4. Extract Min" << endl << " 5. Heap Sort" << endl;
        cout << "Other. Quit" << endl;
        cin >> operation;
        if (!heapCreated && operation > 1  && operation < 5) {
            cout << "You must first create a new Min Heap!" << endl;
            operation = 1;
        }
        switch (operation) {
        case 1:
            cout << "Count: ";
            int count;
            cin >> count;
            cout << "Random? (y/n) ";
            char random;
            cin >> random;
            delete mh;
            mh = new MinHeap<int, int>;
            if (random == 'y') {
                for (int i = 0; i < count; i++) {
                    int num = rand() % (count * 3);
                    mh->insert(num, num);
                }
            }
            else {
                for (int i = 0; i < count; i++) {
                    cout << i << ". key: ";
                    cin >> key;
                    cout << i << ". data: ";
                    cin >> data;
                    mh->insert(data, key);
                }
            }
            heapCreated = true;
            break;
        case 2:
            cout << "Min Heap size: " << mh->size() << ", depth: " << mh->depth() << endl;
            mh->traverseLevel(mh->root(), [&](struct MinHeap<int, int>::Node *node){cout << node->key << "-" << node->data << " ";});
            cout << endl;
            break;
        case 3:
            cout << "Insert: " << endl;
            cout << "Key: ";
            cin >> key;
            cout << "Data: ";
            cin >> data;
            mh->insert(data, key);
            break;
        case 4:
            cout << "Extract Min: " << mh->extractMin() << endl;
            break;
        case 5:
            cout << "Heap Sort: " << endl;
            cout << "Count: ";
            cin >> count;
            cout << "Random?(y/n) ";
            cin >> random;
            arr = new int[count];
            if (random == 'y') {
                for (int i = 0; i < count; i++) {
                    arr[i] = rand() % (count * 3);
                }
            }
            else {
                for (int i = 0; i < count; i++) {
                    cout << i + 1 << ". number: ";
                    cin >> arr[i];
                }
            }
            cout << "Original array: ";
            for (int i = 0; i < count; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
            arr = MinHeap<int, int>::heapSort(arr, count);
            cout << endl << "Array after heap sort:" << endl;
            for (int i = 0; i < count; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
            break;
        default:
            exit = true;
            break;
        }
    }
    while (!exit);
    delete mh;
    delete arr;
}



void showAVLTree() {
    bool treeCreated = false;
    bool exit = false;
    AVLTree<string, int> avl;

    do {
        exit = false;
        int operation, key;
        string data;
        cout << endl << "AVL Tree Menu:" << endl << " 1. Create new AVL Tree" << endl << " 2. Show" << endl << " 3. Insert" << endl << " 4. Remove" << endl << " 5. Search" << endl;
        cout << "Other. Quit" << endl;
        cin >> operation;
        if (!treeCreated && operation > 1  && operation < 6) {
            cout << "You must first create a new AVL Tree!" << endl;
            operation = 1;
        }
        switch (operation) {
        case 1:
            cout << "Count: ";
            int count;
            cin >> count;
            avl.initialize();
            for (int i = 0; i < count; i++) {
                cout << i << ". key: ";
                cin >> key;
                cout << i << ". data: ";
                cin >> data;
                avl.insert(data, key);
            }
            treeCreated = true;
            break;
        case 2:
            cout << "AVL Tree size: " << avl.size() << ", depth: " << avl.depth() << endl;
            avl.traverseLevel(avl.root(), [&](struct BinaryTree<string, int>::Node *node){cout << node->key << "-" << node->data << " ";});
            cout << endl;
            break;
        case 3:
            cout << "Insert: " << endl;
            cout << "Key: ";
            cin >> key;
            cout << "Data: ";
            cin >> data;
            avl.insert(data, key);
            break;
        case 4:
            cout << "Remove: " << endl;
            cout << "Key: ";
            cin >> key;
            avl.removeKey(key);
            break;
        case 5:
            cout << "Search: " << endl;
            cout << "Key: ";
            cin >> key;
            try {
                cout << avl.search(key) << endl;
            }
            catch (const char *err) {
                cout << err << endl;
            }
            break;
        default:
            exit = true;
            break;
        }
    }
    while (!exit);
}





