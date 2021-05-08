#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include "graphm.h"

using namespace std;

GraphM::GraphM() {
    for(int i = 1; i < MAXNODES; i++) {
        for(int j = 1; j < MAXNODES; j++) {
            T[i][j].visited = false;
            T[i][j].dist = INT_MAX;
            T[i][j].path = 0;
            C[i][j] = INT_MAX;
        }
    }
    size = 0;
}

GraphM::~GraphM() {
    for(int i = 1; i <= size; i++) {
        delete data[i];
        data[i] = nullptr;
    }
}

void GraphM::buildGraph(ifstream &infile) {
    string title;
    int from, to, cost, count;

    infile >> count;
    getline(infile, title);

    for(int i = 1; i <= count; i++) {
        getline(infile, title);
        NodeData *node = new NodeData(title);
        data[i] = node;
        size++;

        // // Check to display names.
        cout << i << " " << *data[i];
        cout << endl;
    }

    infile >> from >> to >> cost;
        
    while(from != 0 && to != 0 && cost != 0) {
        C[from][to] = cost;
        infile >> from >> to >> cost;     

        // Display data input.
        cout << from << " " << to << " " << cost << endl;   
    }
}

void GraphM::insertEdge(int from, int to, int weight) {
    C[from][to] = weight;
}

void GraphM::removeEdge(int from, int to) {
    C[from][to] = INT_MAX;
}

void GraphM::findShortestPath() {
    
    int v = 0;
    int vWeight = INT_MAX;
    
    for(int source = 1; source <= size; source++) {
        

        T[source][source].dist = 0;

        for(int i = 1; i <= size; i++) {
            if(C[source][i] != INT_MAX) {
                T[source][i].dist = C[source][i];
                T[source][i].path = source;
            }
        }
        
        while(true) {

            v = 0;
            vWeight = INT_MAX;

            for(int i = 1; i <= size; i++) {
                if(!T[source][i].visited && C[source][i] < vWeight) {
                    v = i;
                    vWeight = C[source][i];
                }
            }

            if(v == 0) break;

            T[source][v].visited = true;

            for(int w = 1; w <= size; w++) {

                if(!T[source][w].visited && C[v][w] != INT_MAX && v != w) {
                    if (T[source][w].dist > T[source][v].dist + C[v][w]) {
                        T[source][w].dist = T[source][v].dist + C[v][w];
                        T[source][w].path = v;
                    }
                }
            }

        }
    }
    
}