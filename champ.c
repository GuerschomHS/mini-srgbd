#include "wr/champ.h"
#include "wr/Response.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


CH* initListe(){

    return NULL;
}
CH* newChamp(CH* head,char* nom,char* type){

    CH* nvElement;
    nvElement=malloc(sizeof(*nvElement));
    strcpy(nvElement->nom,nom);
    strcpy(nvElement->type,type);
    nvElement->suivant= NULL;
    nvElement->listeData = initListeData();
    if(head == NULL)return nvElement;
    CH* temp;
    temp = head;
    while(temp->suivant!=NULL){

        temp = temp->suivant;
    }

    temp->suivant = nvElement;

    return head;
}

void PrintListe(CH* head){

    if(head == NULL){

        RE_ r;
        setReponse(&r,"Liste de champs","Aucun champ disponible",0);
        printReponse(r);
    }
    else{

        puts("  #-------------------------");
        puts("  # CHAMP [TYPE]        ");
        puts("  #-------------------------");
        while(head!=NULL){

            printf("  # %s [%s]\n",head->nom,head->type);
            head = head->suivant;
        }
    }
}

CH* removeChamp(CH* head,char* nom){

    if(head == NULL) return NULL;
    CH* before;
    CH* current= head;
    CH* after=NULL;
    // teste pour la tete
    if(strcmp(head->nom,nom) == 0){

        if(head->suivant!=NULL) {

            after = head->suivant;
        }
        head->suivant = NULL;
        free(head);
        return after;
    }
    // pour le corp
    while(strcmp(current->nom,nom)!=0){

        before = current;
        current = current->suivant;
        after = current->suivant;
    }
    before->suivant = after;
    current->suivant = NULL;
    free(current);
    return before;
}

CH* getChamp(CH* head,char* nom){

    if(head == NULL) return NULL;
    CH* temp = head;
    int founded = 0;
    while(temp!=NULL){

        if(strcmp(nom,temp->nom)==0){

            founded = 1;
            break;
        }
        temp = temp->suivant;
    }
    if(founded == 1) return temp;
    else return NULL;
}
int countChamp(CH* head){

    if(head == NULL) return 0;
    int n=0;
    while(head!=NULL){

        n++;
        head=head->suivant;
    }

    return n;
}

int getNPlace(char* nom,CH* head){

    int counter = 1;
    int founded = 0;
    if(head == NULL) return 0;
    CH* temp = head;
    while(temp != NULL){

        if(strcmp(nom,temp->nom) == 0){

            founded = 1;
            break;
        }
        counter++;
        temp = temp->suivant;
    }
    //printf("pour %s place = %d\n",nom,counter);
    if(founded == 0) return 0;
    else return counter;
}
