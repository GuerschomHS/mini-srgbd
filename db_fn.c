#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "wr/data_type.h"
#include "wr/Explode.h"
#include "wr/table.h"
#include "wr/champ.h"
#include "wr/Response.h"

RE_ initDBInfos(Pdb stock,Ip pos)
{

    RE_ result;
    FILE *dbconf = fopen("dbs/dbs_list.txt","r");
    int indice = 0;
    if(dbconf == NULL)
    {

        setReponse(&result,"Chargement","Impossible de demarrer le programme,config introuvable",0);
        return result;
    }
    db_name chaine;
    while(fgets(chaine,sizeof(db_name),dbconf)!=NULL)
    {

        int sep = getSeparator(chaine,':');
        attribPart2(stock->nom,chaine,sep,1);
        attribPart2(stock->ref_,chaine,sep,2);
        stock++;
        indice++;
    }
    *(pos) = indice;
    setReponse(&result,"Chargement","Initialisation de la BD faite",1);
    return result;
}

void showDB(Pdb stock,int plafond)
{

    puts("");
    puts("  #-------------------------");
    puts("  # LIST DE BASE DE DONNEES ");
    puts("  #-------------------------");
    for(int i=0; i<plafond; i++)
    {

        printf("  #    %s\n",stock->nom);
        puts("  #-------------------------");
        stock++;
    }
    puts("");
}

void useDB(db_name target_name,Pdb stock,int plafond,Ip use)
{

    State founded = UNOK;
    for(int i=0; i<plafond; i++)
    {

        if(strcmp(stock->nom,target_name) == 0)
        {

            *(use) = i;
            printf("  <%s> est en cours d'utilisation\n",stock->nom);
            founded = OK;
            break;
        }
        else
        {

            stock++;
        }
    }
    if(founded == UNOK) printf("  la base de donee <%s> est introuvable\n",target_name);
}


State dbExist(db_name nom,Pdb stock,int plafond)
{

    State founded = UNOK;
    for(int i=0; i<plafond; i++)
    {

        if(strcmp(stock->nom,nom) == 0)
        {
            founded = OK;
            break;
        }
        else stock++;

    }

    return founded;
}

char * createRef()
{

    srand(time(NULL));
    int n = rand()%1000;
    int* tab = getArrayOfNumber(n);
    char *chaine = toStr(tab);
    char* ref =concate("ref_",chaine);
    char* cmd = concate("mkdir dbs\\",ref);
    system(cmd);

    return ref;
}
State createDirFiles(char *nom)
{

    char *path = concate("dbs/",nom);
    path = concate(path,"/db.txt");
    FILE *f = fopen(path,"w+");
    if(f == NULL ) return UNOK;
    else
    {

        fclose(f);
        return OK;
    }
}
State addDbToList(db_name nom,db_ref_name ref,Pdb stock,int pos)
{

    strcpy((stock+pos)->nom,nom);
    strcpy((stock+pos)->ref_,ref);

    FILE *f = fopen("dbs/dbs_list.txt","a");
    if(f == NULL) return UNOK;
    char *data = concate(nom,":");
    data = concate(data,ref);
    data = concate(data,"\n");
    int t = fputs(data,f);
    fclose(f);

    if(t == 0) return OK;
    else return UNOK;
}

State createDB(db_name nom,Pdb stock,Ip pos)
{

    // db existe
    State exist = dbExist(nom,stock,*(pos));
    if(exist == OK)
    {

        puts("BASE DE EXISTE");
        return UNOK;
    }
    char *ref = createRef(); // creation de la Reference
    State dirCreation = createDirFiles(ref);
    if(dirCreation == UNOK)
    {

        puts("IMPOSSIBLE DE CREER LE DIR");
        return UNOK;
    }
    State toListe = addDbToList(nom,ref,stock,*(pos));
    if(toListe == UNOK)
    {

        puts("IMPOSSIBLE DE CREER LA CONFIGURATION");
        return UNOK;
    }
    int indice = *(pos)+1;
    *(pos) = indice;
    return OK;
}
TB* getDBDatas(Pdb stock,int ref_use)
{

    // 1 on recup les tables
    struct db* cible = (stock+ref_use);
    char* path = concate("dbs/",cible->ref_);
    path = concate(path,"/db.txt");
    FILE* dbStruct = fopen(path,"r");
    if(dbStruct == NULL)
    {

        printf("Erreure de recuperation du fichier de la base de donne <%s>",cible->nom);
        return NULL;
    }
    // recuperation et creation de table
    TB* tabListe = initListeTable();
    char chaine[200];
    while(fgets(chaine,50,dbStruct)!=NULL)
    {

        // recuperation du nom de la table
        ExplodeR* tableDesc = explode(chaine,'@');
        tabListe = newTable(tabListe,tableDesc->value);
        // creation des champ de la table
        CH* tableChamps = initListe();
        ExplodeR* champs = explode(tableDesc->suivant,',');
        while(champs!=NULL)
        {

            ExplodeR* listed = explode(champs->value,':');
            tableChamps = newChamp(tableChamps,delN(listed->value),delN(listed->suivant->value));
            free(listed);
            champs = champs->suivant;
        }
        // ajout de champ dans la table
        TB* TBtarget = getTable(tabListe,tableDesc->value);
        TBtarget->ListeChamp = tableChamps;
        free(tableDesc);

    }
    fclose(dbStruct);

    return tabListe;
}

