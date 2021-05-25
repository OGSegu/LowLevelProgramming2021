#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "math.h"

struct Graph *createGraph(int amountOfNode) {
    struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph *));
    graph->nodeList = malloc((sizeof(struct Node *) * amountOfNode) + sizeof(struct NodeList));
    graph->nodeList->amount = 0;
    graph->edgeList = malloc(
            sizeof(struct Edge *) * getMaxNumberOfEdges(amountOfNode) +
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

struct Edge *getEdge(struct Graph *graph, struct Node *firstNode, struct Node *secondNode) {
    int firstNodeValue = firstNode->number;
    int secondNodeValue = secondNode->number;
    for (int i = 0; i < graph->edgeList->amount; i++) {
        int localFirstNodeValue = graph->edgeList[i].value->firstNode->number;
        int localSecondNodeVValue = graph->edgeList[i].value->secondNode->number;
        if ((localFirstNodeValue == firstNodeValue || localFirstNodeValue == secondNodeValue)
            && (localSecondNodeVValue == firstNodeValue || localSecondNodeVValue == secondNodeValue))
            return graph->edgeList[i].value;
    }
    return NULL;
}

int isEdgeExists(struct Graph *graph, struct Node *firstNode, struct Node *secondNode) {
    return getEdge(graph, firstNode, secondNode) != NULL ? 1 : 0;
}

// Создание вершины
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

// Удаление вершины
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

// Вывести все вершины
void printAllNodes(struct Graph *graph) {
    for (int i = 0; i < graph->nodeList->amount; i++) {
        printf("Node %d: %d\n", i, graph->nodeList[i].value->number);
    }
}

// Создание ребра
struct Edge *createEdge(struct Graph *graph, struct Node *firstNode, struct Node *secondNode, int weight) {
    if (isEdgeExists(graph, firstNode, secondNode) == 1) {
        printf("Edge [%d, %d] already exists\n", firstNode->number, secondNode->number);
        return NULL;
    }
    struct Edge *edge = malloc(sizeof(struct Edge));
    edge->firstNode = firstNode;
    edge->secondNode = secondNode;
    edge->weight = weight;
    int amount = graph->edgeList->amount;
    graph->edgeList[amount].value = edge;
    graph->edgeList->amount++;
    return edge;
}

// Удаление ребра
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

// Вывести все ребра
void printAllEdges(struct Graph *graph) {
    for (int i = 0; i < graph->edgeList->amount; i++) {
        printf("[%d, %d] | Weight: %d\n", graph->edgeList[i].value->firstNode->number,
               graph->edgeList[i].value->secondNode->number,
               graph->edgeList[i].value->weight);
    }
}

// Записать все ребра в файл
void printAllEdgesToFile(struct Graph *graph, FILE *file) {
    for (int i = 0; i < graph->edgeList->amount; i++) {
        fprintf(file, "[%d, %d] | Weight: %d\n", graph->edgeList[i].value->firstNode->number,
                graph->edgeList[i].value->secondNode->number,
                graph->edgeList[i].value->weight);
    }
    fclose(file);
}

// Изменение значение вершины
void changeValueOfNode(struct Graph *graph, int fromValue, int toValue) {
    if (isNodeExists(graph, toValue) == 1) {
        printf("Value %d already exists\n", toValue);
        return;
    }
    for (int i = 0; i < graph->nodeList->amount; i++) {
        if (graph->nodeList[i].value->number == fromValue)
            graph->nodeList[i].value->number = toValue;
    }
}

// Изменение веса ребра
void changeWeightOfEdge(struct Graph *graph, struct Edge *edge, int newWeight) {
    if (isEdgeExists(graph, edge->firstNode, edge->secondNode) == 0) {
        printf("Edge doesn't exist\n");
        return;
    }
    for (int i = 0; i < graph->edgeList->amount; i++) {
        if ((graph->edgeList[i].value->firstNode == edge->firstNode ||
             graph->edgeList[i].value->firstNode == edge->secondNode)
            && (graph->edgeList[i].value->secondNode == edge->firstNode ||
                graph->edgeList[i].value->secondNode == edge->secondNode)) {
            graph->edgeList[i].value->weight = newWeight;
        }
    }
}
