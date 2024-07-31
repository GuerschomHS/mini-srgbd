#ifndef TYPES_DB
#define TYPES_DB
#include "primitives.h"
#include "table.h"
#include "Response.h"

// DB type
struct db{

    db_name nom;
    db_ref_name ref_;
};
// raccourcis
typedef struct db stock[4];
typedef struct db *Pdb;
// fonctions
RE_ initDBInfos(Pdb stock,Ip pos);
void showDB(Pdb stock,int plafond);
void useDB(db_name name,Pdb stock,int plafond,Ip use);
// fonctions de creation d'une DB;
State dbExist(db_name nom,Pdb stock,int plafond);
char* createRef();
State createDirFiles(char *);
State addDbToList(db_name nom,db_ref_name ref_,Pdb stock,int pos);
State createDB(db_name nom,Pdb stock,Ip pos);
TB* getDBDatas(Pdb Stock,int ref_use);
//selection
State Select(char* table,char* champ,TB* tabListe,Pdb stock,int in_use);
//create Table
State createTable(char* tableName,char* champs,TB* tabListe,Pdb stock,int in_use);
//insert
State insertIn(char* tableName,char* fvalues,TB* tabListe,Pdb stock,int in_use);
#endif
