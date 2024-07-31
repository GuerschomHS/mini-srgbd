#ifndef CHAMP_H_INCLUDED
#define CHAMP_H_INCLUDED
#include "Data.h"
struct Champ{

    char nom[20];
    char type[8];
    struct Data* listeData;
    struct Champ* suivant;
};
typedef struct Champ CH;
// fonctions
CH* initListe();
CH* newChamp(CH* Head,char* nom,char* type);
CH* getChamp(CH* head,char* nom);
CH* removeChamp(CH* head,char* nom);
int getNPlace(char* nom,CH* liste);
void PrintListe(CH* head);
int countChamp(CH* head);
#endif // CHAMP_H_INCLUDED
