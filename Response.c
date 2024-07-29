
// *** END ***
#include <stdio.h>
#include <string.h>
#include "wr/Response.h"

void setReponse(RE_* r,char* action,char* msg,int etat){

    strcpy(r->action_titre,action);
    strcpy(r->msg,msg);
    r->etat = etat;
}

void printReponse(RE_ r){

    puts("");
    printf("  #%s",r.action_titre);
    if(r.etat == 1) printf("[Succes]\n");
    else printf("[Erreur]\n");
    printf("  %s\n",r.msg);
    puts("");
}
