#ifndef PRIMITIVES
#define PRIMITIVES

typedef char db_name[20];
typedef char db_ref_name[10];
typedef char Le;
typedef int *Ip;
typedef enum{

    OK,
    UNOK
}State;
typedef enum{

    INT,
    STR,
    FLT

}DATA_TYPE;
char* type2str(DATA_TYPE type);
// fonctions
int getSeparator(char *chaine,char separator);
void attribPart2(char *dest,char *source,int sep,int part);
char * concate(char * chaine1,char * chaine2);
char int2char(int x);
char* toStr(int* tab);
int* getArrayOfNumber(int x);
char* delN(char* ch);
#endif
