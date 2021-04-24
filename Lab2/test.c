#include "graph.h"

/*
 * TESTS
 */
int tCreateNode(struct Graph *graph) {
    createNode(graph, 1);
    createNode(graph, 2);
}

void runTests(struct Graph *graph) {
    tCreateNode(graph);
}

