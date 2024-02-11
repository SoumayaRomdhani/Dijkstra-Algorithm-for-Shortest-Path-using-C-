#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "eltprim.h"
#include "chrprim.h"
#include "lstprim.h"

Graph createGraph(int V){
    Graph G;
    int i;
    G = (Graph)malloc(sizeof(strucGraph));
    if(!G) {

     printf("Problème de mémoire\n") ;
     exit(0) ;}
     G->V=V;
     //ici on souhaite initialiser la table d’adjacence (les listes sont vides)
    for (i = 0; i<V; i++) {
        G->adjList[i]= NULL;
    }
     return G;
}

GRAPH_MAN createGraphMan(int v){
    GRAPH_MAN G;
    int i;
    G = (GRAPH_MAN)malloc(sizeof(strucGraph_man));
    if(!G) {

     printf("Problème de mémoire\n") ;
     exit(0) ;}
     G->v=v;
     //ici on souhaite initialiser la table d’adjacence (les listes sont vides)
    for (i = 0; i<v; i++) {
        G->adjList[i]= NULL;
    }
     return G;
}

void destroyGraph(GRAPH_MAN g){
    int i;
    NODE_MAN n;
    for(i=1; i<=g->v; i++){
        n = g->adjList[i];
        while(n){
            NODE_MAN q = n;
            n = n->next;
            noeudDetruireMan(q);
        }
    }
    free(g);
}

Node createNode(ELEMENT e, int weight){
    Node n;

    n =(Node)malloc(sizeof(structNode));
    if(!n){
    printf ("Plus d'espace\n");
    }
    else{
    elementAffecter(&(n->info), e);
    n->weight=weight;
    n->next = NULL;
    }
    return n;
}

NODE_MAN createNodeMan(elem e, int weight){
    NODE_MAN n;

    n =(NODE_MAN)malloc(sizeof(structNode_man));
    if(!n){
    printf ("Plus d'espace\n");
    }
    else{
    elemAffecter(&(n->info), e);
    n->weight=weight;
    n->next = NULL;
    }
    return n;
}

