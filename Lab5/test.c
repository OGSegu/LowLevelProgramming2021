#include <mm_malloc.h>
#include <stdio.h>
#include "graph.h"

/*
 * TESTS
 */

int tCreateNode(struct Graph *graph) {
    printf("Node creation: ");
    createNode(graph, 1);
    createNode(graph, 2);
    createNode(graph, 3);
    createNode(graph, 4);
    createNode(graph, 5);
    struct Node *node = getNode(graph, 1);
    if (node->number != 1) {
        return 0;
    }
    struct Node *secondNode = getNode(graph, 10);
    if (secondNode != NULL) {
        return 0;
    }
    return 1;
}

int tRemoveNode(struct Graph *graph) {
    printf("Node deletion: ");
    struct Node *node = getNode(graph, 5);
    if (node == NULL) {
        return 0;
    }
    removeNode(graph, 5);
    if (getNode(graph, 5) != NULL) {
        return 0;
    }
    return 1;
}

int tCreateEdge(struct Graph *graph) {
    printf("Edge creation: ");
    struct Node *firstNode = getNode(graph, 1);
    struct Node *secondNode = getNode(graph, 2);
    struct Node *thirdNode = getNode(graph, 3);
    struct Node *fourthNode = getNode(graph, 4);
    createEdge(graph, firstNode, secondNode, 1);
    createEdge(graph, thirdNode, fourthNode, 6);
    struct Edge *edge = getEdge(graph, firstNode, secondNode);
    if (edge == NULL) {
        return 0;
    }
    return 1;
}

int tRemoveEdge(struct Graph *graph) {
    printf("Edge deletion: ");
    struct Node *firstNode = getNode(graph, 1);
    struct Node *secondNode = getNode(graph, 2);
    struct Edge *edge = getEdge(graph, firstNode, secondNode);
    removeEdge(graph, edge->firstNode, edge->secondNode);
    if (getEdge(graph, firstNode, secondNode) != NULL) {
        return 0;
    } else {
        return 1;
    }
}

int tChangeValueOfNode(struct Graph *graph) {
    printf("Node value changing: ");
    struct Node *node = getNode(graph, 1);
    if (node->number != 1) {
        return 0;
    }
    changeValueOfNode(graph, 1, 8);
    if (node->number != 8) {
        return 0;
    }
    return 1;
}

int tChangeWeightOfEdge(struct Graph *graph) {
    printf("Node weight changing: ");
    struct Edge *edge = getEdge(graph, getNode(graph, 3), getNode(graph, 4));
    if (edge->weight != 6) {
        return 0;
    }
    changeWeightOfEdge(graph, edge, 4);
    if (edge->weight != 4) {
        return 0;
    }
    return 1;
}

void runTests(struct Graph *graph) {
    if (tCreateNode(graph) == 1) {
        printf("success\n");
    } else {
        printf("failed\n");
    }

    if (tCreateEdge(graph) == 1) {
        printf("success\n");
    } else {
        printf("failed\n");
    }

    if (tRemoveEdge(graph) == 1) {
        printf("success\n");
    } else {
        printf("failed\n");
    }

    if (tRemoveNode(graph) == 1) {
        printf("success\n");
    } else {
        printf("failed\n");
    }

    if (tChangeValueOfNode(graph) == 1) {
        printf("success\n");
    } else {
        printf("failed\n");
    }

    if (tChangeWeightOfEdge(graph) == 1) {
        printf("success\n");
    } else {
        printf("failed\n");
    }
}

