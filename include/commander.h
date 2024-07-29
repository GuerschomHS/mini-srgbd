#ifndef COMMANDER_H_INCLUDED
#define COMMANDER_H_INCLUDED
#define MAX_INSTRUCTION 255
#include "Explode.h"
#include "data_type.h"
struct Process{

    int nbrDB;
    int DBcursor;
    int sortie;
    TB* DBTables;
    Pdb _Ref;
};
typedef struct Process PXR;
PXR traite(char* cmd,PXR pxr);
void toLower(char* ch);
#endif // COMMANDER_H_INCLUDED