State Select(char* table,char* champs,TB* tabListe,Pdb stock,int in_use)
{

    TB* target = getTable(tabListe,table);
    if(target == NULL)
    {

        puts("Aucune table ne correspond");
        return UNOK;
    }
    int ColonsPlace[10];
    int nbr = 0;
    int typeAffichage = 0; // 0 == affichge de tout (*) , 1 == affichage avec filtre
    //parametre d'affichage
    if(strcmp(champs,"*") != 0)
    {

        typeAffichage = 1;
        ExplodeR* cols = explode(champs,',');
        if(CountResult(cols) == 1)
        {

            //puts("Un seul champ dans la selection");
            ColonsPlace[0]= getNPlace(champs,target->ListeChamp);
            //printf("Nom  = %s place %d\n",cols->value,ColonsPlace[0]);
            nbr = 1;
        }
        else
        {

            int c = 0;
            //puts("Plusieurs champs dans la selection");
            ExplodeR* temp = cols;
            while(temp!=NULL)
            {

                ColonsPlace[c] = getNPlace(delN(temp->value),target->ListeChamp);
                //printf("Nom  = %s place %d\n",temp->value,ColonsPlace[c]);
                temp = temp->suivant;
                c++;
                nbr++;
            }
        }
        free(cols);
    };

    //Ouvrir le fichier de la table;
    struct db* cible = (stock+in_use);
    char* table_file_name = concate(target->nom,".txt");
    char* path = concate("dbs/",cible->ref_);
    path = concate(path,"/");
    path = concate(path,table_file_name);
    FILE* table_file_data = fopen(path,"r");
    if(table_file_data == NULL)
    {

        printf(" Impossible d'ouvrir le fichier <%s>\n",path);
        return UNOK;
    }

    //Affichage des en-tetes
    int nChamp = countChamp(target->ListeChamp);
    CH* temp = target->ListeChamp;
    puts("");
    puts("#-------------------------#");
    if(typeAffichage == 0)
    {

        for(int i=0; i<nChamp; i++)
        {

            if((i+1)<nChamp)
            {

                printf("|  %s  |",temp->nom);
                temp = temp->suivant;
            }
            else printf("  %s  \n",temp->nom);
        }
    }
    else
    {

        if(nbr == 1)
        {
            CH* ch = getChamp(target->ListeChamp,champs);
            if(ch != NULL) printf("  %s  \n",ch->nom);
        }
        else
        {
            ExplodeR* colsName = explode(champs,',');
            for(int i=0; i<nbr; i++)
            {

                char* ch = delN(EgetNvalue(i+1,colsName));
                CH* ch_ = getChamp(target->ListeChamp,ch);
                if(ch_ == NULL) continue;
                else printf("|  %s  ",ch_->nom);
            }
            printf("\n");
        }
    }

    //Affichage des data
    char chaine[20];
    puts("#-------------------------#");

    while(fgets(chaine,20,table_file_data)!=NULL)
    {

        ExplodeR* explodeTab = explode(chaine,',');
        int nValues = CountResult(explodeTab);
        if(nValues > nChamp)
        {

            RE_ r;
            char* msg = concate("Il semble que la table ",target->nom);
            msg = concate(msg," soit corrompue");
            setReponse(&r,"Lecture de donnees ",msg,0);
            printReponse(r);
            break;
        }
        //afichage selon la cible
        if(typeAffichage == 0)
        {

            for(int i=0; i<nValues; i++)
            {


                if((i+1) == nValues) printf("  %s  \n",delN(EgetNvalue(i+1,explodeTab)));
                else printf("|  %s  |",delN(EgetNvalue(i+1,explodeTab)));
            }
        }
        else
        {

            if(nbr == 1) printf("|  %s  \n",delN(EgetNvalue(ColonsPlace[0],explodeTab)));
            else if(nbr > 1)
            {

                for(int i=0; i<nbr; i++)
                {

                    if((i+1) == nValues) printf("  %s  \n",delN(EgetNvalue(ColonsPlace[i],explodeTab)));
                    else printf("|  %s  |",delN(EgetNvalue(ColonsPlace[i],explodeTab)));
                }
            }
        }
        //---------------------------
        free(explodeTab);
    }
    fclose(table_file_data);

    puts("#-------------------------#");
    puts("");
}


State createTable(char* tableName,char* champs,TB* tabListe,Pdb stock,int in_use)
{

    //existe
    int existe = getTable(tabListe,tableName);
    if(existe != NULL)
    {

        free(existe);
        return UNOK;
    }

    //creation fichier
    struct db* cible = (stock+in_use);
    char* path = concate("dbs/",cible->ref_);
    path = concate(path,"/");
    char* path_db = concate(path,"db.txt");
    char* filename = concate(tableName,".txt");
    path = concate(path,filename);
    //construction de l'infos
    char* infos = concate(tableName,"@");
    infos = concate(infos,champs);
    infos = concate(infos,"\n");
    printf("Result %s\n",infos);
    //saving de l'infos
    FILE* filex = fopen(path_db,"a");
    if(filex == NULL) return UNOK;
    int x = fputs(infos,filex);
    fclose(filex);

    //creation fu fichier table
    filex = fopen(path,"w+");
    if(filex == NULL) return UNOK;
    fclose(filex);
    return OK;
}

State insertIn(char* tableName,char* fvalues,TB* tabListe,Pdb stock,int in_use)
{

    //existe
    TB* tab = getTable(tabListe,tableName);
    if(tab == NULL)
    {

        return UNOK;
    }
    struct db* cible = (stock+in_use);
    char* file_name = concate(tableName,".txt");

    char* path = concate("dbs/",cible->ref_);
    path = concate(path,"/");
    path = concate(path,file_name);
    FILE*  target = fopen(path,"a");

    if(target == NULL) return UNOK;
    char* data = concate(fvalues,"\n");
    fputs(data,target);
    fclose(target);

    return OK;
}
