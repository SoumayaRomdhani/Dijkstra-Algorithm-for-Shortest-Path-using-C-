#ifndef ELTCHR_H_INCLUDED
#define ELTCHR_H_INCLUDED


typedef struct{
    int jour;
    int mois;
    int annee;
}date;

typedef struct{
    char nom[20];
    date date_creation;
    int population, nb_municipalites, superficie;
}gouver, *ELEMENT;



#endif // ELTCHR_H_INCLUDED
