#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eltprim.h"
#include "chrprim.h"
#include "lstprim.h"



int alpha(elem c){
    int test = 1;
    if(toupper(c)<'A' || toupper(c)>'Z'){
        test = 0;
    }
    return test;

}

int existe_caractere(char* ch, int n, elem c){
    int i=0, trouve = 0;
    while(!trouve && i<n){
        if(ch[i] == c){
            trouve = 1;
        }
        i++;
    }
    return trouve;
}

int chercher(int *T, int n, int x){
    int i=0;
    while(T[i]!=x && i<n){
        i++;
    }
    return i==n;

}

void autoReadGraphFromFile(Graph g, char filename[]) {
    int i=1;
    char nom[20];
    int population, superficie, nbmuni, j, m, a, weight, tmp;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }
    char line[100];
    g->V = atoi(fgets(line, 100, file));
    while ((i<=g->V) && (fgets(line, 100, file))){
        ELEMENT e=elementCreer();
        strcpy(nom, strtok(line, " "));
        j = atoi(strtok(NULL, " "));
        m = atoi(strtok(NULL, " "));
        a = atoi(strtok(NULL, " "));
        population = atoi(strtok(NULL, " "));
        superficie = atoi(strtok(NULL, " "));
        nbmuni = atoi(strtok(NULL, " "));


        strcpy(e->nom, nom);
        e->population=population;
        e->superficie=superficie;
        e->nb_municipalites=nbmuni;
        e->date_creation.jour=j;
        e->date_creation.mois=m;
        e->date_creation.annee=a;

        Node n=createNode(e,weight);
        g->adjList[i]=n;
        i++;
    }
        for(j=1; j<=g->V; j++){
            fgets(line, 100, file);
            tmp = atoi(strtok(line, " "));
            for(i=1; i<=tmp; i++){
                ELEMENT e = elementCreer();
                strcpy(nom, strtok(NULL, " "));
                elementAffecter(&e, recuperer(g, nom));
                weight = atoi(strtok(NULL, " "));
                addEdge(g, g->adjList[j]->info, e, weight);
            }
        }

    fclose(file);
}


