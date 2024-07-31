#ifndef EXPLODE_H_INCLUDED
#define EXPLODE_H_INCLUDED
struct Explode{

    char value[100];
    struct Explode* suivant;
};
typedef struct Explode ExplodeR;
ExplodeR* initExplodeListe();
ExplodeR* append(ExplodeR* Head,char* value);
void PExplodeListe (ExplodeR* head);
ExplodeR* explode(char* chaine,char sep);
int CountResult(ExplodeR* head);
char* EgetNvalue(int n,ExplodeR* head);
#endif // EXPLODE_H_INCLUDED
