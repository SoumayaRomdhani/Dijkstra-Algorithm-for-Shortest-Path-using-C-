#ifndef LSTPRIM_H_INCLUDED
#define LSTPRIM_H_INCLUDED

#include "lstsdd.h"


Graph createGraph(int V);
GRAPH_MAN createGraphMan(int v);
Node createNode(ELEMENT e, int weight);
NODE_MAN createNodeMan(elem e, int weight);
void addEdge(Graph G, ELEMENT src, ELEMENT dest, int weight);
void addEdgeMan(GRAPH_MAN G, elem src, elem dest, int weight);
void printGraph(Graph G);
void shortestPath(Graph G, char *source, char *dest);
void shortestPathMan(GRAPH_MAN g, char source, char dest, int pos_src, int pos_dest);
void printGraph(Graph G);
int GraphTaille(Graph G);
int estSaturee(Graph G);
int estVide(Graph G);
void noeudDetruire(n);
void noeudDetruireMan(NODE_MAN n);
int existeMan(NODE_MAN n1, NODE_MAN n2);
int recuperer_position(Graph G, char *nom);
int recuperer_positionMan(GRAPH_MAN G, char nom);
ELEMENT recuperer(Graph g, char *nom);
elem recupererMan(GRAPH_MAN g, char c);
char* recuperer_nom(Graph g, int pos);
char recuperer_nomMan(GRAPH_MAN g, int pos);
void printGraph(Graph g);
void printMap(Graph g, char filename[]);
void destroyGraph(GRAPH_MAN g);

#endif // LSTPRIM_H_INCLUDED
