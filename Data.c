#include "wr/Data.h"
#include <stdio.h>
DT* initListeData(){

    return NULL;
}
DT* newData(DT* head,char* value){

    DT* nvElement;
    nvElement=malloc(sizeof(*nvElement));
    strcpy(nvElement->value,value);
    nvElement->suivant= NULL;
    if(head == NULL){

        return nvElement;
    }
    DT* temp;
    temp = head;
    while(temp->suivant!=NULL){

        temp = temp->suivant;
    }

    temp->suivant = nvElement;

    return head;
}

void PrintListeData(DT* head){

    if(head == NULL)puts("AUCUNE Data");
    else{


        while(head!=NULL){

            puts("-----------Affichage de la liste Data-------------");
            printf("Data : %s\n",head->value);
            printf("\t");
            head = head->suivant;
        }
    }
}

DT* removeData(DT* head,char* value){

    if(head == NULL) return NULL;
    DT* before;
    DT* current= head;
    DT* after=NULL;
    // teste pour la tete
    if(strcmp(head->value,value) == 0){

        if(head->suivant!=NULL) {

            after = head->suivant;
        }
        head->suivant = NULL;
        free(head);
        return after;
    }
    // pour le corp
    while(strcmp(current->value,value)!=0){

        before = current;
        current = current->suivant;
        after = current->suivant;
    }
    before->suivant = after;
    current->suivant = NULL;
    free(current);
    return before;
}

DT* getData(DT* head,char* value){

    if(head == NULL) return NULL;
    DT* temp = head;
    while(strcmp(temp->value,value)!=0){

        temp = temp->suivant;
    }
    return temp;
}

int countData(DT* head){

    if(head == NULL) return 0;
    int n=0;
    while(head!=NULL){

        n++;
        head=head->suivant;
    }

    return n;
}

char* getNvalue(int n,DT* head){

    DT* target = head;
    for(int i=0;i<n;i++)
        target = target->suivant;
    return target->value;
}
