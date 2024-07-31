#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
struct Data{

    char value[30];
    int nLine;
    struct Data* suivant;
};
typedef struct Data DT;
DT* initListeData();
DT* newData(DT* Head,char* value);
DT* getData(DT* head,char* value);
DT* removeData(DT* head,char* value);
void PrintListeData(DT* head);
int countData(DT* head);
char* getNvalue(int n,DT* head);
#endif // DATA_H_INCLUDED
