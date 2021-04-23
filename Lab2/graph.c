#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define true 1;
#define false 0;

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

int isEdgeExists(struct Graph *graph, struct Node *firstNode, struct Node *secondNode) {
    int firstNodeValue = firstNode->number;
    int secondNodeValue = secondNode->number;
    for (int i = 0; i < graph->edgeList->amount; i++) {
        int localFirstNodeValue = graph->edgeList[i].value->firstNode->number;
        int localSecondNodeVValue = graph->edgeList[i].value->secondNode->number;
        if ((localFirstNodeValue == firstNodeValue || localFirstNodeValue == secondNodeValue)
            && (localSecondNodeVValue == firstNodeValue || localSecondNodeVValue == secondNodeValue))
            return true;
    }
    return false;
}

void addEdge(struct Graph *graph, int firstNodeNumber, int secondNodeNumber, int weight) {
    struct Node *firstNode = createNode(firstNodeNumber);
    struct Node *secondNode = createNode(secondNodeNumber);
    if (isEdgeExists(graph, firstNode, secondNode) == 1) {
        printf("Edge already exists\n");
        return;
    }
    struct Edge *edge = malloc(sizeof(struct Edge));
    edge->firstNode = firstNode;
    edge->secondNode = secondNode;
    edge->weight = weight;
    int amount = graph->edgeList->amount;
    graph->edgeList[amount].value = edge;
    graph->edgeList->amount++;
}


void alignListAfterRemove(struct Graph *graph, int emptyValue) {
    for (int i = emptyValue; i <= graph->edgeList->amount; i++) {
        graph->edgeList[i].value = graph->edgeList[i + 1].value;
    }
}

void removeEdge(struct Graph *graph, int firstNodeValue, int secondNodeValue) {
    for (int i = 0; i < graph->edgeList->amount; i++) {
        int localFirstNodeValue = graph->edgeList[i].value->firstNode->number;
        int localSecondNodeVValue = graph->edgeList[i].value->secondNode->number;
        if ((localFirstNodeValue == firstNodeValue || localFirstNodeValue == secondNodeValue)
            && (localSecondNodeVValue == firstNodeValue || localSecondNodeVValue == secondNodeValue)) {
            alignListAfterRemove(graph, i);
            graph->edgeList->amount--;
            return;
        }
    }
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
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 2, 3, 2);
    addEdge(graph, 1, 5, 2);
    removeEdge(graph, 1, 2);
    printAllEdges(graph);
}