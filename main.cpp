#include "Graph.h"

int main() {
    Graph *graph = new Graph();
    graph->populate();
    graph->print();
    delete graph;
    return 0;
}