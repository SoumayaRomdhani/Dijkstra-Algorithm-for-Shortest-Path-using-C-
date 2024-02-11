#include <stdlib.h>
#include <stdio.h>
#include "eltprim.h"



ELEMENT elementCreer(){
    ELEMENT elt;
    elt = (ELEMENT) malloc(sizeof(gouver));
    return elt;
}

void elementDetruire(ELEMENT e){
    free(e);
}
void elementLire(ELEMENT *e){
    printf("donnez n caractere");
    scanf("%c",&*(*e));
}
void elementAfficher(ELEMENT e){
    printf("Nom : %s\n", e->nom);
    printf("   Date creation %i/%i/%i\n", e->date_creation.jour, e->date_creation.mois, e->date_creation.annee);
    printf("   Population : %i\n", e->population);
    printf("   Superficie : %i\n", e->superficie);
    printf("   Nombre Municipalites : %i", e->nb_municipalites);

}
void elementAffecter(ELEMENT *e1,ELEMENT e2){
    *e1=e2;
}
void elementCopier(ELEMENT *e1,ELEMENT e2){
    *(*e1)=*e2;
}
int elementComparer(ELEMENT e1,ELEMENT e2){
    return(strcmp(e1->nom, e2->nom));
}







