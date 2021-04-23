#include <stdio.h>
#include <stdlib.h>
#include "math.h"

struct Graph {
    struct EdgeList *edgeList;
    struct NodeList *nodeList;
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

struct NodeList {
    int amount;
    struct Node *value;
};

struct Node {
    int number;
};


struct Graph *createGraph(int amountOfNode) {
    struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph*));
    graph->nodeList = malloc((sizeof(struct Node *) * amountOfNode) + sizeof(struct NodeList));
    graph->nodeList->amount = 0;
    graph->edgeList = malloc(
            sizeof(struct Edge*) * getMaxNumberOfEdges(amountOfNode) +
            sizeof(struct EdgeList)); // Выделяем макс. возможное кол-во сочетаний точек
    graph->edgeList->amount = 0;
    return graph;
}

void alignEdgeListAfterRemove(struct Graph *graph, int emptyValue) {
    for (int i = emptyValue; i <= graph->edgeList->amount; i++) {
        graph->edgeList[i].value = graph->edgeList[i + 1].value;
    }
}

void alignNodeListAfterRemove(struct Graph *graph, int emptyValue) {
    for (int i = emptyValue; i <= graph->nodeList->amount; i++) {
        graph->nodeList[i].value = graph->nodeList[i + 1].value;
    }
}

struct Node *getNode(struct Graph *graph, int number) {
    for (int i = 0; i < graph->nodeList->amount; i++) {
        struct Node *node = graph->nodeList[i].value;
        if (number == node->number) {
            return node;
        }
    }
    return NULL;
}

int isNodeExists(struct Graph *graph, int number) {
    return getNode(graph, number) != NULL ? 1 : 0;
}


struct Node *createNode(struct Graph *graph, int number) {
    if (isNodeExists(graph, number) == 1) {
        printf("Node is already exists");
        return NULL;
    }
    struct Node *node = malloc(sizeof(struct Node));
    node->number = number;
    int amount = graph->nodeList->amount;
    graph->nodeList[amount].value = node;
    graph->nodeList->amount++;
    return node;
}

void printAllNodes(struct Graph *graph) {
    for (int i = 0; i < graph->nodeList->amount; i++) {
        printf("Node %d: %d\n", i, graph->nodeList[i].value->number);
    }
}


void removeEdgeWithNode(struct Graph *graph, int number) {
    for (int i = 0; i < graph->edgeList->amount; i++) {
        if (graph->edgeList[i].value->firstNode->number == number ||
            graph->edgeList[i].value->secondNode->number == number) {
            alignEdgeListAfterRemove(graph, i);
            graph->edgeList->amount--;
            i = -1;
        }
    }
}

void removeNode(struct Graph *graph, int number) {
    for (int i = 0; i < graph->nodeList->amount; i++) {
        if (graph->nodeList[i].value->number == number) {
            removeEdgeWithNode(graph, number);
            alignNodeListAfterRemove(graph, i);
            graph->nodeList->amount--;
            return;
        }
    }
}


int isEdgeExists(struct Graph *graph, struct Node *firstNode, struct Node *secondNode) {
    int firstNodeValue = firstNode->number;
    int secondNodeValue = secondNode->number;
    for (int i = 0; i < graph->edgeList->amount; i++) {
        int localFirstNodeValue = graph->edgeList[i].value->firstNode->number;
        int localSecondNodeVValue = graph->edgeList[i].value->secondNode->number;
        if ((localFirstNodeValue == firstNodeValue || localFirstNodeValue == secondNodeValue)
            && (localSecondNodeVValue == firstNodeValue || localSecondNodeVValue == secondNodeValue))
            return 1;
    }
    return 0;
}

void createEdge(struct Graph *graph, struct Node *firstNode, struct Node *secondNode, int weight) {
    if (isEdgeExists(graph, firstNode, secondNode) == 1) {
        printf("Edge [%d, %d] already exists\n", firstNode->number, secondNode->number);
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

void removeEdge(struct Graph *graph, struct Node *firstNode, struct Node *secondNode) {
    for (int i = 0; i < graph->edgeList->amount; i++) {
        int localFirstNodeValue = graph->edgeList[i].value->firstNode->number;
        int localSecondNodeVValue = graph->edgeList[i].value->secondNode->number;
        if ((localFirstNodeValue == firstNode->number || localFirstNodeValue == secondNode->number)
            && (localSecondNodeVValue == firstNode->number || localSecondNodeVValue == secondNode->number)) {
            alignEdgeListAfterRemove(graph, i);
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
    int maxNodeAmount = 20;
    struct Graph *graph = createGraph(maxNodeAmount);
    struct Node *firstNode = createNode(graph, 1);
    struct Node *secondNode = createNode(graph, 2);
    struct Node *thirdNode = createNode(graph, 3);
    struct Node *fourthNode = createNode(graph, 4);
    struct Node *fifthNode = createNode(graph, 5);
    struct Node *sixthNode = createNode(graph, 6);
    createEdge(graph, firstNode, secondNode, 1);
    createEdge(graph, thirdNode, firstNode, 1);
    createEdge(graph, thirdNode, firstNode, 1);
    createEdge(graph, fourthNode, fifthNode, 1);
    removeNode(graph, 4);
    printAllNodes(graph);
    printAllEdges(graph);
}