void main(){
    Graph g = createGraph(24);
    GRAPH_MAN gm;
    char filename[] = "gouvernorats2.txt", continuer;
    int choix, k, j, voisin, i, nb_voisin, weight, detruit = 1;

    do{

        int test_cont=1;
        do{
            system("cls");
            printf("\033[0;33m");
            printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
            printf("\033[0;32m");
            printf(" __   __  _\n");
            printf("|  | |__ | | | |  |  0\n");
            printf("|  | |__ | |_| |__|  0\n\n");
            printf("\033[0;0m");
            printf("1.Creer un graph automatiquement\n2.Creer un graph manuellement\n3.Quitter\n");
            printf("\033[0;33m");
            printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
            printf("\033[0;0m");
            printf("Entrer vore choix > ");
            scanf("%i", &choix);
        }while(choix<1 || choix>3);


        if(choix == 1){
            autoReadGraphFromFile(g, filename);
            int choix1;
            char continuer1;
            do{
                do{
                    system("cls");
                    printf("\033[0;33m");
                    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                    printf("\033[0;32m");
                    printf(" __   __  _\n");
                    printf("|  | |__ | | | |  |  0\n");
                    printf("|  | |__ | |_| |__|  0\n\n");
                    printf("\033[0;0m");
                    printf("1.Chercher shortest path entre deux gouvernorats donnes\n2.Voir info sur un gouvernorat donne\n3.Voir le Graphe avec tous les informations sur chaque noeud\n4.Voir le Graphe de la tunisie\n5.Revenir au menu principal\n");
                    printf("\033[0;33m");
                    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
                    printf("\033[0;0m");
                    printf("Entrer vore choix > ");
                    scanf("%i", &choix1);
                }while(choix1<1 || choix1>5);
                if(choix1==1){
                    int tmp, k;
                    char *souurc, *dees;
                    do{
                    system("cls");
                    for(k=1; k<=24; k=k+2){
                        printf("%i. %s\t\t\t\t%i. %s\n", k, g->adjList[k]->info->nom, k+1, g->adjList[k+1]->info->nom);
                    }
                    printf("\nChoisisez la source > ");
                    scanf("%i", &tmp);
                    }while(tmp < 1 || tmp > 24);
                    souurc = recuperer_nom(g, tmp);
                    do{
                    system("cls");
                    for(k=1; k<=24; k=k+2){
                        printf("%i. %s\t\t\t\t%i. %s\n", k, g->adjList[k]->info->nom, k+1, g->adjList[k+1]->info->nom);
                    }
                    printf("\nChoisisez votre destination > ");
                    scanf("%i", &tmp);
                    }while((tmp < 1 || tmp > 24) || recuperer_position(g, souurc) == tmp);
                    dees = recuperer_nom(g, tmp);

                    shortestPath(g, souurc, dees);
                }else if(choix1==2){
                    int tmp, voi;
                    Node n;
                    do{
                    system("cls");
                    for(k=1; k<=24; k=k+2){
                        printf("%i. %s\t\t\t\t%i. %s\n", k, g->adjList[k]->info->nom, k+1, g->adjList[k+1]->info->nom);
                    }
                    printf("\nChoisisez un gouvernorat > ");
                    scanf("%i", &tmp);
                    }while(tmp < 1 || tmp > 24);
                    system("cls");
                    //printf("\033[0;34m");
                    //printf("%i. ", tmp);
                    printf("\033[0;36m");
                    //printf("%s ", g->adjList[i]->info->nom);
                    elementAfficher(g->adjList[tmp]->info);
                    printf("\033[34m");
                    n = g->adjList[tmp]->next;
                    voi = 1;
                    printf("\n\t\t\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                    printf("\033[0;0m");
                    while(n){
                        printf("\n\t\t\t\t\t\t|| %i. ", voi);
                        printf("%s (%i KM) ||\n", n->info->nom, n->weight);
                        voi++;
                        n = n->next;
                    }
                    printf("\033[0;34m");
                    printf("\n\t\t\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
                    printf("\033[0m");
                }else if(choix1 == 3){
                    system("cls");
                    printGraph(g);
                }else if(choix1 == 4){
                    system("cls");
                    printMap(g, "map.txt");
                }else{
                    test_cont = 0;
                }
                if(test_cont){
                    do{
                        printf("\nVoulez vous revenir au menu principal (O/N)? > ");
                        fflush(stdin);
                        scanf("%c", &continuer1);
                        continuer1 = toupper(continuer1);
                    }while(continuer1 != 'O' && continuer1 != 'N');
                    test_cont = (continuer1 != 'O');
                }else{
                    continuer1='O';
                }
        }while(test_cont || continuer1=='N');

        }else if(choix == 2){
            //partie manuelle
            int v, i, m, j, k, pair, choix2, weight2;
            char continuer2;
            if(detruit){
            system("cls");
            detruit = 0;
            do{
                printf("Donner le nombre total des noeuds > ");
                scanf("%i", &v);
            }while(v<2);
            gm = createGraphMan(v);
            char ch[v];
            m = 0;
            for(i=1; i<=v; i++){
                elem e = elemCreer();
                do{
                    printf("Donner un caractere pour le noeuds numero %i > ", i);
                    fflush(stdin);
                    scanf("%c", &e);
                }while(!alpha(e) || existe_caractere(ch, strlen(ch), e));
                ch[m] = e;
                m++;
                NODE_MAN n = createNodeMan(e, 0);
                gm->adjList[i] = n;
            }

            for(i=1; i<=gm->v; i++){
                do{
                    system("cls");
                    printf("Donner le nombre des voisins du noeud %c > ", gm->adjList[i]->info);
                    scanf("%i", &nb_voisin);
                }while(nb_voisin<1 || nb_voisin>(gm->v)-1);

                int T[nb_voisin+1];
                T[0] = i;
                m = 1;
                for(j=1; j<=nb_voisin; j++){
                    do{
                        system("cls");
                        if((gm->v)%2 == 0){
                            pair = 0;
                        }else{
                            pair = 1;
                        }
                        for(k=1; k<=(gm->v)-pair; k=k+2){
                            printf("%i. %c\t\t\t\t%i. %c\n", k, gm->adjList[k]->info, k+1, gm->adjList[k+1]->info);
                        }
                        if(pair){
                            printf("%i. %c\n", k, gm->adjList[k]->info);
                        }
                        printf("\nVoisin %i de %c > ", j, gm->adjList[i]->info);
                        scanf("%i", &voisin);
                    }while((voisin < 1 || voisin > gm->v) || chercher(T, m, voisin)==0);
                    T[m] = voisin;
                    m++;
                    do{
                        printf("Donner le poids entre %c et %c > ", gm->adjList[i]->info, gm->adjList[voisin]->info);
                        scanf("%i", &weight2);
                    }while(weight2<=0);

                    //elem e = elementCreer();
                    //elemAffecter(&e, recupererMan(gm, gm->adjList[voisin]->info));
                    elem e = recupererMan(gm, gm->adjList[voisin]->info);
                    addEdgeMan(gm, gm->adjList[i]->info, e, weight2);

                    }
                }

            }
                do{
                do{
                    system("cls");
                    printf("\033[0;33m");
                    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                    printf("\033[0;32m");
                    printf(" __   __  _\n");
                    printf("|  | |__ | | | |  |  0\n");
                    printf("|  | |__ | |_| |__|  0\n\n");
                    printf("\033[0;0m");
                    printf("1.Chercher shortest path entre deux noeuds donnees\n2.Voir info sur un noeud donne\n3.Voir le Graphe avec toutes les informations sur chaque noeud du graphes\n4.Creer un Graphe (Attention, ceci va detruire le Graphe precedent !)\n5.Detruire le Graphe\n6.Revenir au menu principal\n");
                    printf("\033[0;33m");
                    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
                    printf("\033[0;0m");
                    printf("Entrer vore choix > ");
                    scanf("%i", &choix2);
                }while(choix2<1 || choix2>6);
                if(choix2 == 1){
                    int src, dest;
                    char source, destin;
                    do{
                        system("cls");
                        if((gm->v)%2 == 0){
                            pair = 0;
                        }else{
                            pair = 1;
                        }
                        for(k=1; k<=(gm->v)-pair; k=k+2){
                            printf("%i. %c\t\t\t\t%i. %c\n", k, gm->adjList[k]->info, k+1, gm->adjList[k+1]->info);
                        }
                        if(pair){
                            printf("%i. %c\n", k, gm->adjList[k]->info);
                        }
                        printf("\nChoisisez une source > ");
                        scanf("%i", &src);
                    }while(src < 1 || src > gm->v);
                    source = gm->adjList[src]->info;

                    do{
                        system("cls");
                        if((gm->v)%2 == 0){
                            pair = 0;
                        }else{
                            pair = 1;
                        }
                        for(k=1; k<=(gm->v)-pair; k=k+2){
                            printf("%i. %c\t\t\t\t%i. %c\n", k, gm->adjList[k]->info, k+1, gm->adjList[k+1]->info);
                        }
                        if(pair){
                            printf("%i. %c\n", k, gm->adjList[k]->info);
                        }
                        printf("\nChoisisez une destination > ");
                        scanf("%i", &dest);
                    }while(dest < 1 || dest > gm->v || dest == src);
                    destin = gm->adjList[dest]->info;
                    shortestPathMan(gm, source, destin, src, dest);
                }else if(choix2==2){
                    int tmp2, voi;
                    NODE_MAN n;
                    do{
                        system("cls");
                        if((gm->v)%2 == 0){
                            pair = 0;
                        }else{
                            pair = 1;
                        }
                        for(k=1; k<=(gm->v)-pair; k=k+2){
                            printf("%i. %c\t\t\t\t%i. %c\n", k, gm->adjList[k]->info, k+1, gm->adjList[k+1]->info);
                        }
                        if(pair){
                            printf("%i. %c\n", k, gm->adjList[k]->info);
                        }
                        printf("\nChoisisez un noeud > ");
                        scanf("%i", &tmp2);
                    }while(tmp2 < 1 || tmp2 > gm->v);

                    system("cls");
                    //printf("\033[0;34m");
                    //printf("%i. ", tmp2);
                    printf("\033[0;36m");
                    printf(". ");
                    //printf("%s ", g->adjList[i]->info->nom);
                    elemAfficher(gm->adjList[tmp2]->info);
                    printf("\033[34m");
                    n = gm->adjList[tmp2]->next;
                    voi = 1;
                    printf("\n\t\t\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                    printf("\033[0;0m");
                    while(n){
                        printf("\n\t\t\t\t\t\t|| %i. ", voi);
                        printf("%c (%i) ||\n", n->info, n->weight);
                        voi++;
                        n = n->next;
                    }
                    printf("\033[0;34m");
                    printf("\n\t\t\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
                    printf("\033[0m");
                }
                else if(choix2 == 3){
                    system("cls");
                    printGraphMan(gm);
                }else if(choix2 == 4){
                if(!detruit){
                    destroyGraph(gm);
                    detruit = 1;
                }
                system("cls");
                int v, i, m, j, k, pair, weight2;
                detruit = 0;
                do{
                    printf("Donner le nombre total des noeuds > ");
                    scanf("%i", &v);
                }while(v<2);
                gm = createGraphMan(v);
                char ch[v];
                m = 0;
                for(i=1; i<=v; i++){
                    elem e = elemCreer();
                    do{
                        printf("Donner un caractere pour le noeuds numero %i > ", i);
                        fflush(stdin);
                        scanf("%c", &e);
                    }while(!alpha(e) || existe_caractere(ch, strlen(ch), e));
                    ch[m] = e;
                    m++;
                    NODE_MAN n = createNodeMan(e, 0);
                    gm->adjList[i] = n;
                }

                for(i=1; i<=gm->v; i++){
                    do{
                        system("cls");
                        printf("Donner le nombre des voisins du noeud %c > ", gm->adjList[i]->info);
                        scanf("%i", &nb_voisin);
                    }while(nb_voisin<1 || nb_voisin>(gm->v)-1);

                    int T[nb_voisin+1];
                    T[0] = i;
                    m = 1;
                    for(j=1; j<=nb_voisin; j++){
                        do{
                            system("cls");
                            if((gm->v)%2 == 0){
                                pair = 0;
                            }else{
                                pair = 1;
                            }
                            for(k=1; k<=(gm->v)-pair; k=k+2){
                                printf("%i. %c\t\t\t\t%i. %c\n", k, gm->adjList[k]->info, k+1, gm->adjList[k+1]->info);
                            }
                            if(pair){
                                printf("%i. %c\n", k, gm->adjList[k]->info);
                            }
                            printf("\nVoisin %i de %c > ", j, gm->adjList[i]->info);
                            scanf("%i", &voisin);
                        }while((voisin < 1 || voisin > gm->v) || chercher(T, m, voisin)==0);
                        T[m] = voisin;
                        m++;
                        do{
                            printf("Donner le poids entre %c et %c > ", gm->adjList[i]->info, gm->adjList[voisin]->info);
                            scanf("%i", &weight2);
                        }while(weight2<=0);

                        //elem e = elementCreer();
                        //elemAffecter(&e, recupererMan(gm, gm->adjList[voisin]->info));
                        elem e = recupererMan(gm, gm->adjList[voisin]->info);
                        addEdgeMan(gm, gm->adjList[i]->info, e, weight2);

                        }
                    }
                }else if(choix2 == 5){
                    if(!detruit){
                        destroyGraph(gm);
                        detruit = 1;
                    }
                }else{
                    test_cont = 0;
                }
                if(test_cont){
                    do{
                        printf("\nVoulez vous revenir au menu principal (O/N)? > ");
                        fflush(stdin);
                        scanf("%c", &continuer2);
                        continuer2 = toupper(continuer2);
                    }while(continuer2 != 'O' && continuer2 != 'N');
                    test_cont = (continuer2 != 'O');
                }else{
                    continuer2='O';
                }
                printf("%i  %c\n", test_cont, continuer2);
          }while(test_cont || continuer2=='N');

        }else{
            test_cont = 0;
        }
        if(test_cont){
            do{
                printf("Voulez vous continuer (O/N)? > ");
                fflush(stdin);
                scanf("%c", &continuer);
                continuer = toupper(continuer);
            }while(continuer != 'O' && continuer != 'N');
        }else{
            continuer='O';
        }
    }while(continuer=='O' && choix!=3);
}


