#include <string.h>
#include "wr/commander.h"
#include "wr/table.h"
#include "wr/Explode.h"

void toLower(char* ch){

    int t = strlen(ch);
    for(int i=0;i<t;i++){

        int c =*(ch+i);
        if(c<92 && c>64){

            *(ch+i) = c+27;
        }
    }
}
PXR traite(char* cmd,PXR pxr){

    ExplodeR* line = explode(cmd,' ');
    //PExplodeListe(line1);
    if(strcmp(delN(line->value),"fin")==0){

        puts(" AU Revoir");
        pxr.sortie = 1;
        free(line);
        return pxr;
    }
    else if(strcmp(delN(line->value),"insertion")==0){

        char* d = delN(EgetNvalue(3,line));
        if(CountResult(line) == 4 && strcmp(d,"dans")==0){

            char* v = delN(EgetNvalue(2,line));
            char* tabName = delN(EgetNvalue(4,line));
            ExplodeR* vb = EgetNvalue(2,explode(v,':'));
            State i = insertIn(tabName,vb,pxr.DBTables,pxr._Ref,pxr.DBcursor);
            if(i == OK){

                RE_ r;
                setReponse(&r," Insertion ","Une ligne affecte",1);
                printReponse(r);
            }else{


                RE_ r;
                setReponse(&r," Insertion ","Erreure d'insertion",0);
                printReponse(r);
            }

        }else{


            RE_ r;
            setReponse(&r," Insertion ","Erreure de syntaxe",0);
            printReponse(r);
        }
    }
    else if(strcmp(delN(line->value),"creer")==0){

        if(CountResult(line) < 3){

            RE_ r;
            setReponse(&r," Creation ","Erreure de syntaxe",0);
            printReponse(r);
        }
        else{

            char* type = delN(EgetNvalue(2,line));
            if(strcmp(type,"db")==0){

                char* dbName = delN(EgetNvalue(3,line));
                State c = createDB(dbName,pxr._Ref,&pxr.nbrDB);
                RE_ r;
                if(c == UNOK) setReponse(&r," Creation Bade de Donnee","Erreure lors de la creation de la Base de donnee",0);
                else setReponse(&r,"Creation Bade de Donnee","Base de donnee créée",1);
                printReponse(r);
            }else if(strcmp(type,"table")==0){

                RE_ r;
                if(pxr.DBcursor<0){

                    setReponse(&r,"Creation Table","Aucune Base de donnee selectionee",0);
                    printReponse(r);
                }else{

                    ExplodeR* suite = explode(EgetNvalue(3,line),'!');
                    char* tabName = delN(EgetNvalue(1,suite));
                    char* cols = delN(EgetNvalue(2,suite));
                    State c = createTable(tabName,cols,pxr.DBTables,pxr._Ref,pxr.DBcursor);
                    if(c == UNOK) setReponse(&r," Creation Table","Erreure lors de la creation de la table",0);
                    else setReponse(&r,"Creation Table","Table créée",1);
                    pxr.DBTables = getDBDatas(pxr._Ref,pxr.DBcursor);
                    printReponse(r);
                }
            }
        }
    }
    else if(strcmp(delN(line->value),"listeTab")==0){

        if(pxr.DBcursor < 0) puts(" Aucune Base De Donnees Selectione");
        else{

            if(CountResult(line) ==  2){

                char* tabName = delN(EgetNvalue(2,line));
                PrintListeTable(tabName,pxr.DBTables);

            }else PrintListeTable(NULL,pxr.DBTables);
        }
    }
    else if(strcmp(delN(line->value),"utilise")==0){

        char* dbName = delN(EgetNvalue(2,line));
        useDB(dbName,pxr._Ref,pxr.nbrDB,&pxr.DBcursor);
        pxr.DBTables = getDBDatas(pxr._Ref,pxr.DBcursor);
    }
    else if(strcmp(delN(line->value),"selection")==0){

        if(pxr.DBcursor < 0){

            RE_ r;
            setReponse(&r,"Selection","Aucune Base de donnee selectionee",0);
            printReponse(r);
        }
        else if(CountResult(line) > 3){

            char* tabName = delN(EgetNvalue(4,line));
            char* colons = delN(EgetNvalue(2,line));
            Select(tabName,colons,pxr.DBTables,pxr._Ref,pxr.DBcursor);
        }else{

            RE_ r;
            setReponse(&r,"Selection","Erreure de syntaxe",0);
            printReponse(r);
        }
    }
    else if(strcmp(delN(line->value),"listeDB")==0){

        showDB(pxr._Ref,pxr.nbrDB);
    }
    else{
        puts("  Commande Inconnue");
    }

    free(line);
    return pxr;
}
