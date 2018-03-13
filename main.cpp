#include <iostream>
#include "SortAlgorithm.h"
#include "Graph.h"
#include <time.h>
#include <Windows.h>
#include <stdlib.h>

using namespace std;

void showSort();
void showGraph();

int main()
{
    bool exit = false;
    do {
        cout << "\nMain Menu\n1. Sort algorithm\n2. Graph\n3. Search algorithm\nOther. Exit\n";
        int option;
        exit = false;
        cin >> option;
        switch (option) {
        case 1:
            showSort();
            break;
        case 2:
            showGraph();
            break;
        case 3:
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

            delete[] arr;
            delete[] arr1;
            delete[] arr2;
            delete[] arr3;
            delete[] arr4;
            delete[] arr5;
            delete[] arr6;
            delete[] arr7;
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


void showGraph() {
    bool graphCreated = false;
    bool exit = false;
    Graph *g = NULL;
    int v1, v2, range;
    int deleteV;
    do {
        exit = false;
        int operation;
        cout << "\nGraph menu \n 1. Create Graph \n 2. Add Vertice \n 3. Delete Vertice \n 4. Add Edge \n 5. Delete Edge \n Other. Quit\n";
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
            g = new Graph(gsize);

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
            for (int i = 0; i < g->getTotalVertice(); i++) {
                for (int j = 0; j < g->getTotalVertice(); j++) {
                    cout << " " << g->getEdgeMatrix(i, j) << " ";
                }
                cout << "\n";
            }

            graphCreated = true;
            break;
        case 2:
            cout << "Add Vertice:\n";
            g->addVertice();
            for (int i = 0; i < g->getTotalVertice(); i++) {
                for (int j = 0; j < g->getTotalVertice(); j++) {
                    cout << " " << g->getEdgeMatrix(i, j) << " ";
                }
                cout << "\n";
            }
            break;
        case 3:
            cout << "Delete Vertice: ";
            cin >> deleteV;
            g->deleteVertice(deleteV);
            for (int i = 0; i < g->getTotalVertice(); i++) {
                for (int j = 0; j < g->getTotalVertice(); j++) {
                    cout << " " << g->getEdgeMatrix(i, j) << " ";
                }
                cout << "\n";
            }
            break;
        case 4:
            cout << "Add Edge: \nFirst Vertice: ";
            cin >> v1;
            cout << "Second Vertice: ";
            cin >> v2;
            cout << "Range: ";
            cin >> range;
            g->addEdge(v1, v2, range);
            for (int i = 0; i < g->getTotalVertice(); i++) {
                for (int j = 0; j < g->getTotalVertice(); j++) {
                    cout << " " << g->getEdgeMatrix(i, j) << " ";
                }
                cout << "\n";
            }
            break;
        case 5:
            cout << "Delete Edge: \nFirst Vertice: ";
            cin >> v1;
            cout << "Second Vertice: ";
            cin >> v2;
            g->deleteEdge(v1, v2);
            for (int i = 0; i < g->getTotalVertice(); i++) {
                for (int j = 0; j < g->getTotalVertice(); j++) {
                    cout << " " << g->getEdgeMatrix(i, j) << " ";
                }
                cout << "\n";
            }
            break;
        default:
            exit = true;
            break;
        }
    }
    while (!exit);
    delete g;
}