void printGraph(Graph g){
    printf("Nombre de sommets de ce graphe est %i\n\n", g->V);
    int i, voi;
    Node n;
    for(i=1; i<=g->V; i++){
        printf("\033[0;34m");
        printf("%i. ", i);
        printf("\033[0;36m");
        //printf("%s ", g->adjList[i]->info->nom);
        elementAfficher(g->adjList[i]->info);
        printf("\033[0m");
        n = g->adjList[i]->next;
        voi = 1;
        while(n){
            printf("\n\t\t\t\t\t\t|| %i. ", voi);
            printf("%s (%i KM) ||\n", n->info->nom, n->weight);
            voi++;
            n = n->next;
        }
        printf("\033[0;34m");
        printf("\n\t\t\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        printf("\033[0m");
    }
}

void printGraphMan(GRAPH_MAN g){
    printf("Nombre de sommets de ce graphe est %i\n\n", g->v);
    int i, voi;
    NODE_MAN n;
    for(i=1; i<=g->v; i++){
        printf("\033[0;34m");
        printf("%i. ", i);
        printf("\033[0;36m");
        elemAfficher(g->adjList[i]->info);
        printf("\033[0m");
        n = g->adjList[i]->next;
        voi = 1;
        while(n){
            printf("\n\t\t\t\t\t\t|| %i. ", voi);
            printf("%c (%i) ||\n", n->info, n->weight);
            voi++;
            n = n->next;
        }
        printf("\033[0;34m");
        printf("\n\t\t\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        printf("\033[0m");
    }
}


int recuperer_position(Graph G, char *nom){
    int i=1;
    while(strcmp(G->adjList[i]->info->nom, nom)!=0){
        i++;
    }
    return i;
}

int recuperer_positionMan(GRAPH_MAN G, char c){
    int i=1;
    while(G->adjList[i]->info != c){
        i++;
    }
    return i;
}

char* recuperer_nom(Graph g, int pos){
    char *ch = g->adjList[pos]->info->nom;
    return ch;
}

char recuperer_nomMan(GRAPH_MAN g, int pos){
    char c = g->adjList[pos]->info;
    return c;
}


//initialisation des 3 tableaux
void initialize(Graph g, int src, int *distances, int *visited, int *parent) {
    int i;
    for (i = 1; i <= g->V; i++) {
        distances[i] = 999999;
        visited[i] = 0;
        parent[i] = -1;
    }
    distances[src] = 0;
}

void initializeMan(GRAPH_MAN g, int src, int *distances, int *visited, int *parent) {
    int i;
    for (i = 1; i <= g->v; i++) {
        distances[i] = 999999;
        visited[i] = 0;
        parent[i] = -1;
    }
    distances[src] = 0;
}

// trouver le nœud non visité ayant la plus petite distance
int minDistance(int *distances, int *visited, int V) {
    int min = 999999;
    int minIndex=-1;
    for (int i = 1; i <= V; i++) {
        if (!visited[i] && distances[i] < min) {
            min = distances[i];
            minIndex = i;
        }
    }
    return minIndex;
}
//djikstra
void dijkstra(Graph G, int src, int* visited, int* parent, int* distances){
initialize(G, src, distances, visited, parent);
int weight,r, n=1;

for (int i = 1; i < G->V ; i++) {
 // Recherche du noeud non visité ayant la distance minimale
        int u =minDistance(distances, visited, G->V);

// Marquage du noeud comme visité
        visited[u] = 1;
// Mise à jour des distances des noeuds adjacents non visités
        Node courant = G->adjList[u];
        while (courant != NULL) {
            char *ch = courant->info->nom;
            int weight = courant->weight;
            r = recuperer_position(G, ch);
            if (!visited[r] && (distances[u] + weight) < distances[r]) {
                distances[r] = distances[u] + weight;
                parent[r] = u;
            }

            courant = courant->next;
        }
    }

}

void dijkstraMan(GRAPH_MAN G, int src, int* visited, int* parent, int* distances){
initializeMan(G, src, distances, visited, parent);
int weight,r, n=1;

for (int i = 1; i < G->v ; i++) {
 // Recherche du noeud non visité ayant la distance minimale
        int u =minDistance(distances, visited, G->v);

// Marquage du noeud comme visité
        visited[u] = 1;
// Mise à jour des distances des noeuds adjacents non visités
        NODE_MAN courant = G->adjList[u];
        while (courant != NULL) {
            char ch = courant->info;
            int weight = courant->weight;
            r = recuperer_positionMan(G, ch);
            if (!visited[r] && (distances[u] + weight) < distances[r]) {
                distances[r] = distances[u] + weight;
                parent[r] = u;
            }

            courant = courant->next;
        }
    }

}

int existe2(int* path, int n, int x){
    int i=1, test=0;
    while(!test && i<n){
        if(path[i]==x){
            test=1;
        }
        i++;
    }
    return test;
}


void printMap(Graph g, char filename[]) {
    int i;
    int gouv;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }
    char line[100];
    while (fgets(line, 100, file)){
        for(i=0; i<strlen(line); i++){
            if(line[i]>='0' && line[i]<='9'){
                gouv = line[i] - '0';
                    printf("\033[0;31m");
                    printf("%i", gouv);
                    printf("\033[0;0m");
            }else{
                printf("%c", line[i]);
            }
        }
    }

    fclose(file);
}


void printMap2(Graph g, char filename[], int* path, int n) {
    int i;
    int gouv;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }
    char line[100];
    while (fgets(line, 100, file)){
        i = 0;
        while(i<strlen(line)){
            if(line[i]>='0' && line[i]<='9'){
                gouv = 0;
                while(line[i]>='0' && line[i]<='9'){
                    gouv = (gouv*10) + (line[i] - '0');
                    i++;
                }
                if(existe2(path, n, gouv)){
                        printf("\033[0;31m");
                        printf("%i", gouv);
                        printf("\033[0;0m");
                }else{
                        printf("%i", gouv);
                }
                printf("%c", line[i]);
            }else{
                printf("%c", line[i]);
            }
            i++;
        }
    }

    fclose(file);
}

void shortestPath(Graph G, char *source, char *dest){
    int visited[25], parent[25], distances[25], path[25], n=0, src = recuperer_position(G, source), i;
    dijkstra(G, src, visited, parent, distances);
    n++;    path[n] = recuperer_position(G, dest);
    while(path[n] != -1){
        n++;
        path[n] = parent[path[n-1]];
    }
    system("cls");
    printf("\033[0;33m");
    printf("Shortest path is %s", source);
    for(i=n-2; i>0; i--){
        printf(" > %s", recuperer_nom(G, path[i]));
    }
    printf("\nDistance = %i KM\n", distances[path[1]]);
    printf("\033[0;0m");
    //printMap(G, "map.txt");
    printMap2(G, "map.txt", path, n);


}

void shortestPathMan(GRAPH_MAN g, char source, char dest, int pos_src, int pos_dest){
    int visited2[(g->v)+1], parent2[(g->v)+1], distances2[(g->v)+1], path2[(g->v)+1], n=0, i;
    dijkstraMan(g, pos_src, visited2, parent2, distances2);
    n++;
    path2[n] = pos_dest;
    while(path2[n] != -1){
        n++;
        path2[n] = parent2[path2[n-1]];
    }
    system("cls");
    printf("\033[0;33m");
    printf("Shortest path is %c", source);
    for(i=n-2; i>0; i--){
        printf(" > %c", recuperer_nomMan(g, path2[i]));
    }
    printf("\nDistance = %i\n", distances2[path2[1]]);
    printf("\033[0;0m");
}


int existe(Node n1, Node n2){
    while(n1 && (elementComparer(n1->info,n2->info)!=0)){
        n1 = n1->next;
    }
    if(n1 == NULL){
        return 0;
    }
    return 1;
}

int existeMan(NODE_MAN n1, NODE_MAN n2){
    while(n1 && (n1->info!=n2->info)){
        n1 = n1->next;
    }
    if(n1 == NULL){
        return 0;
    }
    return 1;
}

void addEdge(Graph G, ELEMENT src, ELEMENT dest, int weight){
     int i=1,trouve=0;
     Node n1=createNode(dest ,weight);
     Node n2=createNode(src ,weight);
     while(!(trouve) && (i<=G->V)){
        if(elementComparer(src,G->adjList[i]->info)==0){
           trouve=1;
           if(!existe(G->adjList[i]->next, n1)){
              if(G->adjList[i]->next==NULL){
                G->adjList[i]->next=n1;
                n1->next=NULL;}
              else{
                n1->next=G->adjList[i]->next;
                G->adjList[i]->next=n1;}
            }
        }
        else{
            i++;
        }
    }
    trouve = 0;
    i = 1;
     while(!(trouve) && (i<=G->V)){
        if(elementComparer(dest,G->adjList[i]->info)==0){
           trouve=1;
            if(!existe(G->adjList[i]->next, n2)){
                if(G->adjList[i]->next==NULL){
                    G->adjList[i]->next=n2;
                    n2->next=NULL;
                }
                else{
                    n2->next=G->adjList[i]->next;
                    G->adjList[i]->next=n2;
                }
            }
        }
        else{
            i++;
        }
    }

}

void addEdgeMan(GRAPH_MAN G, elem src, elem dest, int weight){
     int i=1,trouve=0;
     NODE_MAN n1=createNodeMan(dest ,weight);
     NODE_MAN n2=createNodeMan(src ,weight);
     while(!(trouve) && (i<=G->v)){
        if(src==G->adjList[i]->info){
           trouve=1;
           if(!existeMan(G->adjList[i]->next, n1)){
              if(G->adjList[i]->next==NULL){
                G->adjList[i]->next=n1;
                n1->next=NULL;}
              else{
                n1->next=G->adjList[i]->next;
                G->adjList[i]->next=n1;}
            }
        }
        else{
            i++;
        }
    }
    trouve = 0;
    i = 1;
     while(!(trouve) && (i<=G->v)){
        if(dest==G->adjList[i]->info){
           trouve=1;
            if(!existeMan(G->adjList[i]->next, n2)){
                if(G->adjList[i]->next==NULL){
                    G->adjList[i]->next=n2;
                    n2->next=NULL;
                }
                else{
                    n2->next=G->adjList[i]->next;
                    G->adjList[i]->next=n2;
                }
            }
        }
        else{
            i++;
        }
    }

}

void noeudDetruire(Node n){
    elementDetruire(n ->info);
    free(n);
}
void noeudDetruireMan(NODE_MAN n){
    elemDetruire(n ->info);
    free(n);
}

int GraphTaille(Graph G) {
    return (G->V);
}

int estSaturee(Graph G) {
    Node temp;
    int saturee = 1;
    temp = (Node) malloc ( sizeof ( structNode ) );
    if(temp != NULL) {
        saturee = 0; /* mémoire non saturée */
        free(temp);
    }
    return saturee;
}

int estVide(Graph G){
    return (G->V == 0);
}

ELEMENT recuperer(Graph g, char *ch) {
    ELEMENT elt= elementCreer();
    int i=1, test=0;
    if (g->V == 0)

    printf ("Graph est vide\n");

    else {
        while(!test && i<=24){
            if(strcmp(g->adjList[i]->info->nom, ch)==0){
                test = 1;
                elementAffecter(&elt, g->adjList[i]->info);
            }else{
                i++;
            }
        }
    }

    return(elt);
}

elem recupererMan(GRAPH_MAN g, char c) {
    elem elt= elemCreer();
    int i=1, test=0;
    if (g->v == 0)

    printf ("Graphe est vide\n");

    else {
        while(!test && i<=g->v){
            if(g->adjList[i]->info==c){
                test = 1;
                elemAffecter(&elt, g->adjList[i]->info);
            }else{
                i++;
            }
        }
    }

    return(elt);
}

