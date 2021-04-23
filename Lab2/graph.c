#include <stdio.h>
#include <stdlib.h>
#include "math.h"

struct Graph {
    struct EdgeList *edgeList;
};

struct EdgeList {
    int amount;
    struct Edge *value;
};

struct Edge {
    int weight;
    struct Node *firstNode;
    struct Node *secondNode;
};

struct Node {
    int number;
};


struct Graph *createGraph(int amountOfNode) {
    struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph));
    graph->edgeList = malloc(
            sizeof(struct Edge *) * getMaxNumberOfEdges(amountOfNode) +
            sizeof(struct EdgeList)); // Выделяем макс. возможное кол-во сочетаний точек
    graph->edgeList->amount = 0;
    return graph;
}

struct Node *createNode(int number) {
    struct Node *node = malloc(sizeof(struct Node));
    node->number = number;
    return node;
}

void addEdge(struct Graph *graph, int firstNodeNumber, int secondNodeNumber, int weight) {
    struct Node *firstNode = createNode(firstNodeNumber);
    struct Node *secondNode = createNode(secondNodeNumber);
    struct Edge *edge = malloc(sizeof(struct Edge));
    edge->firstNode = firstNode;
    edge->secondNode = secondNode;
    edge->weight = weight;
    int amount = graph->edgeList->amount;
    graph->edgeList[amount].value = edge;
    graph->edgeList->amount++;
}

void printAllEdges(struct Graph *graph) {
    for (int i = 0; i < graph->edgeList->amount; i++) {
        printf("[%d, %d] | Weight: %d\n", graph->edgeList[i].value->firstNode->number,
               graph->edgeList[i].value->secondNode->number,
               graph->edgeList[i].value->weight);
    }
}

int main() {
    int amountOfNode = 2;
    struct Graph *graph = createGraph(amountOfNode);
    addEdge(graph, 1, 2, 2);
    addEdge(graph, 6, 1, 2);
    addEdge(graph, 2, 4, 2);
    addEdge(graph, 3, 5, 2);
    printAllEdges(graph);
}