#include "wr/table.h"
#include <stdio.h>
#include "wr/Response.h"


TB* initListeTable(){

    return NULL;
}
TB* newTable(TB* head,char* nom){

    TB* nvElement;
    nvElement=malloc(sizeof(*nvElement));
    strcpy(nvElement->nom,nom);
    nvElement->suivant= NULL;
    nvElement->ListeChamp = initListe();
    if(head == NULL) return nvElement;
    TB* temp;
    temp = head;
    while(temp->suivant!=NULL){

        temp = temp->suivant;
    }

    temp->suivant = nvElement;

    return head;
}

void PrintListeTable(char* tabName,TB* head){

    if(head == NULL){


        RE_ r;
        setReponse(&r,"Liste de Table","Aucune Table disponible dans la BDD",0);
        printReponse(r);
    }
    else if(tabName != NULL){

        TB* target = getTable(head,tabName);
        if(target == NULL){

            RE_ r;
            setReponse(&r,"Liste de Table","Aucune Table  correspondante",0);
            printReponse(r);
            return;
        }else{

            puts("");
            puts("  #++++++++++++++++++++++++++#");
            printf("  # %s\n",target->nom);
            puts("  #--------------------------#");
            puts("  # NOM      | TYPE          ");
            puts("  #--------------------------#");
            CH* temp = target->ListeChamp;
            int nhead = countChamp(temp);
            while(temp!=NULL){

                printf("  # %s     | %s    \n",temp->nom,temp->type);
                temp = temp->suivant;
            }
            puts("  #++++++++++++++++++++++++++#");
            puts("");
        }

    }
    else{


        while(head!=NULL){

            //PrintListe(head->ListeChamp);
            puts(" ");
            puts("  #++++++++++++++++++++++++++#");
            printf("  # %s\n",head->nom);
            puts("  #--------------------------#");
            puts("  # NOM      | TYPE          ");
            puts("  #--------------------------#");
            CH* temp = head->ListeChamp;
            int nhead = countChamp(temp);
            for(int i=0;i<nhead;i++){

                printf("  # %s     | %s    \n",temp->nom,temp->type);
                if((i+1)<nhead) temp = temp->suivant;
            }
            free(temp);
            head = head->suivant;
            puts("  #++++++++++++++++++++++++++#");
            puts(" ");
        }

    }
}

TB* removeTable(TB* head,char* nom){

    if(head == NULL) return NULL;
    TB* before;
    TB* current= head;
    TB* after=NULL;
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

TB* getTable(TB* head,char* nom){


    if(head == NULL) return NULL;
    TB* temp = head;
    int n = countTable(head);
    int f = 0;
    for(int i=0;i<n;i++){

        if(strcmp(temp->nom,nom)==0){

            f = 1;
            break;
        }else temp = temp->suivant;
    }
    if(f == 0) return NULL;
    else return temp;
}

int tableExist(char* name,TB* tabList){

    int r = 0;
    if(tabList == NULL) return r;
    TB* temp = tabList;
    while(temp!=NULL){

        if(strcmp(temp->nom,name)==0){

            r=1;
            break;
        }
        temp = temp->suivant;
    }
    return r;
}
int countTable(TB* head){

    if(head == NULL) return 0;
    int n=0;
    while(head!=NULL){

        n++;
        head=head->suivant;
    }

    return n;
}
