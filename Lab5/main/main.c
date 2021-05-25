#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "../graph.h"

int main(int argc, char *argv[]) {
    printf("%d\n", argc);
    printf("%s\n", argv[1]);
    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    struct Graph *graph = parseFile(file);

    printAllEdges(graph);
    removeNode(graph, 3);
    printf("Removed node 3\n");
    printAllEdges(graph);
    struct Edge *edge = getEdge(graph, getNode(graph, 1), getNode(graph, 2));
    printf("Weight of edge [1,2] was changed from 2 to 4\n");
    changeWeightOfEdge(graph, edge, 4);
    printAllEdges(graph);

    FILE *outputFile;
    outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    printAllEdgesToFile(graph, outputFile);

    return 0;
}

struct Graph *parseFile(FILE *file) {
    const int multiplier = 10;

    struct Edge *pEdge;
    struct Graph *graph;
    int maxAmountOfVertex = 0;
    int firstNodeNumber = 0;
    int secondNodeNumber = 0;
    struct Node *firstNode = NULL;
    struct Node *secondNode = NULL;
    int weight = 0;
    /**
     * -1 - set first node
     * 0 - set second node
     * 1 - set weight
     * 2 - create edge
     */
    char current;
    int mode = -1;

    while ((current = fgetc(file)) != -1) {
        if (current == '\n')
            continue;
        if (maxAmountOfVertex == 0) {
            maxAmountOfVertex = (int) current - 48;
            graph = createGraph(maxAmountOfVertex);
            printf("Graph with %d vertex was created\n", maxAmountOfVertex);
            continue;
        }
        switch (mode) {
            case -1:
                if (current == ':') {
                    firstNode = createNode(graph, firstNodeNumber);
                    if (firstNode == NULL) {
                        firstNode = getNode(graph, firstNodeNumber);
                    }
                    printf("First node was set\n");
                    firstNodeNumber = 0;
                    mode++;
                } else if (current == '[') {
                    continue;
                } else {
                    firstNodeNumber = firstNodeNumber * multiplier + ((int) current - 48);
                    printf("Counting first node number %d\n", firstNodeNumber);
                }
                break;
            case 0:
                if (current == '-') {
                    secondNode = createNode(graph, secondNodeNumber);
                    if (secondNode == NULL) {
                        secondNode = getNode(graph, secondNodeNumber);
                    }
                    printf("Second node was set\n");
                    secondNodeNumber = 0;
                    mode++;
                } else {
                    secondNodeNumber = secondNodeNumber * multiplier + ((int) current - 48);
                    printf("Counting second node number %d\n", secondNodeNumber);
                }
                break;
            case 1:
                if (current == ']') {
                    pEdge = createEdge(graph, firstNode, secondNode, weight);
                    printf("Edge [%d, %d] - %d was created\n", pEdge->firstNode->number, pEdge->secondNode->number,
                           pEdge->weight);
                    firstNode = NULL;
                    secondNode = NULL;
                    weight = 0;
                    mode = -1;
                } else {
                    weight = weight * multiplier + ((int) current - 48);
                    printf("Counting weight %d\n", weight);
                }
                break;
        }
    }
    return graph;
}

