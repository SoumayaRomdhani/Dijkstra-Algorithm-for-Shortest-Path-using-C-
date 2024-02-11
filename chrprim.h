#ifndef CHRPRIM_H_INCLUDED
#define CHRPRIM_H_INCLUDED


#include "chrsdd.h"

elem elemCreer();
void elemDetruire(elem);
void elemLire(elem*);
void elemAfficher(elem);
void elemAffecter(elem*, elem);
void elemCopier(elem*, elem);
int elemComparer(elem, elem);





#endif // CHRPRIM_H_INCLUDED
