#include <stdlib.h>
#include <stdio.h>
#include "chrprim.h"

elem elemCreer () {
    elem e;
return e;
}

void elemDetruire (elem elt) {}

void elemAffecter(elem * e1, elem e2) {

*e1 = e2 ;}

void elemCopier(elem *e1, elem e2) {

*e1 = e2 ;
}

void elemLire(elem * elt) {
printf("Entrez un caratere : ") ;
scanf("%c",elt);
}

void elemAfficher(elem elt) {
printf(" %c ",elt);
}

int elemComparer(elem e1, elem e2)
{
return (e1==e2);
}
