#ifndef LSTCHR_H_INCLUDED
#define LSTCHR_H_INCLUDED

#include "eltprim.h"
#include "chrprim.h"
#define longmax 50


typedef struct structNode_man {
    elem info;
    int weight;
    struct structNode_man* next;
} structNode_man, *NODE_MAN;

typedef struct {
    int v;
    NODE_MAN adjList[longmax];
} strucGraph_man, *GRAPH_MAN;




typedef struct structNode {
    ELEMENT info;
    int weight;
    struct structNode* next;
} structNode, *Node;

typedef struct {
    int V;
    Node adjList[25];
} strucGraph, *Graph;


#endif // LSTCHR_H_INCLUDED
