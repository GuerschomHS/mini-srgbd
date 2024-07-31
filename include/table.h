#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include "champ.h"

struct Table{

    char nom[20];
    CH* ListeChamp;
    struct Table* suivant;
};
typedef struct Table TB;
TB* initListeTable();
TB* newTable(TB* Head,char* nom);
TB* getTable(TB* head,char* nom);
TB* removeTable(TB* head,char* nom);
int tableExist(char* name,TB* tabList);
void PrintListeTable(char* tabName,TB* head);
#endif // TABLE_H_INCLUDED
