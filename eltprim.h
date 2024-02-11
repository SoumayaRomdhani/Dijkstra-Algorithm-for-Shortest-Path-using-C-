#ifndef ELTPRIM_H_INCLUDED
#define ELTPRIM_H_INCLUDED

#include "eltsdd.h"

ELEMENT elementCreer();
void elementDetruire(ELEMENT);
void elementLire(ELEMENT*);
void elementAfficher(ELEMENT);
void elementAffecter(ELEMENT*, ELEMENT);
void elementCopier(ELEMENT*, ELEMENT);
int elementComparer(ELEMENT, ELEMENT);




#endif // ELTPRIM_H_INCLUDED
