#include "wr/Explode.h"
#include <stdio.h>

ExplodeR* initExplodeListe(){
    return NULL;
}
ExplodeR* append(ExplodeR* head,char* value){

    ExplodeR* nvElement;
    nvElement=malloc(sizeof(*nvElement));
    strcpy(nvElement->value,value);
    nvElement->suivant= NULL;
    if(head == NULL) return nvElement;
    ExplodeR* temp;
    temp = head;
    while(temp->suivant!=NULL){

        temp = temp->suivant;
    }

    temp->suivant = nvElement;

    return head;
}

void PExplodeListe (ExplodeR* head){

    if(head == NULL)puts("AUCUN ELEMENT");
    else{

        puts("-----------Affichage de la liste-------------");
        while(head!=NULL){

            printf("CHAMP : %s[%d]\n",delN(head->value),strlen(head->value));
            head = head->suivant;
        }
    }
}

ExplodeR* explode(char* chaine,char sep){

    ExplodeR* Liste = initExplodeListe();
    char tempChaine[20];
    int letterPos = 0;
    for(int i=0;i<strlen(chaine);i++){

        if(*(chaine+i)==sep){

            tempChaine[letterPos]='\0';
            Liste = append(Liste,tempChaine);
            letterPos =0;
            continue;
        }
        tempChaine[letterPos] = *(chaine+i);
        letterPos++;
    }
    tempChaine[letterPos] = '\0';
    Liste = append(Liste,tempChaine);

    return Liste;
}
int CountResult(ExplodeR* head){

    if(head == NULL) return 0;
    int n=0;
    while(head!=NULL){

        n++;
        head=head->suivant;
    }

    return n;
}

char* EgetNvalue(int n,ExplodeR* head){

    ExplodeR* target = head;
    for(int i=0;i<(n-1);i++)
        target = target->suivant;
    return target->value;
}
