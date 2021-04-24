#ifndef LOWLEVELPROGRAMMING2021_GRAPH_H
#define LOWLEVELPROGRAMMING2021_GRAPH_H

struct Graph;
struct EdgeList;
struct Edge;
struct NodeList;
struct Node;

struct Node *createNode(struct Graph *graph, int number);

struct Node *getNode(struct Graph *graph, int number);

int isNodeExists(struct Graph *graph, int number);

int isEdgeExists(struct Graph *graph, struct Node *firstNode, struct Node *secondNode);

void removeNode(struct Graph *graph, int number);

void printAllNodes(struct Graph *graph);

struct Edge *createEdge(struct Graph *graph, struct Node *firstNode, struct Node *secondNode, int weight);

void removeEdge(struct Graph *graph, struct Node *firstNode, struct Node *secondNode);

void printAllEdges(struct Graph *graph);

void changeValueOfNode(struct Graph *graph, int fromValue, int toValue);

void changeWeightOfEdge(struct Graph *graph, struct Edge *edge, int newWeight);
#endif //LOWLEVELPROGRAMMING2021_GRAPH_H
