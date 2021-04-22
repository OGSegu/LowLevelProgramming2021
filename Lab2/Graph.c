#include <stdio.h>
#include <stdlib.h>

struct Graph {
    int amount;
    struct EdgeList *edgeList;
};

struct EdgeList {

};

struct Edge {
    int weight;
    struct Node* firstNode;
    struct Node* secondNode;
};

struct Node {
    char* name;
};

struct Graph* createGraph(int amountOfNode) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->amount = amountOfNode;
    graph->edgeList = (struct EdgeList*) malloc(sizeof(struct Edge) * amountOfNode);
    return graph;
}

void addEdge(struct Graph* graph, struct Node* firstNode, struct Node* secondNode) {
    
}

int main() {
    int amountOfNode = 5;
    struct Graph* graph = createGraph(amountOfNode);
    printf("%d\n", graph->edgeList);
}