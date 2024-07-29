#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wr/commander.h"
#include "wr/Response.h"

//DB Variable
stock DBStock;
//Lecture des commandes
char cmd[MAX_INSTRUCTION];
int sortie = 0;
PXR pxr;
const char* prompt = " $root ";
int main(){
    pxr.sortie = 0;
    pxr._Ref = DBStock;
    pxr.DBcursor =-1;
    // itialisation DB
    RE_ c = initDBInfos(pxr._Ref,&pxr.nbrDB);
    printReponse(c);
    while(pxr.sortie !=1){

        printf("%s",prompt);
        fgets(cmd,sizeof(cmd),stdin);
        pxr = traite(cmd,pxr);
    }
    return 1;
}
